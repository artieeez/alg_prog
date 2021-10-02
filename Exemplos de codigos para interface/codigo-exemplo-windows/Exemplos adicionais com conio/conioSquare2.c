/*
 *  INF01202 - Algoritmos e Programacao
 *  Intituto de Informatica - UFRGS
 *  Material cedido pelo Prof. Dr. Joel Luis Carbonera.
 *
 * Descricao:
 * Imprime um padrao colorido na tela com cores aleatorias alternadas
 * Este programa demonstra como usar funcoes da conio para manipular o console
 */

/*Inclui funcoes para manipular o terminal*/
#include <conio2.h>
/*Incluida apenas para usar a funcao Sleep*/
#include <windows.h>
/*Incluida apenas para usar a funcao time*/
#include <time.h>

/*Define o tamanho maximo do quadrado*/
#define MAX_SIZE 30
/*Define o tempo de espera para desenhar cada ponto do quadrado*/
#define WAIT_TIME 10
int main()
{
    int i,n,color;

    /*Inicializa a semente do gerador
    numeros pseudo-aleatorios*/
    srand(time(NULL));

    n=1;

    /*Limpa a tela*/
    clrscr();

    /*Define o fundo de todo o texto a seguir como preto*/
    textbackground(BLACK);

    /*Desenha quadrados aninhados, do mais externo
    para o mais interno*/
    while(n<MAX_SIZE)
    {
        /*Escolhe aleatoriamente uma cor entre 0 e 15*/
        color = rand()%15;

        /*Define a cor de todo o texto que vem a seguir
        como a cor aleatoria escolhida anteriormente*/
        textcolor(color);
        /*Gera um quadrado, cujos limites sao controlados por n*/
        for(i=n;i<MAX_SIZE-n;i++)
        {
            /*A cada iteracao, escreve 4 asteriscos coloridos
             em 4 pontos diferentes da tela. A cada ponto escrito,
             o programa espera um total de WAIT_TIME milissegundos
             para executar a proxima acao.*/
            gotoxy(i,n);
            cprintf("*");
            Sleep(WAIT_TIME);
            gotoxy(n,i);
            cprintf("*");
            Sleep(WAIT_TIME);
            gotoxy(i,MAX_SIZE-n-1);
            cprintf("*");
            Sleep(WAIT_TIME);
            gotoxy(MAX_SIZE-n-1,i);
            cprintf("*");
            Sleep(WAIT_TIME);
        }
        n++;
    }
    /*Espera o usuario digitar algo para finalizar o programa*/
    _getche();


    return 0;
}
