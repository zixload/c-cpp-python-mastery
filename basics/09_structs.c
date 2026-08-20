#include <stdio.h>
#include <string.h>

/*
 * 09 - STRUCTURES (struct)
 * ==========================
 * Une struct regroupe plusieurs variables (potentiellement de types
 * differents) sous un seul nom. C'est l'equivalent C d'un objet simple
 * sans methodes - la base pour representer des donnees complexes
 * (un point, une personne, un paquet reseau, etc.).
 */

/* --- Definition d'une structure ---
 * Ceci ne cree PAS de variable, ca definit juste un nouveau "moule"/type.
 */
struct Point {
    int x;
    int y;
};

/* --- typedef : donner un alias plus court a un type ---
 * Sans typedef, il faudrait ecrire "struct Personne" partout.
 * Avec typedef, on peut juste ecrire "Personne".
 */
typedef struct {
    char nom[50];
    int age;
    float taille; /* en metres */
} Personne;

/* --- Structure imbriquee : une struct qui contient une autre struct --- */
typedef struct {
    char nom_equipe[30];
    struct Point position_avatar; /* on reutilise Point defini plus haut */
    int score;
} Joueur;

void afficher_point(struct Point p);          /* passage par valeur = copie */
void deplacer_point(struct Point *p, int dx, int dy); /* passage par pointeur = modif reelle */
void afficher_personne(const Personne *p);

int main(void)
{
    /* --- Creer et initialiser une structure --- */
    struct Point origine = {0, 0}; /* initialisation dans l'ordre des champs */
    struct Point autre = {.x = 10, .y = 20}; /* initialisation nommee, plus explicite */

    printf("origine : ");
    afficher_point(origine);
    printf("autre : ");
    afficher_point(autre);

    /* --- Acceder et modifier les champs avec le point . --- */
    origine.x = 5;
    origine.y = 7;
    printf("\nApres modification, origine : ");
    afficher_point(origine);

    /* --- Passage par pointeur pour modifier reellement la structure ---
     * Comme pour les variables simples (voir 05 et 08), passer une struct
     * par valeur cree une COPIE - modifier la copie dans la fonction ne
     * change rien a l'original. Il faut passer son adresse.
     */
    printf("\nAvant deplacer_point : ");
    afficher_point(autre);
    deplacer_point(&autre, 5, -3); /* &autre = adresse de la struct autre */
    printf("Apres deplacer_point(&autre, 5, -3) : ");
    afficher_point(autre);

    /* --- Utilisation du type avec typedef (plus propre) --- */
    Personne moi;
    strcpy(moi.nom, "Luca");
    moi.age = 22;
    moi.taille = 1.78f;

    printf("\n");
    afficher_personne(&moi);

    /* --- L'operateur -> : acceder a un champ via un POINTEUR vers une struct ---
     * (*ptr).champ fonctionne, mais ptr->champ est le raccourci standard
     * et bien plus lisible - tu le verras partout en C.
     */
    Personne *ptr_moi = &moi;
    printf("\nVia le pointeur ptr_moi->age = %d (equivaut a (*ptr_moi).age)\n", ptr_moi->age);
    ptr_moi->age = 23; /* modifie directement la struct originale */
    printf("Apres ptr_moi->age = 23, moi.age = %d\n", moi.age);

    /* --- Tableau de structures ---
     * Tres courant : une liste d'enregistrements du meme type.
     */
    Personne equipe[3] = {
        {"Alice", 30, 1.65f},
        {"Bob", 25, 1.80f},
        {"Chloe", 28, 1.70f}
    };

    printf("\nTableau de structures (equipe) :\n");
    for (int i = 0; i < 3; i++) {
        afficher_personne(&equipe[i]);
    }

    /* --- Structure imbriquee --- */
    Joueur j1 = {"Les Faucons", {12, 8}, 150};
    printf("\nJoueur de l'equipe \"%s\", position (%d, %d), score %d\n",
           j1.nom_equipe, j1.position_avatar.x, j1.position_avatar.y, j1.score);
    /* on accede au champ imbrique avec deux points successifs :
     * j1.position_avatar est une struct Point, .x acces son champ x */

    return 0;
}

void afficher_point(struct Point p)
{
    printf("(%d, %d)\n", p.x, p.y);
}

void deplacer_point(struct Point *p, int dx, int dy)
{
    p->x += dx; /* equivaut a (*p).x += dx */
    p->y += dy;
}

void afficher_personne(const Personne *p)
{
    /* const Personne * : on promet de ne pas modifier la struct pointee,
     * juste la lire. Bonne pratique pour les fonctions d'affichage. */
    printf("  %s, %d ans, %.2fm\n", p->nom, p->age, p->taille);
}
