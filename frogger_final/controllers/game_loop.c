#include <conio2.h>
#include "../constants.h"
#include "../models/headers/models.h"
#include "../models/headers/initializers.h"
#include "../render/render.h"
#include "../persistent_data/headers/progress.h"
#include "headers/frog.h"
#include "headers/vehicles.h"
#include "headers/player.h"

void display_game_status(JOGADOR *jog, short indice_sapo) {
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
    printf("(P)ausa");
    gotoxy(52, Y_MIN - 2);
    printf("Sapos salvos: %d", jog->sapos_salvos);
    //gotoxy( 50, Y_MIN - 1);
    //printf("Score: %8.2f", score);
    gotoxy(90, Y_MIN - 2);
    printf("Tempo de jogo: %3ds", tempo_jogo);
    gotoxy(90, Y_MIN - 1);
    printf("(C)arregar");

    gotoxy(X_MAX, Y_MAX);
}

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

void instancia_jogo(
    ESTADO estado,
    SAPO lista_sapos[],
    VEICULO lista_veiculos[],
    JOGADOR *jogador,
    short *indice_sapo) {
    for (int i = 0; i < NUM_SAPO; i++) {
        lista_sapos[i] = estado.lista_sapos[i];
    }
    for (int i = 0; i < NUM_VEICULOS; i++) {
        lista_veiculos[i] = estado.lista_veiculos[i];
    }
    *jogador = estado.jogador;
    *indice_sapo = estado.indice_sapo;
    return;
}

void game_loop(
    JOGADOR *jog,
    SAPO lista_sapos[],
    VEICULO lista_veiculos[]) {
    short indice_sapo = 0;
    ativa_sapo(&lista_sapos[indice_sapo]);
    desenha_sapo(
        lista_sapos[indice_sapo].envelope[0],
        lista_sapos[indice_sapo].envelope[1],
        lista_sapos[indice_sapo].cor);

    inicializa_veiculos(lista_veiculos, DIR);

    ESTADO estado = {
        .indice_sapo = indice_sapo,
        .jogador = *jog,
        .lista_sapos = *lista_sapos,
        .lista_veiculos = *lista_veiculos,
    };

    Beep(100, 150);
    Beep(400, 100);

    int counter = 0;
    bool halt = false;
    while (indice_sapo < NUM_SAPO && !halt) {
        if (counter == 30 || counter == 15) {
            desenha_lista_veiculos(lista_veiculos, false);
        }

        gotoxy(X_MAX, Y_MAX);
        //Sleep(33.33);
        Sleep(10);

#if true
        int action = capture_action();
        if (action) {
            switch (action) {
                case 6: {
                    ESTADO est = {
                        .indice_sapo = indice_sapo,
                        .jogador = *jog,
                        .lista_sapos = *lista_sapos,
                        .lista_veiculos = *lista_veiculos,
                    };

                    for (int i = 0; i < NUM_SAPO; i++) {
                        est.lista_sapos[i] = lista_sapos[i];
                    }
                    for (int i = 0; i < NUM_VEICULOS; i++) {
                        est.lista_veiculos[i] = lista_veiculos[i];
                    }

                    pausa(&est);
                    salva_jogo(est);
                    halt = true;
                }

                break;
                case 7: {
                    pausa(&estado);
                    desenha_lista_veiculos(lista_veiculos, true);
                    desenha_sapo(
                        lista_sapos[indice_sapo].envelope[0],
                        lista_sapos[indice_sapo].envelope[1], COR_FUNDO);
                    le_jogo_salvo(&estado, estado.jogador.nome);
                    instancia_jogo(
                        estado,
                        lista_sapos,
                        lista_veiculos,
                        jog,
                        &indice_sapo);
                    desenha_sapo(
                        lista_sapos[indice_sapo].envelope[0],
                        lista_sapos[indice_sapo].envelope[1],
                        lista_sapos[indice_sapo].cor);
                } break;
                default:
                    // Mover sapo
                    move_sapo(&lista_sapos[indice_sapo], action);
                    Beep(500, 10);
                    Beep(2200, 5);
                    break;
            }
        }
        /* Executa mata_sapo apenas nos frames onde o carro ou o sapo se move */
        if (is_render_frame(counter) || action) {
            mata_sapo(lista_sapos, &indice_sapo, lista_veiculos);
            display_game_status(jog, indice_sapo);
        }
#endif

        if (counter == 30) {
            counter = 1;
        } else {
            counter++;
        }
    }  // FIM DO GAME LOOP
    gotoxy(1, Y_MAX + 1);

    if (!halt) {
        calcula_score(jog);
        printf("Seu score final: %d\n", jog->score);
        getch();
    }
}
