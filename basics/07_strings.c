#include <stdio.h>
#include <string.h>

/*
 * 07 - CHAINES DE CARACTERES (strings)
 * ======================================
 * En C, il n'existe PAS de vrai type "string" comme en Python ou C++.
 * Une chaine est simplement un tableau de char, termine par un octet
 * special valant 0, appele "caractere nul" et note '\0'. C'est cette
 * convention (pas un type special) qui permet de savoir ou la chaine
 * s'arrete.
 */

int longueur_manuelle(const char s[]); /* const = on promet de ne pas modifier s */
void inverser_chaine(char s[]);

int main(void)
{
    /* --- Declaration d'une chaine ---
     * "bonjour" occupe en realite 8 octets : b-o-n-j-o-u-r-\0
     * Le \0 final est ajoute AUTOMATIQUEMENT par le compilateur pour les
     * chaines litterales entre guillemets.
     */
    char mot[20] = "bonjour"; /* tableau de 20 chars, dont 8 utilises */

    printf("mot = \"%s\"\n", mot); /* %s affiche jusqu'au \0, pas jusqu'a la fin du tableau */
    printf("Taille du tableau (sizeof) = %zu\n", sizeof(mot));      /* 20 : la taille reservee */
    printf("Longueur de la chaine (strlen) = %zu\n", strlen(mot)); /* 7 : jusqu'au \0, sans le compter */

    /* --- Acceder aux caracteres individuellement, comme un tableau normal --- */
    printf("\nPremiere lettre : mot[0] = %c\n", mot[0]);
    printf("Derniere lettre avant le \\0 : mot[6] = %c\n", mot[6]);
    printf("Le caractere terminal mot[7] vaut %d (c'est \\0)\n", mot[7]);

    /* --- Fonctions de <string.h> : les outils standards pour manipuler les chaines --- */

    /* strlen : longueur d'une chaine (sans compter le \0) */
    printf("\nstrlen(\"exploit-mastery\") = %zu\n", strlen("exploit-mastery"));

    /* strcpy : copier une chaine dans une autre (ATTENTION : ne verifie pas
     * la taille du tableau destination, risque de debordement -> classique
     * source de vulnerabilites en C, on y reviendra cote exploit-mastery) */
    char destination[20];
    strcpy(destination, "copie moi");
    printf("Apres strcpy : destination = \"%s\"\n", destination);

    /* strcat : concatener (coller) une chaine a la fin d'une autre */
    char phrase[50] = "Bonjour";
    strcat(phrase, ", monde !"); /* le tableau doit etre assez grand pour tout contenir */
    printf("Apres strcat : phrase = \"%s\"\n", phrase);

    /* strcmp : comparer deux chaines
     * Renvoie 0 si elles sont IDENTIQUES.
     * Renvoie < 0 si la premiere est "avant" alphabetiquement.
     * Renvoie > 0 si la premiere est "apres" alphabetiquement.
     * PIEGE CLASSIQUE : on ne peut PAS comparer des chaines avec == en C,
     * ca comparerait les ADRESSES memoire, pas le contenu !
     */
    printf("\nstrcmp(\"abc\", \"abc\") = %d (identiques)\n", strcmp("abc", "abc"));
    printf("strcmp(\"abc\", \"abd\") = %d (abc vient avant)\n", strcmp("abc", "abd"));
    printf("strcmp(\"abd\", \"abc\") = %d (abd vient apres)\n", strcmp("abd", "abc"));

    /* strncpy / strncat : versions "n" = on precise une taille max, plus
     * sures que strcpy/strcat car elles limitent le nombre de caracteres
     * copies (bonne pratique en securite) */
    char securise[10];
    strncpy(securise, "une chaine trop longue", sizeof(securise) - 1);
    securise[sizeof(securise) - 1] = '\0'; /* strncpy ne garantit pas le \0 final ! */
    printf("\nstrncpy tronque : \"%s\"\n", securise);

    /* --- Parcourir une chaine caractere par caractere manuellement ---
     * Utile pour comprendre ce que font vraiment les fonctions de
     * string.h en interne, et essentiel pour du parsing bas niveau.
     */
    printf("\nParcours manuel de \"%s\" caractere par caractere :\n", mot);
    for (int i = 0; mot[i] != '\0'; i++) {
        printf("  mot[%d] = '%c'\n", i, mot[i]);
    }

    /* --- Implementation "maison" de strlen, pour comprendre le principe --- */
    printf("\nlongueur_manuelle(\"test\") = %d\n", longueur_manuelle("test"));

    /* --- Inverser une chaine sur place --- */
    char a_inverser[] = "Hello";
    printf("\nAvant inversion : \"%s\"\n", a_inverser);
    inverser_chaine(a_inverser);
    printf("Apres inversion : \"%s\"\n", a_inverser);

    return 0;
}

int longueur_manuelle(const char s[])
{
    int i = 0;
    while (s[i] != '\0') { /* on avance tant qu'on n'a pas trouve le caractere nul */
        i++;
    }
    return i;
}

void inverser_chaine(char s[])
{
    int longueur = longueur_manuelle(s);
    int debut = 0;
    int fin = longueur - 1;

    /* technique classique "deux pointeurs" : on echange les extremites en
     * se rapprochant du centre, jusqu'a se croiser */
    while (debut < fin) {
        char temp = s[debut];
        s[debut] = s[fin];
        s[fin] = temp;
        debut++;
        fin--;
    }
}
