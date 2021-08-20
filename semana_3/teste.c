#include <stdio.h>

int main(void) {
    int x;
    scanf("%d", &x);
    switch(x)
    {
    case 1:
        printf("Valor 1.\n");
    case 2:
        printf("Valor 2.\n");
    case 3:
        printf("Valor 3.\n");
    case 4:
        printf("Valor 4.\n");

    default:
        printf("Valor Invalido.\n");

    }
}