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
/*Define o tempo de espera para desenhar cada quadrado*/
#define WAIT_TIME 500
int main()
{
    int i,n,color;

    /*Inicializa a semente do gerador
    numeros pseudo-aleatorios*/
    srand(time(NULL));

    n=1;

    /*Limpa a tela*/
    clrscr();

    /*Desenha quadrados aninhados, do mais externo
    para o mais interno*/
    while(n<MAX_SIZE)
    {
        /*Escolhe aleatoriamente uma cor entre 0 e 15*/
        color = rand()%15;
        /*Define a cor do fundo de todo o texto que vem a seguir
        como a cor aleatoria escolhida anteriormente*/
        textbackground(color);
        /*Gera um quadrado, cujos limites sao controlados por n*/
        for(i=n;i<MAX_SIZE-n;i++)
        {
            /*A cada iteracao, escreve 4 espacos, que serao
            coloridos com a cor do fundo em 4 pontos
            diferentes da tela*/
            gotoxy(i,n);
            cprintf(" ");
            gotoxy(n,i);
            cprintf(" ");
            gotoxy(i,MAX_SIZE-n-1);
            cprintf(" ");
            gotoxy(MAX_SIZE-n-1,i);
            cprintf(" ");
        }
        n++;
        /*Espera um tempo de WAIT_TIME milissegundos para
        executar o proximo comando. Como isso ocorre apenas
        uma vez a cada quadrado desenhado, gera-se a impressao
        de que estamos desenhando um quadrado por vez*/
        Sleep(WAIT_TIME);
    }
    /*Espera o usuario digitar algo para finalizar o programa*/
    _getche();


    return 0;
}
