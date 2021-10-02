/* Este programa retorna quantidade de ações compradas na bolsa de valores e valor pago.*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


#define VENDASMAXIMO 10000
#define N 7
#define MESES 12
#define MAXIMO 30
#define LIMITE 12
#define SAIR -1
#define TAMANHO_MAXIMO_NOME 20


int main(void)
{
    char usuario[MAXIMO] = {0};
    char acoes[N][TAMANHO_MAXIMO_NOME] = { "GERDAU" , "PETROBRAS","RENNER","VIVO","VALE","METALSINOS"};
    int vendas[N][MESES];
    int retorno=0;
    int l=0, c=0;
    int i=0;

    srand(time(NULL));

    for (l=0; l<N; l++) //For que atribui valores aleatorios entre 0 e 100 para os elementos da matriz
    {
        for(c=0; c<MESES; c++)
        {
            vendas[l][c] = (rand()/(double) RAND_MAX * (LIMITE+1)); //Gera valores aleatorios na matriz
        }
    }

    for (l =0; l<N; l++)
    {
        for(c=0; c<MESES; c++)
        {
            printf("%5d",vendas[l][c]);
        }
        printf("\n\n");
    }

    for(i=0; i<N; i++)
    {
        if( ! strcmp(usuario,acoes) )
        {
            printf("Acao digitada %s",usuario);
        }
    }


    int indice = -1;
    while( indice == -1 ) {
        printf("Digite o nome de uma acao:\n");
        scanf(" %s", &usuario);
        printf("Acao digitada %s",usuario);

        int i = 0;
        while(indice == -1 && i < N) {

            if (!strcmp(usuario, acoes[i])) {

                indice = i;
            }

            i++;
        };

        printf("%d", indice);

    }
    

    return(0);//Encerra programa
}

