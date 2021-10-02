/* Este programa retorna quantidade de ações compradas na bolsa de valores e valor pago.*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define NUMAC 4
#define IDMAXIMO 50
#define PRECOMAXIMO 100
#define ACOESMAXIMO 10000
#define VALORMAXIMO 10000


int find_index(int key, int arr[], int n);


int main()
{
    int codigousuario, acoes;
    float valorpago, totalfaturado;
    int codigo[NUMAC]= {0};
    int qtade_inicial[NUMAC]= {0};
    int qtade_vendida[NUMAC]= {0};
    int disponivel[NUMAC]= {0};
    float preco[NUMAC] = {0};
    int i;
    int acaoindex=NUMAC;

    i=0;



    srand(time(0));


    for(i = 0; i < NUMAC; i++)
    {

        codigo[i] = (int)(rand() / (double) RAND_MAX * (IDMAXIMO + 1));
        qtade_inicial[i] = (int)(rand() / (double) RAND_MAX * (ACOESMAXIMO + 1));
        preco[i] = (float)(rand()/(float)RAND_MAX * (PRECOMAXIMO +1));
        disponivel[i] = qtade_inicial[i];
    }

    do
    {
        /*Retorna na tela Tabela incial com as quantidades de acoes e seus valores*/
        printf("\nAbaixo, selecione o codigo de uma empresa e escolha quantidade de acoes que deseja comprar:\n\n");
        printf("CODIGOACAO\tESTOQUE\t\tVALOR(R$)\n");
        for(int i=0; i<NUMAC ; i++)
        {
            printf("%d\t\t%d\t\t%.2f\n",codigo[i], disponivel[i], preco[i]);
        }
        printf("\nDigite o codigo das acoes que voce deseja comprar:\n");//Retorna mensagem na tela
        scanf("%d",&codigousuario);//leitura do valor digitado pelo usuario
        printf("Digite a quantidade de acoees que deseja comprar:\n");
        scanf("%d",&acoes);

        acaoindex = find_index(codigousuario, codigo, NUMAC);

        if(acoes < ACOESMAXIMO)
        {
            printf("Acoes compradas:%10d\n",acoes);//Retorna mensagem na tela com a quantidade de acoes compradas
            valorpago = acoes * preco[acaoindex];
            printf("Valor a pagar: R$%10.2f\n",valorpago);//Retorna mensagem na tela com resultado da operacao
            qtade_vendida[acaoindex] +=acoes;
            disponivel[acaoindex] -=acoes;
            totalfaturado +=valorpago;
        }

    }
    while (totalfaturado < VALORMAXIMO);

    printf("\nRELATORIO DE VENDAS DO DIA\n");//Retorna mensagem na tela
    printf("\nCODIGO DA ACAO\t\tQUANTIDADE\tTOTAL FATURADO(R$)\n");//Retorna mensagem na tela
    printf("\n%d\t%d\t%.2f",codigo[acaoindex],qtade_vendida[acaoindex],totalfaturado);




    return(0);//Encerra programa
}

int find_index(int key, int arr[], int n) {
    int i = 0;
    int index = n;
    while (index == n && i < n) {
        if (arr[i] == key) {
            index = i;
        }
        i++;
    }
    return index;
}
