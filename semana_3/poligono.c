#include <stdlib.h>
#include <stdio.h>

int main(void) {
    float a, b, c, d;
    float *pointers_lados[3] = {&a, &b, &c};
    char id_lados[3] = {'A', 'B', 'C'};
    for(int i = 0; i < 3; i++) {
        if (i < 2) {
            printf("Insira o valor do lado %c: ", id_lados[i]);
        } else {
            printf("Insira o valor do lado C (será o mesmo de D): ", &c, &d);
        }
        scanf(" %f", pointers_lados[i]);
    }
    d = c;

    /* Checar se é um quadrado (todos lados iguais) */
    int todos_lados_sao_iguais = 1;
    for (int i = 0; i < 2; i++) {
        if (*pointers_lados[i] != c) {
            todos_lados_sao_iguais = 0;
        }
    }
    if (todos_lados_sao_iguais) {
        printf("\nOs valores inseridos formam um quadrado (Q)");
        return 0;
    }

    /* Checar se é um Retangulo (2 pares iguais de lados) */
    if (a == b) {
        printf("\nOs valores inseridos formam um retângulo (Q)");
        return 0;
    }

    /* Else */
    printf("\nOs valores inseridos formam um trapézio (T)");
    return 0;
}
