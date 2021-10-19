//JOGO FROGGER ERIC D ARRIAGA(TURMA C) ISAAC BUENO(TURMA D).
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <windows.h>
#define VELOSPORT 60
#define MAXIMO 10

typedef enum
// constantes com as larguras dos carros.
{
    LCARRO  = 4,
    LONIBUS = 7,
    LSEDAN  = 6
}LARGURAS;
typedef enum
// constantes dos valores das teclas.
{
    ESPECIAL   = -32,
    SETA_ESQ   = 75,
    SETA_DIR   = 77,
    SETA_CIMA  = 72,
    SETA_BAIXO = 80,
    ENTER      = 13,
    ESC        = 27
}TECLAS;
typedef enum
//constantes dos valores dos limites do mapa.
{
    LIM_ESQ   = 1,
    LIM_DIR   = 70,
    LIM_CIMA  = 3,
    LIM_BAIXO = 25
}LIMITES_MOVIMENTO;
typedef enum
//constantes das posicaoes iniciais do sapo.
{
    X1_I = 28,
    Y1_I = 24,
    FILA1 = 10

}POSICOES;
void plota_sapo (int x1sapo, int y1sapo, int x2sapo, int y2sapo, COLORS cor)
//funcao que plota o sapo do jogo.
{
    textcolor(cor);
    gotoxy(x1sapo,y1sapo);
    printf(" /%c_%c\\ " ,169,169);
    gotoxy(x2sapo,y2sapo);
    printf("(_\\ /_)");
    textcolor(WHITE);
}
void frame(void)
//funcao que coloca moldura do jogo na tela.
{
        int i;
        for (i = LIM_CIMA - 1; i < LIM_DIR + 6; i++)//teto
        {
            gotoxy(i,LIM_CIMA);
            printf("%c", 205);
        }
        for (i = LIM_CIMA; i < LIM_BAIXO + 1; i++)//parede esquerda
        {
            gotoxy(LIM_ESQ,i);
            printf("%c",186);
        }
        for (i = LIM_CIMA; i < LIM_BAIXO + 1; i++)//chao
        {
            gotoxy( LIM_DIR + 6,i);
            printf("%c",186);
        }
        for (i = LIM_CIMA-1; i < LIM_DIR + 6; i++)//parede direita
        {
            gotoxy(i,LIM_BAIXO + 1);
            printf("%c",205);
        }
        //caracteres dos cantos da moldura de jogo
        gotoxy(LIM_ESQ,LIM_CIMA);//superior esquerdo
        printf("%c",201);
        gotoxy(LIM_ESQ,LIM_BAIXO +1);//inferior direito
        printf("%c",200);
        gotoxy(LIM_DIR+ 6,LIM_BAIXO + 1);//inferior direito
        printf("%c",188);
        gotoxy(LIM_DIR + 6,LIM_CIMA);//superior direito
        printf("%c",187);

    }

void testa_move (int *x1s, int *y1s, int *x2s, int *y2s, int tecla)
//funcao que testa se o movimento do sapo é valido (dentro da area de jogo).
//recebe cordenadas do sapo e uma tecla.
{
    switch (tecla)
    {
        case SETA_ESQ :
            if((*x1s -1) > LIM_ESQ)//condicao de limite da parede esquerda.
            {
                *x1s = *x1s -1;
                *x2s = *x2s -1;
                gotoxy(80,25);
                printf("ESQUERDA");
            }
            break;
        case SETA_DIR :
            if(*x1s+1 < LIM_DIR)  //condicao de limite da parede direita.
            {
                *x1s = *x1s+1;
                *x2s = *x2s+1;
                gotoxy(80,25);
                printf("DIREITA ");
            }
            break;
       case SETA_CIMA :
            if(*y1s -1 > LIM_CIMA) //condicao de limite do teto.
            {
                *y1s = *y1s -1;
                *y2s = *y2s -1;
                gotoxy(80,25);
                printf("CIMA      ");
            }
            break;
        case SETA_BAIXO :
            if(*y1s +1 < LIM_BAIXO) //condicao de limite do chao.
            {
                *y1s = *y1s +1;
                *y2s = *y2s +1;
                gotoxy(80,25);
                printf("BAIXO    ");
            }
            break;
    }
}
int testa_colisao (int x1Obj1, int x2Obj1, int y1Obj1,int y2Obj1, int x1Obj2, int x2Obj2, int y1Obj2, int y2Obj2)
// funcao que testa se ocorre a colisao entre dois objetos (envelopes) retorno 1 para colisao e retorno 0 para nao colisao.
{
    //condicao de colisao
    if(x1Obj2 <= x2Obj1 && x2Obj2 >= x1Obj1 && y1Obj2 <= y2Obj1 && y2Obj2>= y1Obj1)
        return 1; //conteudo de colide = 1.
    else
        return 0; //conteudo de colide = 0.
}

void move_sapo (int *x1s, int *y1s, int *x2s, int *y2s, int tecla, COLORS cor)
// funcao que faz o movimento do sapo.
{
    plota_sapo(*x1s,*y1s,*x2s,*y2s,BLACK); // apaga sapo.
    testa_move( x1s, y1s, x2s, y2s,tecla); // testa movimento do sapo.
    plota_sapo(*x1s,*y1s,*x2s,*y2s,GREEN); // desenha novo sapo.
}
void plota_carroSport(int x_car, int y_car, int *cont)
// funcao que desenha carro esportivo em coordenada especifica.
// count serve para referencias quantar colunas do carro serao impressas ( quanto maior count menos colunas (retirando colunas da esquerda) .
{
    int i,j;                                 // declaracao dos controles de laco.
    char c1[LCARRO+1] = {' ', 'O', ' ', 'O'};// declaracao da primeira linha do carro.
    char c2[LCARRO+1] = {'<', 'H', 'H', 'H'};// declaracao da segunda linha do carro.
    char c3[LCARRO+1] = {' ', 'O', ' ', 'O'};// declaracao da terceira linha do carro.
    gotoxy(x_car, y_car);
    for(j=*cont;j<LCARRO;j++)                // desenha primeira linha do carro.
        printf("%c", c1[j]);
    gotoxy(x_car, y_car+1);
    for(j=*cont;j<LCARRO+1;j++)              // desenha segunda linha do carro.
        printf("%c", c2[j]);
    gotoxy(x_car, y_car+2);
    for(j=*cont;j<LCARRO+1;j++)              // desenha terceira linha do carro.
        printf("%c", c3[j]);
}
void apagar(int x, int y, int tamanho, int linhas)
// funcao que apaga um objeto generico, referenciando uma coordenada e um tamanho.
{
    int i;
    char espaco[MAXIMO] = {};
    for(i=0; i<tamanho; i++)
    {
        espaco[i] = ' ';
    }

    for(i=0; i<linhas; i++)
    {
        cputsxy(x,y, espaco);
        y++;
    }
}
void move_carroSport(int *x_car, int *y_car, int *cont)
// funcao que move o carro esportivo.
{
    apagar(*x_car,*y_car,LCARRO, 3); // apaga o carro.

    if(*x_car<=LIM_ESQ +1)           // se o carro estiver em contato com a parede esquerda count eh acrescentado em um a cada movimento do carro.
        *cont = *cont +1;
    else
        *x_car = *x_car -1;          // senao carro eh desenhado uma posicao mais a esquerda sem mudar a quantidade de colunas desenhadas.
    if(*cont==4)                     // se count é igual a 4 (tamanho do carro) significa que todo carro ja foi apagado e entao coordenada de x_car eh alocada para seu valor inicial e count eh zerado para imprimir um novo carro inteiro na posicao inicial.
    {
      *x_car = LIM_DIR+1;
      *cont = 0;
    }

    plota_carroSport(*x_car,*y_car,cont); // desenha carro nas coordenadas especificas depois das condicionais.
    Sleep(VELOSPORT);
}
void loop_jogo (int *x1s, int *y1s, int *x2s, int *y2s, COLORS cor)
// funcao laco de jogo, espera entrada do usuario, move o sapo e testa se o sapo bateu no carro.
{
    char tecla = 'o'; //para interação.

    int x_car,y_car,cont; //coordenadas do carro e cont(contabilizador de colunas).
    x_car = LIM_DIR+1;
    y_car = FILA1;
    cont=0;
    do{
        fflush(stdin);    //limpa buffer de input.
        move_carroSport(&x_car, &y_car ,&cont);  //move carro.
        if(testa_colisao(*x1s, *x1s+6, *y1s, *y1s+1, x_car, x_car+3, y_car, y_car+2)) //se ouve colisao entre carro e sapo imprime uma mensagem de colizao a direita da area de jogo.
        {
            gotoxy(80,23);
            printf("COLISAO!");
        }

        if(kbhit())       //se uma tecla for apertada.
        {
            tecla = getch(); // tecla eh a entrada do teclado.
            if(tecla == ESPECIAL) //se tecla for do teclado especial.
            {
                tecla = getch();
                move_sapo(x1s,y1s,x2s,y2s,tecla,cor);//chamada da funcao move sapo com as coordenadas e tecla especifica.
            }
        }

    }while(tecla!=ESC); //caso tecla for ESC para o laco de jogo.
}

int main()
{
    int x1sapo,x2sapo,y1sapo,y2sapo; //declaracao das variaveis de coordenada do sapo.

    //valores iniciais das posicoes do envelope do sapo.
    x1sapo = X1_I ;
    x2sapo = X1_I ;
    y1sapo = Y1_I ;
    y2sapo = Y1_I +1;

    frame();
    plota_sapo(x1sapo,y1sapo,x2sapo,y2sapo,GREEN);     //plota sapo na posicao inicial.
    loop_jogo (&x1sapo,&y1sapo,&x2sapo,&y2sapo,GREEN); //espera a entrada de uma seta e movimenta o sapo de acordo com as setas do teclado auxiliar (encerra o programa quando pressionado ESC).
    gotoxy(80,28);//  vai para uma area de mensagem para dar informacoes de retorno.
}


















