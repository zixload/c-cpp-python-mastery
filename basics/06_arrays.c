#include <stdio.h>

/*
 * 06 - TABLEAUX (arrays)
 * =======================
 * Un tableau est une zone de memoire CONTIGUE (les cases se suivent les
 * unes derriere les autres) contenant plusieurs valeurs du meme type.
 * Contrairement aux listes Python, la taille d'un tableau C classique
 * est FIXE une fois declaree.
 */

void afficher_tableau(int tab[], int taille); /* prototype, voir 05 */
int somme_tableau(int tab[], int taille);
void afficher_matrice(int lignes, int colonnes, int matrice[lignes][colonnes]);

int main(void)
{
    /* --- Declaration et initialisation --- */
    int notes[5] = {12, 15, 8, 20, 17};
    /* "notes" est en realite l'ADRESSE de la premiere case du tableau
     * (on approfondit ce lien pointeur/tableau dans le fichier 08) */

    printf("Tableau notes : ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", notes[i]); /* [i] accede a la case d'indice i */
    }
    printf("\n");

    /* --- IMPORTANT : indexation a partir de 0 ---
     * notes[0] est le PREMIER element, notes[4] est le DERNIER (pour un
     * tableau de taille 5). notes[5] serait hors limites -> comportement
     * indefini (le compilateur ne t'arretera pas forcement, mais tu lis
     * de la memoire qui ne t'appartient pas -> bug silencieux ou crash).
     */
    printf("Premier element : notes[0] = %d\n", notes[0]);
    printf("Dernier element : notes[4] = %d\n", notes[4]);

    /* --- Calculer la taille d'un tableau avec sizeof ---
     * sizeof(tableau) donne la taille TOTALE en octets.
     * sizeof(tableau[0]) donne la taille d'UN element.
     * Le nombre d'elements = taille totale / taille d'un element.
     * ATTENTION : ca ne marche QUE dans la fonction ou le tableau a ete
     * declare (voir la note dans afficher_tableau plus bas).
     */
    int nb_elements = sizeof(notes) / sizeof(notes[0]);
    printf("Nombre d'elements dans notes : %d\n", nb_elements);

    /* --- Modifier une case --- */
    notes[2] = 10; /* on remplace le 8 par un 10 */
    printf("Apres modification, notes[2] = %d\n", notes[2]);

    /* --- Tableau non initialise vs initialise partiellement --- */
    int partiel[5] = {1, 2}; /* les cases restantes sont automatiquement mises a 0 */
    printf("\nTableau partiellement initialise {1, 2, ...} : ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", partiel[i]);
    }
    printf("\n");

    /* --- Passer un tableau a une fonction --- */
    printf("\nAppel de fonctions avec le tableau notes :\n");
    afficher_tableau(notes, 5);
    printf("Somme = %d\n", somme_tableau(notes, 5));

    /* --- Tableaux 2D (matrices) ---
     * En memoire, c'est toujours une zone contigue, mais organisee
     * "ligne par ligne". matrice[i][j] = ligne i, colonne j.
     */
    int matrice[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    printf("\nMatrice 2x3 :\n");
    afficher_matrice(2, 3, matrice);

    /* Parcours manuel pour bien visualiser l'acces ligne/colonne */
    printf("\nAcces individuel :\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("  matrice[%d][%d] = %d\n", i, j, matrice[i][j]);
        }
    }

    return 0;
}

void afficher_tableau(int tab[], int taille)
{
    /* Note importante : ici, sizeof(tab) ne fonctionnerait PAS pour avoir
     * la taille du tableau ! Une fois passe en parametre, "tab" est traite
     * comme un simple pointeur vers le premier element - toute
     * l'information de taille est perdue. C'est pour ca qu'on doit
     * TOUJOURS passer la taille explicitement en parametre. */
    for (int i = 0; i < taille; i++) {
        printf("  tab[%d] = %d\n", i, tab[i]);
    }
}

int somme_tableau(int tab[], int taille)
{
    int total = 0;
    for (int i = 0; i < taille; i++) {
        total += tab[i];
    }
    return total;
}

void afficher_matrice(int lignes, int colonnes, int matrice[lignes][colonnes])
{
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            printf("%3d ", matrice[i][j]);
        }
        printf("\n");
    }
}
