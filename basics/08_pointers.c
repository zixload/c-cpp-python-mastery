#include <stdio.h>

/*
 * 08 - POINTEURS
 * ===============
 * LE concept central du C, celui qui le distingue le plus des langages
 * de haut niveau. Un pointeur est une variable qui ne stocke pas une
 * valeur "normale", mais l'ADRESSE MEMOIRE d'une autre variable.
 * Comprendre les pointeurs est indispensable pour la suite (structures
 * de donnees, allocation dynamique, et plus tard reverse engineering /
 * exploitation en bas niveau).
 */

int main(void)
{
    /* --- Toute variable a une adresse en memoire ---
     * L'operateur & ("address-of") donne l'adresse d'une variable.
     */
    int nombre = 42;
    printf("nombre = %d\n", nombre);
    printf("adresse de nombre (&nombre) = %p\n", (void *)&nombre);
    /* %p est le format specifier pour afficher une adresse. Le cast
     * (void *) est requis par convention pour printf avec %p. */

    /* --- Declarer un pointeur ---
     * "int *ptr" signifie : ptr est un pointeur qui pointera vers un int.
     * L'etoile ICI (dans la declaration) fait partie du TYPE, pas d'une
     * operation.
     */
    int *ptr = &nombre; /* ptr contient maintenant l'ADRESSE de nombre */

    printf("\nptr contient l'adresse : %p\n", (void *)ptr);
    printf("Cette adresse est bien celle de nombre : %d\n", &nombre == ptr);

    /* --- Dereferencement : acceder a la valeur POINTEE ---
     * *ptr ICI (dans une expression, pas une declaration) signifie :
     * "la valeur stockee a l'adresse contenue dans ptr".
     */
    printf("\n*ptr (valeur pointee) = %d\n", *ptr);

    /* --- Modifier la variable originale via le pointeur --- */
    *ptr = 100; /* on ecrit 100 a l'adresse pointee, donc on modifie nombre */
    printf("Apres *ptr = 100, nombre vaut maintenant : %d\n", nombre);
    /* C'est exactement ce mecanisme qui permettait a echanger() (voir 05)
     * de modifier les variables du main() : elle recevait leurs adresses. */

    /* --- NULL : le pointeur qui ne pointe vers rien ---
     * Convention pour dire "ce pointeur n'est pas encore initialise" ou
     * "n'a pas de cible valide". Dereferencer un pointeur NULL (*ptr sur
     * un pointeur NULL) provoque un crash immediat (segmentation fault) -
     * c'est volontaire, mieux vaut crasher proprement que corrompre de la
     * memoire au hasard.
     */
    int *ptr_vide = NULL;
    printf("\nptr_vide = %p (NULL)\n", (void *)ptr_vide);
    if (ptr_vide == NULL) {
        printf("On verifie AVANT de dereferencer -> on evite le crash\n");
    }
    /* *ptr_vide; <- decommenter cette ligne ferait planter le programme */

    /* --- Pointeurs et tableaux : un lien tres etroit ---
     * Le nom d'un tableau, utilise seul, "decade" (se convertit) en
     * pointeur vers son premier element. C'est pour ca que tab[i] et
     * *(tab + i) sont rigoureusement equivalents en C.
     */
    int tableau[5] = {10, 20, 30, 40, 50};
    int *ptr_tab = tableau; /* equivalent a : int *ptr_tab = &tableau[0]; */

    printf("\ntableau[0] = %d, *ptr_tab = %d (identiques)\n", tableau[0], *ptr_tab);
    printf("tableau[2] = %d, *(ptr_tab + 2) = %d (identiques)\n", tableau[2], *(ptr_tab + 2));

    /* --- Arithmetique de pointeurs ---
     * ptr + 1 n'avance PAS d'un octet, mais de la taille d'UN element du
     * type pointe. Pour un int* (4 octets), ptr+1 avance de 4 octets en
     * memoire reelle, mais represente "l'element suivant" logiquement.
     */
    printf("\nParcours du tableau avec un pointeur qu'on deplace :\n");
    for (int *p = tableau; p < tableau + 5; p++) {
        /* "tableau + 5" = l'adresse juste apres le dernier element,
         * classique "sentinel" pour savoir quand s'arreter */
        printf("  *p = %d (adresse %p)\n", *p, (void *)p);
    }

    /* --- Pointeur vers pointeur (double indirection) ---
     * Un pointeur peut lui-meme etre pointe par un autre pointeur.
     * Utile par exemple pour qu'une fonction puisse modifier un pointeur
     * (et pas juste la valeur qu'il pointe).
     */
    int valeur = 5;
    int *p1 = &valeur;   /* p1 pointe vers valeur */
    int **p2 = &p1;      /* p2 pointe vers p1 */

    printf("\nvaleur = %d\n", valeur);
    printf("*p1 = %d (valeur via p1)\n", *p1);
    printf("**p2 = %d (valeur via p2 -> p1 -> valeur)\n", **p2);

    return 0;
}
