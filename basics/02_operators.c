#include <stdio.h>

/*
 * 02 - OPERATEURS
 * ================
 * Les operateurs permettent de manipuler les valeurs des variables.
 * Ce fichier couvre : arithmetiques, relationnels, logiques, bitwise,
 * et l'ordre de priorite entre eux (tres important pour eviter les bugs
 * subtils).
 */

int main(void)
{
    /* --- Operateurs arithmetiques --- */
    int a = 17, b = 5;
    printf("Operateurs arithmetiques (a=%d, b=%d) :\n", a, b);
    printf("  a + b = %d\n", a + b);
    printf("  a - b = %d\n", a - b);
    printf("  a * b = %d\n", a * b);
    printf("  a / b = %d   <- division ENTIERE, la partie decimale est perdue !\n", a / b);
    printf("  a %% b = %d   <- modulo, le RESTE de la division\n", a % b);

    /* Piege classique : division entiere vs division flottante */
    double resultat_flottant = (double)a / b; /* on force un des deux en double */
    printf("  (double)a / b = %f  <- avec un cast, la division garde les decimales\n", resultat_flottant);

    /* --- Operateurs relationnels (comparaison) ---
     * Renvoient toujours 0 (faux) ou 1 (vrai) en C. Il n'y a pas de type
     * booleen natif avant C99 (stdbool.h), historiquement on utilise int.
     */
    printf("\nOperateurs relationnels :\n");
    printf("  a > b  : %d\n", a > b);
    printf("  a < b  : %d\n", a < b);
    printf("  a == b : %d\n", a == b); /* == pour COMPARER, != pour AFFECTER */
    printf("  a != b : %d\n", a != b);

    /* --- Operateurs logiques ---
     * && (ET), || (OU), ! (NON). Utilises pour combiner des conditions.
     * IMPORTANT : evaluation "court-circuit" - si le premier operande de
     * && est faux, le second n'est meme pas evalue (utile en pratique
     * pour eviter des crashs, ex: verifier qu'un pointeur n'est pas NULL
     * avant de le dereferencer).
     */
    int x = 5, y = 10;
    printf("\nOperateurs logiques :\n");
    printf("  (x > 0) && (y > 0) : %d\n", (x > 0) && (y > 0));
    printf("  (x < 0) || (y > 0) : %d\n", (x < 0) || (y > 0));
    printf("  !(x > 0)           : %d\n", !(x > 0));

    /* --- Operateurs bitwise (manipulation binaire directe) ---
     * Travaillent bit par bit sur la representation binaire des entiers.
     * Essentiels en systeme bas niveau : flags, masques, optimisations,
     * protocoles reseau, registres materiels.
     */
    unsigned char m1 = 0b00001100; /* 12 en decimal */
    unsigned char m2 = 0b00001010; /* 10 en decimal */
    printf("\nOperateurs bitwise (m1=%d=00001100, m2=%d=00001010) :\n", m1, m2);
    printf("  m1 & m2  (ET)         = %d\n", m1 & m2);   /* bit a bit : 1 si les deux valent 1 */
    printf("  m1 | m2  (OU)         = %d\n", m1 | m2);   /* bit a bit : 1 si au moins un vaut 1 */
    printf("  m1 ^ m2  (XOR)        = %d\n", m1 ^ m2);   /* bit a bit : 1 si les deux sont differents */
    printf("  ~m1      (NON/invert) = %d\n", (unsigned char)~m1); /* inverse tous les bits */
    printf("  m1 << 2  (decalage gauche) = %d  <- equivaut a multiplier par 2^2\n", m1 << 2);
    printf("  m1 >> 2  (decalage droite) = %d  <- equivaut a diviser par 2^2\n", m1 >> 2);

    /* --- Operateurs d'affectation composee ---
     * Raccourcis pour "variable = variable OP valeur"
     */
    int compteur = 10;
    compteur += 5;  /* equivaut a compteur = compteur + 5 */
    printf("\ncompteur += 5  -> %d\n", compteur);
    compteur *= 2;
    printf("compteur *= 2  -> %d\n", compteur);

    /* --- Increment / decrement, prefixe vs postfixe ---
     * ++i incremente PUIS renvoie la valeur.
     * i++ renvoie la valeur PUIS incremente.
     * La difference compte quand on utilise le resultat immediatement.
     */
    int i = 5;
    printf("\ni = %d\n", i);
    printf("i++ renvoie %d (utilise l'ancienne valeur)\n", i++);
    printf("apres i++, i vaut maintenant %d\n", i);
    printf("++i renvoie %d (incremente avant utilisation)\n", ++i);

    /* --- Priorite des operateurs (ordre d'evaluation) ---
     * Comme en maths : * et / avant + et -. Les operateurs bitwise ont une
     * priorite plus BASSE que ce qu'on imagine intuitivement, d'ou l'usage
     * systematique de parentheses en pratique pour eviter les erreurs.
     */
    int piege = 2 + 3 * 4;       /* = 14, pas 20 : * avant + */
    int piege_bitwise = 1 + 2 & 3; /* piege : + est evalue AVANT & */
    printf("\n2 + 3 * 4 = %d (multiplication prioritaire)\n", piege);
    printf("1 + 2 & 3 = %d  <- piege classique, toujours mettre des parentheses !\n", piege_bitwise);
    printf("(1 + 2) & 3 = %d\n", (1 + 2) & 3);

    return 0;
}
