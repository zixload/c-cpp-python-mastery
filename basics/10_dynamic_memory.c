#include <stdio.h>
#include <stdlib.h> /* malloc, calloc, realloc, free */
#include <string.h>

/*
 * 10 - ALLOCATION MEMOIRE DYNAMIQUE (malloc / free)
 * ====================================================
 * Jusqu'ici, toutes nos variables/tableaux avaient une taille FIXE,
 * decidee a la compilation, et vivaient sur la "pile" (stack) - elles
 * sont automatiquement detruites en sortant de leur fonction.
 *
 * L'allocation dynamique permet de reserver de la memoire sur le "tas"
 * (heap) A L'EXECUTION, avec une taille connue seulement au runtime
 * (ex: lue depuis un fichier ou saisie utilisateur). Cette memoire
 * NE disparait PAS automatiquement -> c'est a toi de la liberer avec
 * free(), sinon c'est une FUITE MEMOIRE (memory leak).
 */

typedef struct Noeud {
    int valeur;
    struct Noeud *suivant; /* un noeud pointe vers le noeud suivant */
} Noeud;

int *creer_tableau_dynamique(int taille, int valeur_initiale);
void afficher_tableau_int(const int *tab, int taille);
Noeud *creer_noeud(int valeur);
void afficher_liste(Noeud *tete);
void liberer_liste(Noeud *tete);

int main(void)
{
    /* --- malloc : reserver un bloc de memoire brut ---
     * malloc(n) reserve n OCTETS et renvoie un pointeur vers le debut du
     * bloc (ou NULL si l'allocation echoue, ex: plus de memoire dispo).
     * Il faut donc calculer nous-meme la taille avec sizeof.
     */
    int taille = 5;
    int *tableau = malloc(taille * sizeof(int)); /* place pour 5 int */

    if (tableau == NULL) {
        /* TOUJOURS verifier que malloc n'a pas echoue avant d'utiliser le
         * pointeur - sinon on risque de dereferencer NULL et crasher */
        printf("Erreur : allocation memoire echouee\n");
        return 1;
    }

    /* La memoire allouee par malloc n'est PAS initialisee - elle contient
     * des valeurs "poubelle" residuelles, il faut la remplir nous-memes */
    for (int i = 0; i < taille; i++) {
        tableau[i] = i * i; /* on peut utiliser [] comme un tableau normal */
    }

    printf("Tableau alloue dynamiquement : ");
    afficher_tableau_int(tableau, taille);

    /* --- free : liberer la memoire quand on n'en a plus besoin ---
     * OBLIGATOIRE pour chaque malloc/calloc/realloc reussi. Oublier free()
     * = fuite memoire. Le programme continue de tourner, mais consomme de
     * plus en plus de RAM au fil du temps si ca arrive en boucle.
     */
    free(tableau);
    tableau = NULL; /* bonne pratique : remettre a NULL apres free pour
                      * eviter un "use-after-free" (utiliser un pointeur
                      * qui pointe vers de la memoire deja liberee -
                      * source classique de bugs et de vulnerabilites) */

    /* --- calloc : comme malloc, mais initialise tout a 0 ---
     * calloc(nombre_elements, taille_element) - deux parametres au lieu
     * d'un, et la memoire est garantie initialisee a zero.
     */
    int *zeros = calloc(taille, sizeof(int));
    if (zeros == NULL) {
        printf("Erreur : allocation memoire echouee\n");
        return 1;
    }
    printf("\nTableau alloue avec calloc (initialise a 0) : ");
    afficher_tableau_int(zeros, taille);
    free(zeros);

    /* --- realloc : redimensionner un bloc deja alloue ---
     * Utile quand on ne connait pas la taille finale a l'avance (ex: on
     * lit des donnees petit a petit). Peut deplacer le bloc en memoire si
     * necessaire - c'est pour ca qu'on DOIT recuperer le nouveau pointeur.
     */
    int *dynamique = malloc(3 * sizeof(int));
    dynamique[0] = 1;
    dynamique[1] = 2;
    dynamique[2] = 3;
    printf("\nAvant realloc (3 elements) : ");
    afficher_tableau_int(dynamique, 3);

    int *agrandi = realloc(dynamique, 6 * sizeof(int));
    if (agrandi == NULL) {
        printf("Erreur : realloc a echoue\n");
        free(dynamique); /* si realloc echoue, l'ancien bloc est toujours valide */
        return 1;
    }
    dynamique = agrandi; /* on remplace par le (potentiellement nouveau) pointeur */
    dynamique[3] = 4;
    dynamique[4] = 5;
    dynamique[5] = 6;
    printf("Apres realloc (6 elements) : ");
    afficher_tableau_int(dynamique, 6);
    free(dynamique);

    /* --- Exemple concret : une liste chainee ---
     * Structure de donnees classique qui NECESSITE l'allocation
     * dynamique : chaque noeud est cree individuellement au fur et a
     * mesure, sans savoir a l'avance combien il y en aura.
     */
    printf("\nConstruction d'une liste chainee (1 -> 2 -> 3) :\n");
    Noeud *tete = creer_noeud(1);
    tete->suivant = creer_noeud(2);
    tete->suivant->suivant = creer_noeud(3);

    afficher_liste(tete);

    /* Liberer CHAQUE noeud individuellement - free() sur la tete ne
     * libererait que le premier noeud, pas ceux d'apres */
    liberer_liste(tete);

    printf("\nListe liberee, plus de fuite memoire.\n");

    return 0;
}

int *creer_tableau_dynamique(int taille, int valeur_initiale)
{
    int *tab = malloc(taille * sizeof(int));
    if (tab == NULL) {
        return NULL;
    }
    for (int i = 0; i < taille; i++) {
        tab[i] = valeur_initiale;
    }
    return tab; /* on renvoie le pointeur : c'est a l'appelant de faire free() plus tard */
}

void afficher_tableau_int(const int *tab, int taille)
{
    for (int i = 0; i < taille; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

Noeud *creer_noeud(int valeur)
{
    Noeud *n = malloc(sizeof(Noeud));
    if (n == NULL) {
        fprintf(stderr, "Erreur : allocation d'un noeud echouee\n");
        exit(1); /* quitte immediatement le programme avec un code d'erreur */
    }
    n->valeur = valeur;
    n->suivant = NULL;
    return n;
}

void afficher_liste(Noeud *tete)
{
    Noeud *courant = tete;
    while (courant != NULL) {
        printf("  %d -> ", courant->valeur);
        courant = courant->suivant; /* on avance au noeud suivant */
    }
    printf("NULL\n");
}

void liberer_liste(Noeud *tete)
{
    Noeud *courant = tete;
    while (courant != NULL) {
        Noeud *suivant = courant->suivant; /* on sauvegarde AVANT de liberer,
                                              * sinon on perd la reference
                                              * pour continuer le parcours */
        free(courant);
        courant = suivant;
    }
}
