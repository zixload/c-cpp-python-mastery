#include <stdio.h>

/*
 * 04 - BOUCLES (for, while, do-while)
 * =====================================
 * Les trois structures de boucle du C, plus break/continue pour
 * controler leur execution.
 */

int main(void)
{
    /* --- for : quand on connait a l'avance le nombre d'iterations ---
     * Structure : for (initialisation; condition; increment)
     * Les 3 parties sont executees dans cet ordre a chaque tour :
     * 1. initialisation (une seule fois, au debut)
     * 2. verification de la condition (avant chaque tour)
     * 3. corps de la boucle
     * 4. increment (apres chaque tour), puis retour a l'etape 2
     */
    printf("Boucle for (0 a 4) :\n");
    for (int i = 0; i < 5; i++) {
        printf("  i = %d\n", i);
    }

    /* --- while : quand on ne connait pas le nombre d'iterations a l'avance ---
     * La condition est verifiee AVANT chaque tour. Si elle est fausse des
     * le depart, le corps n'est jamais execute.
     */
    printf("\nBoucle while (division par 2 jusqu'a atteindre 1) :\n");
    int n = 100;
    while (n > 1) {
        printf("  n = %d\n", n);
        n = n / 2;
    }
    printf("  n = %d (fin)\n", n);

    /* --- do-while : comme while, mais la condition est verifiee APRES ---
     * Garantit que le corps s'execute AU MOINS une fois, meme si la
     * condition est fausse des le depart. Utile pour les menus interactifs
     * (on veut toujours afficher le menu au moins une fois).
     */
    printf("\nBoucle do-while (s'execute toujours au moins 1 fois) :\n");
    int compteur = 0;
    do {
        printf("  compteur = %d\n", compteur);
        compteur++;
    } while (compteur < 3);

    /* --- break : sortir immediatement de la boucle --- */
    printf("\nRecherche du premier multiple de 7 superieur a 50 (avec break) :\n");
    for (int i = 51; i < 1000; i++) {
        if (i % 7 == 0) {
            printf("  Trouve : %d\n", i);
            break; /* on arrete des qu'on a trouve, pas besoin de continuer */
        }
    }

    /* --- continue : passer directement au tour suivant, sans finir le corps --- */
    printf("\nNombres pairs entre 0 et 10 (avec continue) :\n");
    for (int i = 0; i <= 10; i++) {
        if (i % 2 != 0) {
            continue; /* si impair, on saute le printf ci-dessous */
        }
        printf("  %d\n", i);
    }

    /* --- Boucles imbriquees : une boucle a l'interieur d'une autre ---
     * Classique pour parcourir des structures 2D (tableaux, grilles,
     * matrices). La boucle interieure fait un tour COMPLET pour chaque
     * iteration de la boucle exterieure.
     */
    printf("\nTable de multiplication 1 a 3 (boucles imbriquees) :\n");
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            printf("  %d x %d = %d\n", i, j, i * j);
        }
    }

    /* --- Boucle infinie volontaire + condition de sortie interne ---
     * Pattern courant : for (;;) ou while (1), avec un break conditionnel
     * a l'interieur. Utile quand la condition de sortie est complexe ou
     * depend de plusieurs facteurs verifies a differents endroits.
     */
    printf("\nBoucle infinie avec sortie conditionnelle interne :\n");
    int somme = 0;
    int valeur = 1;
    for (;;) {
        somme += valeur;
        if (somme > 20) {
            printf("  somme a depasse 20 (valeur=%d, somme=%d), on arrete\n", valeur, somme);
            break;
        }
        valeur++;
    }

    return 0;
}
