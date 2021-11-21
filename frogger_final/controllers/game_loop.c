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
    bool *halt,
    ESTADO *estado);

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

    ESTADO estado = {
        .status = RUNNING,
        .indice_sapo = indice_sapo,
        .jogador = *jog,
        .lista_sapos = *lista_sapos,
        .lista_veiculos = *lista_veiculos,
    };

    inicializa_veiculos(estado.lista_veiculos, DIR);
    inicializa_sapos(estado.lista_sapos);

    ativa_sapo(&estado.lista_sapos[indice_sapo]);
    desenha_sapo(
        estado.lista_sapos[indice_sapo].envelope[0],
        estado.lista_sapos[indice_sapo].envelope[1],
        estado.lista_sapos[indice_sapo].cor);

    Beep(100, 150);
    Beep(400, 100);

    int counter = 0;
    bool halt = false;
    while (indice_sapo < NUM_SAPO && !halt) {
        /* 1 - Desenha veiculos nos frames determinados ------------------------------ */
        if (counter == 30 || counter == 15) {
            desenha_lista_veiculos(estado.lista_veiculos, false);
        }

        /* Impede que cursor fique piscando no meio da tela */
        gotoxy(X_MAX, Y_MAX);
        //Sleep(33.33);
        Sleep(10);
        #if true

        /* 2 - Captura acao do usuario ----------------------------------------------- */
        int action = capture_action();
        if (action) {
            handleAction(action,
                         &halt,
                         &estado);
        }

        /* Executa mata_sapo apenas nos frames onde o carro ou o sapo se move */
        if (is_render_frame(counter) || action) {
            mata_sapo(estado.lista_sapos, &estado.indice_sapo, estado.lista_veiculos);
            display_game_status(&estado.jogador, estado.indice_sapo);

            /* Verifica se sapo foi salvo */
            salva_sapo(&estado);
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

void handleAction(
    int action,
    bool *halt,
    ESTADO *estado) {
    switch (action) {
        case 6: {
            pausa(estado);
            salva_jogo(*estado);
            *halt = true;
        }

        break;
        case 7: {
            pausa(estado);
            desenha_lista_veiculos(estado->lista_veiculos, true);
            desenha_sapo(
                estado->lista_sapos[estado->indice_sapo].envelope[0],
                estado->lista_sapos[estado->indice_sapo].envelope[1], COR_FUNDO);
            le_jogo_salvo(estado, estado->jogador.nome);
            instancia_jogo(
                *estado,
                estado->lista_sapos,
                estado->lista_veiculos,
                &estado->jogador,
                &estado->indice_sapo);
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