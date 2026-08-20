#include <stdio.h>

/*
 * 01 - VARIABLES ET TYPES
 * ========================
 * En C, chaque variable doit avoir un type declare AVANT d'etre utilisee.
 * Contrairement a Python, le compilateur doit savoir exactement combien
 * d'octets reserver en memoire pour chaque variable - d'ou l'importance
 * des types.
 */

int main(void)
{
    /* --- Types entiers ---
     * int      : entier "normal", generalement 4 octets (32 bits) sur les
     *            machines modernes -> peut stocker de -2 147 483 648 a
     *            2 147 483 647.
     * short    : entier plus petit, souvent 2 octets.
     * long     : entier plus grand... mais PAS TOUJOURS ! Sur Linux/macOS
     *            64 bits il fait 8 octets, mais sur Windows (MinGW/MSVC)
     *            il reste 4 octets meme en 64 bits, par choix historique
     *            de Microsoft (modele "LLP64" vs "LP64" ailleurs). C'est
     *            un piege classique de portabilite.
     * long long: garanti au moins 8 octets sur TOUTES les plateformes -
     *            c'est le choix sur a faire des qu'on a besoin d'un grand
     *            entier de facon portable.
     * unsigned : version "non signee" -> pas de nombres negatifs, mais le
     *            double de la plage positive.
     */
    int age = 25;
    short annee_courte = 26;               /* juste pour illustrer le type short */
    long long grand_nombre = 10000000000LL; /* LL force le type long long */
    unsigned int compteur = 42;            /* ne peut jamais etre negatif */

    /* --- Types a virgule flottante ---
     * float  : precision simple, ~6-7 chiffres significatifs, 4 octets.
     * double : precision double, ~15-16 chiffres significatifs, 8 octets.
     *          C'est le choix par defaut en C pour les calculs flottants.
     */
    float prix_simple = 19.99f;       /* le suffixe f force le type float */
    double prix_precis = 19.999999999;

    /* --- Type caractere ---
     * char : stocke UN caractere sur 1 octet (en realite un petit entier,
     *        c'est pour ca qu'on peut faire de l'arithmetique dessus).
     */
    char lettre = 'A';
    char chiffre_ascii = lettre + 1; /* 'A' + 1 = 'B', car 'A' vaut 65 en ASCII */

    /* --- sizeof : connaitre la taille reelle d'un type sur TA machine ---
     * La taille exacte des types (sauf char, toujours 1 octet) depend du
     * compilateur et de l'architecture (32 vs 64 bits). sizeof() te donne
     * la vraie valeur au lieu de deviner.
     */
    printf("Tailles en octets sur cette machine :\n");
    printf("  int    : %zu octets\n", sizeof(int));
    printf("  short  : %zu octets\n", sizeof(short));
    printf("  long   : %zu octets\n", sizeof(long));
    printf("  long long : %zu octets\n", sizeof(long long));
    printf("  float  : %zu octets\n", sizeof(float));
    printf("  double : %zu octets\n", sizeof(double));
    printf("  char   : %zu octet\n", sizeof(char));

    /* Note : %zu est le format specifier correct pour sizeof(), qui
     * renvoie un type size_t (entier non signe). */

    printf("\nValeurs :\n");
    printf("  age = %d\n", age);
    printf("  annee_courte = %hd\n", annee_courte); /* %hd pour short */
    printf("  grand_nombre = %lld\n", grand_nombre); /* %lld pour long long */
    printf("  compteur = %u\n", compteur);          /* %u pour unsigned */
    printf("  prix_simple = %f\n", prix_simple);
    printf("  prix_precis = %.9f\n", prix_precis); /* .9 = 9 chiffres apres la virgule */
    printf("  lettre = %c (code ASCII %d)\n", lettre, lettre);
    printf("  chiffre_ascii = %c\n", chiffre_ascii);

    /* --- Conversion de type (casting) ---
     * Convertir explicitement un type vers un autre. Utile car sinon le
     * compilateur peut faire des conversions "silencieuses" qui perdent
     * de l'information (ex: double vers int tronque la partie decimale).
     */
    double pi = 3.14159;
    int pi_tronque = (int)pi; /* (int) force la conversion, .14159 est perdu */
    printf("\npi = %f devient %d une fois converti en int\n", pi, pi_tronque);

    return 0;
}
