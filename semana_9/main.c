/*
TAREFA 8

Feito por:
Artur Webber de Oliveira
João Pedro Telles Fava


*/

#include <conio2.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

/* Constantes */
#define PISTA_1_Y 10
#define MAX_VEICULOS 3
#define SEDAN_TESTE_X 1
#define SEDAN_WIDTH 4
#define ESPORTE_TESTE_X 20
#define ESPORTE_WIDTH 6
#define ONIBUS_TESTE_X 90
#define ONIBUS_WIDTH 12
#define VEIC_SPEED 6
#define NUM_SAPOS 3
#define DEFAULT_SAPO_X1 82
#define DEFAULT_SAPO_Y1 10
#define DEFAULT_SAPO_X2 89
#define DEFAULT_SAPO_Y2 11


#define QNT_TIPOS_VEIC 3

#define X_MIN 12
#define X_MAX 108
#define Y_MIN 3
#define Y_MAX 28

#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_RIGHT 77
#define ARROW_LEFT 75

typedef enum
// constantes com a posição do sapo de espera
{
    EX1 = X_MIN,
    EX2 = X_MIN + 7,
    EY1 = Y_MAX + 1,
    EY2 = Y_MAX + 2,
}POS_ESPERA;

typedef enum
// constantes com o id de cada entidade do jogo
{
    ESPORTE = 0,
    SEDAN  = 1,
    ONIBUS = 2,
}ENTITIES;
#define QNT_TIPOS_VEIC 3

/* --  QUESTÃO 4  --------------------------------------------------- */
typedef enum
{
    ESPERA = 1,
    ATIVO = 2,
    SALVO = 3,
    MORTO = 4
} STATUS_SAPO;

/* Collision */
bool is_a_and_b_colliding_in_one_axis(int a, int a_length, int b, int b_length);
short testa_colisao(int x1Obj1, int x2Obj1, int y1Obj1, int y2Obj1,
                    int x1Obj2, int x2Obj2, int y1Obj2, int y2Obj2);
bool is_out_of_boundary_alternative( int xc1, int yc1, int xc2, int yc2 );

/* Controllers */
int capture_action();
void game_loop(int pontox1[],
                int pontoy1[],
                int pontox2[],
                int pontoy2[],
                int tipoVeiculo[],
                int distVeiculo[],
                short veiculo_valido[],
                STATUS_SAPO sapos[],
                int psx1[],
                int psx2[],
                int psy1[],
                int psy2[]);

/* Renders */
void explosao(int x1, int x2, int y1, int y2);
void desenha_borda(int x_min, int y_min, int x_max, int y_max);
void desenha_sapo(int x1, int x2, int y1, int y2, COLORS color);
short desenha_veiculo(int xc1, int yc1, int xc2, int yc2, int tipo, int direcao,
                         int color );



/* --  QUESTÃO 5  --------------------------------------------------- */
int main()
{
    _setcursortype( _NOCURSOR );

    srand(time(0));

    /* clear the screen */
    clrscr();

    /* Desenha a borda */
    desenha_borda(X_MIN, Y_MIN, X_MAX, Y_MAX);

    gotoxy(25, 1);
    printf("TAREFA 9 - Espere os carros colidirem no sapo para verificar funcoes");


    /* --  QUESTÃO 3  ----------------------------------------------- */
    int pontox1[MAX_VEICULOS] = { SEDAN_TESTE_X, ESPORTE_TESTE_X, ONIBUS_TESTE_X };
    int pontoy1[MAX_VEICULOS] = { PISTA_1_Y, PISTA_1_Y, PISTA_1_Y };
    int pontox2[MAX_VEICULOS] = {((SEDAN_TESTE_X + SEDAN_WIDTH) - 1),
                                ((ESPORTE_TESTE_X + ESPORTE_WIDTH) - 1),
                                ((ONIBUS_TESTE_X + ONIBUS_WIDTH) - 1),};
    int pontoy2[MAX_VEICULOS] = { (PISTA_1_Y + 2), (PISTA_1_Y + 2), (PISTA_1_Y + 2) };
    int tipoVeiculo[MAX_VEICULOS] = { ESPORTE, SEDAN, ONIBUS };
    int distVeiculo[MAX_VEICULOS] = { 0 };
    short veiculo_valido[MAX_VEICULOS] = { 0 };

    int psx1[NUM_SAPOS] = { DEFAULT_SAPO_X1 };
    int psx2[NUM_SAPOS] = { DEFAULT_SAPO_X2 };
    int psy1[NUM_SAPOS] = { DEFAULT_SAPO_Y1 };
    int psy2[NUM_SAPOS] = { DEFAULT_SAPO_Y2 };


    psx1[1] = EX1;
    psx1[1] = EX2;
    psy2[1] = EY1;
    psy2[1] = EY2;

    psx1[2] = EX1 + 9;
    psx1[2] = EX2 + 9;
    psy2[2] = EY1;
    psy2[2] = EY2;





    // Inicialização da Matriz
    for (int i = 0; i < MAX_VEICULOS; i++) {
        distVeiculo[i] = (int)(rand() / (double) RAND_MAX * 24);
    }

    STATUS_SAPO sapos[NUM_SAPOS] = { ESPERA, ESPERA, ESPERA  };

    game_loop(pontox1,
                pontoy1,
                pontox2,
                pontoy2,
                tipoVeiculo,
                distVeiculo,
                veiculo_valido,
                sapos,
                psx1,
                psx2,
                psy1,
                psy2);

    return 0;
}




/* --  QUESTÃO 4  --------------------------------------------------- */
int mata_sapo(STATUS_SAPO sapos[], int *indice_sapo,
                int *x1s, int *x2s, int *y1s, int *y2s,
                int x1c, int x2c, int y1c, int y2c) {

    /* --  ITEM A  -------------------------------------------------- */
    short colisao = testa_colisao( *x1s, *x2s, *y1s, *y2s,
                                    x1c, x2c, y1c, y2c);

    if (colisao) {

        /* --  ITEM B.1  -------------------------------------------- */
        explosao(x1c, x2c, y1c, y2c);

        /* --  ITEM B.2  -------------------------------------------- */
        sapos[*indice_sapo] = MORTO;

        /* Apaga o sapo */
        desenha_sapo(*x1s,
                    *x2s,
                    *y1s,
                    *y2s,
                    BLACK);

        if (*indice_sapo + 1 >= NUM_SAPOS) {
            return 2;
        } else {
            /* --  ITEM B.3  ---------------------------------------- */
            sapos[*indice_sapo + 1] = ATIVO;
            *indice_sapo += 1;
            *x1s = DEFAULT_SAPO_X1;
            *x2s = DEFAULT_SAPO_X2;
            *y1s = DEFAULT_SAPO_Y1;
            *y2s = DEFAULT_SAPO_Y2;
            return 1;
        }
    } else {
        return 0;
    }
}




/* --  QUESTÃO 1  --------------------------------------------------- */
short testa_colisao(int x1Obj1, int x2Obj1, int y1Obj1, int y2Obj1,
                    int x1Obj2, int x2Obj2, int y1Obj2, int y2Obj2) {

    bool x_axis_colission = is_a_and_b_colliding_in_one_axis(x1Obj1,
                                                            x2Obj1 - x1Obj1,
                                                            x1Obj2,
                                                            x2Obj2 - x1Obj2);

    bool y_axis_colission = is_a_and_b_colliding_in_one_axis(y1Obj1,
                                                            y2Obj1 - y1Obj1,
                                                            y1Obj2,
                                                            y2Obj2 - y1Obj2);

    return (short) (x_axis_colission && y_axis_colission);
}

bool is_a_and_b_colliding_in_one_axis(int a, int a_length, int b, int b_length)
{
    return !(b > (a + a_length) || (b + b_length) < a);
}


/* --  QUESTÃO 2  --------------------------------------------------- */
short desenha_veiculo(int xc1, int yc1, int xc2, int yc2,
                        int tipo, int direcao, int color ) {
    short out_of_boundary = (short) is_out_of_boundary_alternative(  xc1,  yc1,  xc2,  yc2 );

    int height = (yc2 - yc1) + 1;
    int width = (xc2 - xc1) + 1;

    char *content_[3];

    if (tipo == ESPORTE) {
        if (direcao) {
            char *content[3] = {
                    "o o ",
                    "HHH>",
                    "o o "
                };
            content_[0] = content[0];
            content_[1] = content[1];
            content_[2] = content[2];
        } else {
            char *content[3] = {
                " o o",
                "<HHH",
                " o o"
            };
            content_[0] = content[0];
            content_[1] = content[1];
            content_[2] = content[2];

        }
    } else if (tipo == SEDAN) {
        if (direcao) {
            char *content[3] = {
                    " o  o ",
                    "=||||]",
                    " o  o "
                };
            content_[0] = content[0];
            content_[1] = content[1];
            content_[2] = content[2];
        } else {
            char *content[3] = {
                " o  o ",
                "[||||=",
                " o  o "
            };
            content_[0] = content[0];
            content_[1] = content[1];
            content_[2] = content[2];

        }
    } else if (tipo == ONIBUS) {
        if (direcao) {
            char *content[3] = {
                    " oo       o ",
                    "[[[[[[[[[[(8",
                    " oo       o "
                };
            content_[0] = content[0];
            content_[1] = content[1];
            content_[2] = content[2];
        } else {
            char *content[3] = {
                " o       oo ",
                "8)]]]]]]]]]]",
                " o       oo "
            };
            content_[0] = content[0];
            content_[1] = content[1];
            content_[2] = content[2];
        }
    }

    textcolor(color);


    for( int i = 0; i < height; i++) {
        gotoxy( xc1, yc1 );

        for( int j = 0; j < width; j++) {

            // Handle render crop at x axis when out of boundary
            if ( ((xc1 + j) - 1) > X_MIN && (xc1 + j) < X_MAX) {
                putch( content_[i][j] );
            } else {
                gotoxy( xc1 + j, yc1 );
            }

        }
        yc1 += 1;
    }

    textcolor(WHITE);
    gotoxy( X_MAX, Y_MAX );

    return out_of_boundary;
}

bool is_out_of_boundary_alternative( int xc1, int yc1, int xc2, int yc2 ) {
    int width = xc2 - xc1;
    int height = yc2 - yc1;

    bool a = yc1            <= Y_MIN;
    bool b = (xc1 + width)  >= X_MAX + 1;
    bool c = (yc1 + height) >= Y_MAX + 1;
    bool d = xc1            <= X_MIN;

    return ( a || b || c || d );
}


/*  RENDERS  -----------------------------------------------------

*/
void desenha_borda(int x_min, int y_min, int x_max, int y_max) {
/*  x1, y1 : canto superior esquerdo da tela.
    x2, y2 : canto inferior direito da tela.
*/
    int i;
    gotoxy( x_min, y_min );
    for (i = x_min; i <= x_max; i++) {
            putch( '=');
    }

    gotoxy( x_min, y_max );
    for (i = x_min; i < x_max; i++) {
            putch( '=' );
    }

    for (i = (y_min + 1); i < y_max; i++)
    {
        putchxy( x_min, i, '|');
        putchxy( x_max, i, '|');
    }
    return;
}

void desenha_sapo(int x1, int x2, int y1, int y2, COLORS color) {
    int height = (y2 - y1) + 1;
    int width = (x2 - x1) + 1;

    char *content[2] = {
        "  (00)  ",
        "\\^{  }^/"
    };

    textcolor(color);

    for( int i = 0; i < height; i++) {
        gotoxy( x1, y1 );

        for( int j = 0; j < width; j++) {

            // Handle render crop at x axis when out of boundary
            if ( ((x1 + j) - 1) > X_MIN && (x1 + j) < X_MAX) {
                putch( content[i][j] );
            } else {
                gotoxy( x1 + j, y1 );
            }

        }
        y1 += 1;
    }

    textcolor(WHITE);
    _setcursortype( _NOCURSOR );
    gotoxy( X_MAX, Y_MAX );

    return;
}

void explosao(int x1, int x2, int y1, int y2) {
    for( int i = 0; i < 3; i++) {
        gotoxy( x1, y1 + i);
        putch( 'X' );
    }

    Sleep(1000);

    for( int i = 0; i < (y2 - y1); i++) {
        gotoxy( x1, y1 );

        for( int j = 0; j < (x2 - x1); j++) {

            // Handle render crop at x axis when out of boundary
            if ( ((x1 + j) - 1) > X_MIN && (x1 + j) < X_MAX) {
                putch( 'X' );
            } else {
                gotoxy( x1 + j, y1 );
            }
        }
        y1 += 1;
    }
}

/*  CONTROLLERS  --------------------------------------------------

*/

/* --  QUESTÃO 3  --------------------------------------------------- */
void desenha_lista_veiculos(int x1[],
                            int y1[],
                            int x2[],
                            int y2[],
                            int tipoVeiculo[],
                            int distVeiculo[],
                            int direcao,
                            short veiculo_valido[]) {

    for (int i = 0; i < MAX_VEICULOS; i++) {

        /* --  ITEM A  ---------------------------------------------- */
        desenha_veiculo(x1[i],
                        y1[i],
                        x2[i],
                        y2[i],
                        tipoVeiculo[i],
                        direcao,
                        BLACK);

        /* --  ITEM B  ---------------------------------------------- */
        if (direcao) {
            x1[i] = x1[i] + VEIC_SPEED;
            x2[i] = x2[i] + VEIC_SPEED;
        } else {
            x1[i] = x1[i] - VEIC_SPEED;
            x2[i] = x2[i] - VEIC_SPEED;
        }

        /* --  ITEM C / ITEM D  ------------------------------------- */
        veiculo_valido[i] = desenha_veiculo(x1[i],
                                            y1[i],
                                            x2[i],
                                            y2[i],
                                            tipoVeiculo[i],
                                            direcao,
                                            GREEN);

        /* Reinicia posição do veículo */
        if (veiculo_valido[i] && x1[i] >= X_MAX) {
            x2[i] -= x1[i] - 1;
            x1[i] = 1;
        }


    }

    return;
}

int capture_action() {
    if (kbhit())
        {
            char c = getch();

            if (c == 'q') {
                return 5;
            }

            if ((int) c == -32)
            {

                switch(getch())
                {
                case ARROW_UP:
                    return 1;
                    break;
                case ARROW_RIGHT:
                    return 2;
                    break;
                case ARROW_DOWN:
                    return 3;
                    break;
                case ARROW_LEFT:
                    return 4;
                    break;
                }
            }
        }
    return 0;
}

void game_loop(int pontox1[],
                int pontoy1[],
                int pontox2[],
                int pontoy2[],
                int tipoVeiculo[],
                int distVeiculo[],
                short veiculo_valido[],
                STATUS_SAPO sapos[],
                int psx1[],
                int psx2[],
                int psy1[],
                int psy2[]) {

    /* INSTANCIAR SAPOS PARA TESTE DE FUNCOES */
    for (int i = 0; i < NUM_SAPOS; i++) {
    desenha_sapo(psx1[i],
            psx2[i],
            psy1[i],
            psy2[i],
            GREEN);
    }


    int indice_sapo = 0;
    sapos[indice_sapo] = ATIVO;

    int counter = 0;
    int estado = 0;
    while( sapos[indice_sapo] == ATIVO ) {
        if (estado) {
            if (estado == 1) {
                gotoxy(2, 30);
                printf("O SAPO MORREU");
                getch();
                estado = 0;
            } else if(estado == 2) {
                gotoxy(2, 30);
                printf("AS VIDAS ACABARAM");
                getch();
                estado = 0;
            }
        }

        Sleep(33.33);


        /* TESTE FILA DE CARROS */
        if (counter == 30 || counter == 15) {
            desenha_lista_veiculos(pontox1,
                           pontoy1,
                           pontox2,
                           pontoy2,
                           tipoVeiculo,
                           distVeiculo,
                           1,
                           veiculo_valido);
        }

        /* Testa Mata sapos para cada carro */
        for (int i = 0; i < MAX_VEICULOS; i++) {
            estado = mata_sapo(sapos, &indice_sapo, &psx1[indice_sapo], &psx2[indice_sapo], &psy1[indice_sapo], &psy2[indice_sapo],
                                                    pontox1[i], pontox2[i], pontoy1[i], pontoy2[i]);
        }


        if (counter == 30) {
            counter = 1;
        } else {
            counter++;
        }
    }


    desenha_borda(52, 12, 52 + 17, 16);
    gotoxy(54, 14);
    printf("O SAPO MORREU");

    gotoxy(1, Y_MAX - 2);


    return;
};
