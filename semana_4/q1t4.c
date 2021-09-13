/* Este programa retorna a equacao  pi^2 = 8/1 + 8/9 + 8/25 + 8/49 + ...
   O programa para de incluir termos quando for menor que a toleranica E = 0,001
*/

#include <stdio.h>
#include <math.h>

#define NUMERADOR 8 // Define constante numerador com valor 8
#define E 0.001     // Tolerancia

int main()
{

    float pi = 0, frac_e;
    int base_a = 1;

    do
    {
        frac_e = NUMERADOR / pow(base_a, 2); // Formula que obtem a constante dividido pelo quadrado da variavel <base_a>;
        base_a += 2;                         // Soma de 2 em 2 a varivel <base_a>
        pi += frac_e;                        // Pi recebe <frac_e>

    } while (frac_e >= E);
    /* Tira a raiz */
    pi = sqrt(pi);

    /* Imprime pi */
    printf("%f\n", pi);

    return (0);
}
