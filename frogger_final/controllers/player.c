#include <stdbool.h>
#include <conio.h>

#include "../models/headers/models.h"
#include "../constants.h"

int capture_action() {
    if (kbhit()) {
        char c = getch();

        if (c == 'p') {
            return 6;
        } else if (c == 'c') {
            return 7;
        } else if (c == ESC) {
            return 5;
        }

        if ((int)c == ESPECIAL) {
            switch (getch()) {
                case SETA_CIMA:
                    return CIMA;
                    break;
                case SETA_BAIXO:
                    return BAIXO;
                    break;
                case SETA_ESQ:
                    return ESQ;
                    break;
                case SETA_DIR:
                    return DIR;
                    break;
            }
        }
    }
    return 0;
}

void pausa(ESTADO *estado) {
    gotoxy(1, Y_MAX + 1);
    printf("Digite o seu nome: ");
    scanf(" %s", &estado->jogador.nome);
}

void calcula_score(JOGADOR *jog) {
    gotoxy(1, Y_MAX + 1);
    /* --  ITEM A  ---------------------------------------------------------- */
    printf("Digite o seu nome: ");
    scanf(" %s", jog->nome);
    /* --  ITEM B  ---------------------------------------------------------- */
    jog->tempo_jogo = time(NULL) - jog->inicio_jogo;
    /* --  ITEM C  ---------------------------------------------------------- */
    jog->score = (10000 * jog->sapos_salvos) / jog->tempo_jogo;
    return;
}

void sair() {
    textcolor(WHITE);
    gotoxy(54, 14);
    printf("ATE MAIS TARDE!\n");
    Sleep(1500);
    gotoxy(42, 16);
    textcolor(WHITE);
    printf("Aperte qualquer tecla para encerrar...");
    getch();
    return;
}

