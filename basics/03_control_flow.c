#include <stdio.h>

/*
 * 03 - STRUCTURES DE CONTROLE (if / else / switch)
 * ==================================================
 * Permettent de faire executer differents blocs de code selon des
 * conditions. En C, "vrai" = toute valeur differente de 0, "faux" = 0.
 */

int main(void)
{
    /* --- if / else if / else --- */
    int note = 14;

    printf("Note = %d\n", note);
    if (note >= 16) {
        printf("Mention Tres Bien\n");
    } else if (note >= 14) {
        printf("Mention Bien\n");
    } else if (note >= 12) {
        printf("Mention Assez Bien\n");
    } else if (note >= 10) {
        printf("Admis sans mention\n");
    } else {
        printf("Recale\n");
    }
    /* Les else if sont evalues dans l'ordre, DES QU'UNE condition est
     * vraie, le reste est ignore - meme si une condition suivante serait
     * aussi vraie. */

    /* --- L'operateur ternaire : if/else condense en une expression ---
     * condition ? valeur_si_vrai : valeur_si_faux
     * Pratique pour des affectations simples, mais a eviter si ca devient
     * illisible (ne pas imbriquer plusieurs ternaires).
     */
    int a = 7, b = 12;
    int maximum = (a > b) ? a : b;
    printf("\nLe maximum entre %d et %d est %d (via l'operateur ternaire)\n", a, b, maximum);

    /* --- switch : quand on compare UNE variable a plusieurs valeurs fixes ---
     * Plus lisible qu'une longue chaine de else if quand on teste
     * l'egalite avec des constantes (pas des plages comme note >= 16).
     */
    int jour = 3;
    printf("\nJour numero %d : ", jour);
    switch (jour) {
        case 1:
            printf("Lundi\n");
            break; /* break est OBLIGATOIRE, sinon ca "tombe" dans le case suivant ! */
        case 2:
            printf("Mardi\n");
            break;
        case 3:
            printf("Mercredi\n");
            break;
        case 4:
            printf("Jeudi\n");
            break;
        case 5:
            printf("Vendredi\n");
            break;
        case 6:
        case 7:
            /* pas de break entre 6 et 7 : les deux valeurs partagent le
             * meme code -> "fall-through" volontaire et courant pour
             * regrouper des cas */
            printf("Week-end\n");
            break;
        default:
            /* execute si aucun case ne correspond */
            printf("Jour invalide\n");
    }

    /* --- Demonstration du piege "oubli de break" ---
     * Volontairement SANS break pour montrer le fall-through non-voulu,
     * une des erreurs les plus classiques en C.
     */
    printf("\nDemonstration du piege sans break (valeur = 2) :\n");
    int valeur = 2;
    switch (valeur) {
        case 1:
            printf("  cas 1\n");
        case 2:
            printf("  cas 2\n");
            /* pas de break ici expres */
        case 3:
            printf("  cas 3 (execute meme si valeur=2, car pas de break avant !)\n");
            break;
        default:
            printf("  defaut\n");
    }

    return 0;
}
