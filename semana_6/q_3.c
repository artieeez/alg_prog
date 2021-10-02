#include <time.h>    // necessaria para a função srand() e rand()
#include <stdlib.h>  //
#include <stdio.h>

/* Constantes */
#define N 5
#define VALOR_MAXIMO 99

int main(void) {
    srand(time(0));
    int m[N][N];
    int soma = 0, qnt_itens_somados;
    float media;

    /* Inicialização da Matriz */
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

            /* Inicializaão de item com valor aleatório */
            m[i][j] = (int)(rand() / (double) RAND_MAX * (VALOR_MAXIMO + 1));

            /* Soma dos itens abaixo da antidiagonal */
            if (i > 0 && (i + j) >= N) {
                soma += m[i][j];
                qnt_itens_somados++;
            }
        }
    }

    /* Print Matriz */
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%3d", m[i][j]);
        }
        printf("\n");
    }

    /* Cálculo da média */
    media = (float) soma / qnt_itens_somados;
    printf("Media dos itens abaixo da antidiagonal: %.2f\n", media);

    return 0;
}