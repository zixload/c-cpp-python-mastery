#include <stdio.h>

/*
 * 05 - FONCTIONS
 * ===============
 * Permettent de decouper un programme en blocs reutilisables. En C, une
 * fonction doit etre DECLAREE (prototype) avant d'etre utilisee si elle
 * est definie plus loin dans le fichier (ou dans un autre fichier).
 */

/* --- Prototypes (declarations) ---
 * Annoncent au compilateur : "cette fonction existe, voici sa signature".
 * Necessaire car le compilateur lit le fichier de haut en bas, et main()
 * est place avant les definitions completes ci-dessous.
 */
int addition(int a, int b);
double moyenne(int a, int b, int c);
void afficher_ligne(int longueur);       /* void = ne renvoie rien */
int factorielle(int n);                   /* fonction recursive */
int fibonacci(int n);                     /* fonction recursive */
void echanger(int *a, int *b);            /* passage par pointeur, voir plus bas */

int main(void)
{
    /* --- Appel de fonction simple avec valeur de retour --- */
    int resultat = addition(5, 3);
    printf("addition(5, 3) = %d\n", resultat);

    /* --- Fonction avec plusieurs parametres, type de retour different --- */
    double m = moyenne(10, 15, 20);
    printf("moyenne(10, 15, 20) = %.2f\n", m);

    /* --- Fonction void : ne renvoie rien, sert juste a produire un effet --- */
    printf("\nafficher_ligne(10) :\n");
    afficher_ligne(10);

    /* --- Recursion : une fonction qui s'appelle elle-meme ---
     * Il FAUT toujours un cas de base (condition d'arret), sinon la
     * fonction s'appelle indefiniment -> stack overflow (la pile d'appels
     * deborde, le programme crash).
     */
    printf("\nfactorielle(5) = %d\n", factorielle(5));
    printf("fibonacci(10) = %d\n", fibonacci(10));

    /* --- IMPORTANT : passage de parametres "par valeur" en C ---
     * Par defaut, quand tu passes une variable a une fonction, C en fait
     * une COPIE. Modifier le parametre a l'interieur de la fonction ne
     * change PAS la variable originale dans main().
     */
    int x = 100;
    printf("\nAvant tentative_modif : x = %d\n", x);
    /* Cette fonction (definie plus bas) modifie sa copie locale, pas x */

    /* --- Pour VRAIMENT modifier une variable depuis une fonction, il faut
     * lui passer son ADRESSE (un pointeur) au lieu de sa valeur. C'est la
     * base de tout le systeme de pointeurs qu'on approfondit en 08. */
    int p = 1, q = 2;
    printf("\nAvant echanger : p = %d, q = %d\n", p, q);
    echanger(&p, &q); /* &p = "l'adresse de p" */
    printf("Apres echanger : p = %d, q = %d\n", p, q);

    return 0;
}

/* --- Definitions (le vrai code des fonctions) --- */

int addition(int a, int b)
{
    return a + b;
}

double moyenne(int a, int b, int c)
{
    /* on force un cast en double pour eviter la division entiere (voir 02) */
    return (double)(a + b + c) / 3.0;
}

void afficher_ligne(int longueur)
{
    for (int i = 0; i < longueur; i++) {
        printf("-");
    }
    printf("\n");
    /* pas de "return valeur;" car le type de retour est void */
}

int factorielle(int n)
{
    if (n <= 1) {
        return 1; /* cas de base : arrete la recursion */
    }
    return n * factorielle(n - 1); /* appel recursif avec un probleme plus petit */
    /* Deroulement de factorielle(4) :
     *   4 * factorielle(3)
     *   4 * (3 * factorielle(2))
     *   4 * (3 * (2 * factorielle(1)))
     *   4 * (3 * (2 * 1))
     *   = 24
     */
}

int fibonacci(int n)
{
    /* Suite de Fibonacci : chaque terme est la somme des deux precedents.
     * 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55...
     */
    if (n <= 1) {
        return n; /* cas de base : fibonacci(0)=0, fibonacci(1)=1 */
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
    /* Attention : cette version recursive naive est TRES inefficace pour
     * de grands n (complexite exponentielle, beaucoup de recalculs). Une
     * version iterative (avec une boucle for) serait bien plus rapide -
     * exercice interessant a faire toi-meme. */
}

void echanger(int *a, int *b)
{
    /* a et b sont des POINTEURS : ils contiennent l'ADRESSE des variables
     * originales, pas leur valeur. *a signifie "la valeur pointee par a",
     * donc on peut la modifier directement. */
    int temp = *a;
    *a = *b;
    *b = temp;
}
