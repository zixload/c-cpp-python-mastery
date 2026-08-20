#include <stdio.h>

/* Comment: Print Fahrenheit to Celsius conversion for a user input */

int main()
{
    int fahr, celsius;

    fahr = 0;
    while (fahr <= 300) {
        celsius = (fahr - 32) * 5 / 9;
        printf("%d Fahrenheit = %d Celsius\n", fahr, celsius);
        fahr = fahr + 20;
    }

    return 0;
}
