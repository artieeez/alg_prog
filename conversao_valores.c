#include <stdio.h>
#include <math.h>

int main(void) {
    double valor;
    int p_inteira, p_decimal;

    scanf(" %lf", &valor);
    p_inteira = (int) valor;
    p_decimal = (int) ((valor - p_inteira) * 100);

    printf("%d\n", p_inteira);
    printf("%d\n", p_decimal);
    return 0;
}