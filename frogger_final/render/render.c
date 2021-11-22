#include <conio2.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../models/headers/models.h"
#include "../constants.h"

/* --  INTERFACE  -------------------------------------------------------------------- */
void desenha_borda(int x_min, int y_min, int x_max, int y_max) {
    /*  x1, y1 : canto superior esquerdo da tela.
        x2, y2 : canto inferior direito da tela.
    */
    int i;
    textcolor(WHITE);
    gotoxy(x_min, y_min);
    for (i = x_min; i <= x_max; i++) {
        putch('=');
    }

    gotoxy(x_min, y_max);
    for (i = x_min; i < x_max; i++) {
        putch('=');
    }

    for (i = (y_min + 1); i < y_max; i++) {
        putchxy(x_min, i, '|');
        putchxy(x_max, i, '|');
    }
    return;
}


/* --  SAPO  ------------------------------------------------------------------------ */
void explosao(COORDENADA env1, COORDENADA env2) {
    int height = (env2.y - env1.y) + 1;
    int width = (env2.x - env1.x) + 1;

    textcolor(RED);

    for (int i = 0; i < height; i++) {
        gotoxy(env1.x, env1.y);

        for (int j = 0; j < width; j++) {
            // Handle render crop at x axis when out of boundary
            if (((env1.x + j) - 1) > X_MIN && (env1.x + j) < X_MAX) {
                putch('X');
            } else {
                gotoxy(env1.x + j, env1.y);
            }
        }
        env1.y += 1;
    }

    gotoxy(X_MAX, Y_MAX);
}

void desenha_sapo(COORDENADA pos1, COORDENADA pos2, COLORS color) {
    short x1 = pos1.x;
    short y1 = pos1.y;
    short x2 = pos2.x;
    short y2 = pos2.y;

    int height = (y2 - y1) + 1;
    int width = (x2 - x1) + 1;

    char *content[2] = {
        "  (00)  ",
        "\\^{  }^/"};

    textcolor(color);

    for (int i = 0; i < height; i++) {
        gotoxy(x1, y1);

        for (int j = 0; j < width; j++) {
            // Handle render crop at x axis when out of boundary
            /* impede que sapo seja desenhado fora da borda
             if (((x1 + j) - 1) > X_MIN && (x1 + j) < X_MAX) {
                putch(content[i][j]);
            } else {
                gotoxy(x1 + j, y1);
            } */

            putch(content[i][j]);
        }
        y1 += 1;
    }

    gotoxy(X_MAX, Y_MAX);

    return;
}


/* --  VEICULOS  ----------------------------------------------------------- */
void desenha_esporte(VEICULO carro, COLORS cor) {
    short x1 = carro.envelope[0].x;
    short y1 = carro.envelope[0].y;
    short x2 = carro.envelope[1].x;
    short y2 = carro.envelope[1].y;
    short width = x2 - x1 + 1;
    short height = y2 - y1 + 1;

    char *content[3] = {
        "o o ",
        "HHH>",
        "o o "};

    if(carro.dir == ESQ) {
        content[0] = " o o";
        content[1] = "<HHH";
        content[2] = " o o";
    }

    textcolor(cor);

    for (int i = 0; i < height; i++) {
        gotoxy(x1, y1);

        for (int j = 0; j < width; j++) {
            // Handle render crop at x axis when out of boundary
            if (((x1 + j) - 1) > X_MIN && (x1 + j) < X_MAX) {
                putch(content[i][j]);
            } else {
                gotoxy(x1 + j, y1);
            }
        }
        y1 += 1;
    }
}

void desenha_sedan(VEICULO carro, COLORS cor) {
    short x1 = carro.envelope[0].x;
    short y1 = carro.envelope[0].y;
    short x2 = carro.envelope[1].x;
    short y2 = carro.envelope[1].y;
    short width = x2 - x1 + 1;
    short height = y2 - y1 + 1;

    char *content[3] = {
        "  o  o ",
        "=||||||",
        "  o  o "};

    if(carro.dir == ESQ) {
        content[0] = " o  o  ";
        content[1] = "||||||=";
        content[2] = " o  o  ";
    }

    textcolor(cor);

    for (int i = 0; i < height; i++) {
        gotoxy(x1, y1);

        for (int j = 0; j < width; j++) {
            // Handle render crop at x axis when out of boundary
            if (((x1 + j) - 1) > X_MIN && (x1 + j) < X_MAX) {
                putch(content[i][j]);
            } else {
                gotoxy(x1 + j, y1);
            }
        }
        y1 += 1;
    }
}

void desenha_onibus(VEICULO carro, COLORS cor) {
    short x1 = carro.envelope[0].x;
    short y1 = carro.envelope[0].y;
    short x2 = carro.envelope[1].x;
    short y2 = carro.envelope[1].y;
    short width = x2 - x1 + 1;
    short height = y2 - y1 + 1;

    char *content[3] = {
        " oo     o ",
        "=|||||||(8",
        " oo     o "};

    if(carro.dir == ESQ) {
        content[0] = " o     oo ";
        content[1] = "8)|||||||=";
        content[2] = " o     oo ";
    }

    textcolor(cor);

    for (int i = 0; i < height; i++) {
        gotoxy(x1, y1);

        for (int j = 0; j < width; j++) {
            // Handle render crop at x axis when out of boundary
            if (((x1 + j) - 1) > X_MIN && (x1 + j) < X_MAX) {
                putch(content[i][j]);
            } else {
                gotoxy(x1 + j, y1);
            }
        }
        y1 += 1;
    }
}

void display_game_status(ESTADO estado, JOGADOR *jog, short indice_sapo) {
    textcolor(WHITE);

    gotoxy(X_MIN, Y_MIN - 2);
    if (NUM_SAPO - indice_sapo <= 1) {
        textcolor(RED);
    }
    short tempo_jogo = time(NULL) - jog->inicio_jogo;
    float score;
    if (tempo_jogo == 0) {
        score = 0;
    } else {
        score = (float)(10000 * jog->sapos_salvos) / (float)tempo_jogo;
    }
    printf("Sapos vivos: %d\n", NUM_SAPO - indice_sapo);
    gotoxy(X_MIN, Y_MIN - 1);
    printf("(P)ausa      (ESC)Sair");
    gotoxy(52, Y_MIN - 2);
    printf("Sapos salvos: %d", jog->sapos_salvos);
    gotoxy(56, Y_MIN - 1);
    printf("Fase: %d", estado.fase);
    //gotoxy( 50, Y_MIN - 1);
    //printf("Score: %8.2f", score);
    gotoxy(90, Y_MIN - 2);
    printf("Tempo de jogo: %3ds", tempo_jogo);
    gotoxy(90, Y_MIN - 1);
    printf("(C)arregar");

    gotoxy(X_MAX, Y_MAX);
}
