#include <conio2.h>

#include "../constants.h"
#include "../models/headers/initializers.h"
#include "../models/headers/models.h"
#include "../persistent_data/headers/progress.h"
#include "../render/render.h"
#include "headers/frog.h"
#include "headers/player.h"
#include "headers/vehicles.h"

void handleAction(
    int action,
    ESTADO *estado);
void display_vence_jogo(ESTADO *estado);
void display_perde_jogo();

bool is_render_frame(short f) {
    return (
        f == 10 ||
        f == 20 ||
        f == 30);
}

void ativa_sapo(SAPO *s) {
    s->envelope[0].x = DEFAULT_PLAYER_X;
    s->envelope[0].y = DEFAULT_PLAYER_Y;
    s->envelope[1].x = DEFAULT_PLAYER_X + 7;
    s->envelope[1].y = DEFAULT_PLAYER_Y + 1;
    s->status = ATIVO;
    return;
}

void game_loop(
    JOGADOR *jog,
    SAPO lista_sapos[]) {
    short indice_sapo = 0;

    VEICULO lista_veiculos[NUM_PISTAS][NUM_VEICULOS] = {0};

    ESTADO estado = {
        .fase = 1,
        .status = RUNNING,
        .indice_sapo = indice_sapo,
        .jogador = *jog,
        .lista_sapos = *lista_sapos,
        .lista_veiculos = {0},
    };

    int counter = 0;
    while (estado.status != HALT) {
        /* clear the screen */
        clrscr();
        /* Desenha a borda */
        desenha_borda(X_MIN, Y_MIN, X_MAX, Y_MAX);

        inicializa_sapos(estado.lista_sapos);
        for (int i = 0; i < NUM_PISTAS; i++) {
            switch (i) {
                case PISTA_1:
                    inicializa_veiculos(estado, estado.lista_veiculos[i], DIR, PISTA_1);
                    break;
                case PISTA_2:
                    inicializa_veiculos(estado, estado.lista_veiculos[i], DIR, PISTA_2);
                    break;
                case PISTA_3:
                    inicializa_veiculos(estado, estado.lista_veiculos[i], ESQ, PISTA_3);
                    break;
                case PISTA_4:
                    inicializa_veiculos(estado, estado.lista_veiculos[i], ESQ, PISTA_4);
                    break;
            }
        }
        ativa_sapo(&estado.lista_sapos[indice_sapo]);
        desenha_sapo(
            estado.lista_sapos[indice_sapo].envelope[0],
            estado.lista_sapos[indice_sapo].envelope[1],
            estado.lista_sapos[indice_sapo].cor);
        Beep(100, 150);
        Beep(400, 100);

        while (indice_sapo < NUM_SAPO && (estado.status == RUNNING)) {
            /* 1 - Desenha veiculos nos frames determinados ------------------------------ */

            if (counter == 10 || counter == 20 || counter == 30) {
                for (int i = 0; i < NUM_PISTAS; i++) {
                    desenha_lista_veiculos(estado.lista_veiculos[i], false);
                }
            }

            /* Impede que cursor fique piscando no meio da tela */
            gotoxy(X_MAX, Y_MAX);
            Sleep(30);

            /* 2 - Captura acao do usuario ----------------------------------------------- */
            int action = capture_action();
            if (action) {
                handleAction(action,
                             &estado);
            }

            /* Executa mata_sapo apenas nos frames onde o carro ou o sapo se move */
            if (is_render_frame(counter) || action) {
                int morreu;
                for (int i = 0; i < NUM_PISTAS; i++) {
                    mata_sapo(&estado, estado.lista_sapos, &estado.indice_sapo, estado.lista_veiculos[i]);
                }

                /* Verifica se sapo foi salvo */
                salva_sapo(&estado);

                display_game_status(estado, &estado.jogador, estado.indice_sapo);
            }

            if (counter == 30) {
                counter = 1;
            } else {
                counter++;
            }

        }  // FIM LOOP DA FASE

        /* WIN */
        if (estado.status == WIN) {
            calcula_score(&estado.jogador);

            display_vence_jogo(&estado);

            if (estado.status == WIN) {
                estado.fase++;
                estado.indice_sapo = 0;
                estado.jogador.sapos_salvos = 0;
                estado.jogador.score = 0;
                estado.jogador.inicio_jogo = time(NULL);
                estado.status = RUNNING;
            }

            /* LOOSE */
        } else if (estado.status == LOOSE) {
            display_perde_jogo();
            estado.indice_sapo = 0;
            estado.jogador.sapos_salvos = 0;
            estado.jogador.score = 0;
            estado.jogador.inicio_jogo = time(NULL);
            estado.status = RUNNING;
        }
    }  // FIM DO GAME_LOOP
}

void handleAction(
    int action,
    ESTADO *estado) {
    switch (action) {
        case EXIT: {
            sair();
            estado->status = HALT;
            break;
        }
        case PAUSE: {
            pausa(estado);
            salva_jogo(*estado);
            estado->status = HALT;
        }

        break;
        case LOAD: {
            pausa(estado);
            for (int i = 0; i < NUM_PISTAS; i++) {
                desenha_lista_veiculos(estado->lista_veiculos[i], true);
            }
            desenha_sapo(
                estado->lista_sapos[estado->indice_sapo].envelope[0],
                estado->lista_sapos[estado->indice_sapo].envelope[1], COR_FUNDO);
            le_jogo_salvo(estado, estado->jogador.nome);
            desenha_sapo(
                estado->lista_sapos[estado->indice_sapo].envelope[0],
                estado->lista_sapos[estado->indice_sapo].envelope[1],
                estado->lista_sapos[estado->indice_sapo].cor);
        } break;
        default:
            // Mover sapo
            move_sapo(&estado->lista_sapos[estado->indice_sapo], action);
            Beep(500, 10);
            Beep(2200, 5);
            break;
    }
}
