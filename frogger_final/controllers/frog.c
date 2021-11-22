#include "../colission/main.h"
#include "../constants.h"
#include "../models/headers/models.h"
#include "../render/render.h"

void move_sapo(SAPO *s, DIRECAO_MOVIMENTO dir) {
    // 1 - Pega nova coordinates
    COORDENADA tmp_pos1 = s->envelope[0];
    COORDENADA tmp_pos2 = s->envelope[1];
    switch (dir) {
        case CIMA:
            tmp_pos1.y -= SAPO_SPEED_Y;
            tmp_pos2.y -= SAPO_SPEED_Y;
            break;
        case BAIXO:
            tmp_pos1.y += SAPO_SPEED_Y;
            tmp_pos2.y += SAPO_SPEED_Y;
            break;
        case ESQ:
            tmp_pos1.x -= SAPO_SPEED_X;
            tmp_pos2.x -= SAPO_SPEED_X;
            break;
        case DIR:
            tmp_pos1.x += SAPO_SPEED_X;
            tmp_pos2.x += SAPO_SPEED_X;
            break;
    }

    // 2 - Pode mover?
    bool out_of_boundary = is_out_of_boundary(
        tmp_pos1,
        tmp_pos2);

    // 1 - Hit the border
    if (out_of_boundary) {
        return;
    }

    desenha_sapo(s->envelope[0], s->envelope[1], COR_FUNDO);
    // Update position
    s->envelope[0] = tmp_pos1;
    s->envelope[1] = tmp_pos2;
    desenha_sapo(s->envelope[0], s->envelope[1], s->cor);
    return;
}

void mata_sapo(ESTADO *estado, SAPO lista_sapos[], short *indice_sapo, VEICULO lista_veiculos[]) {
    SAPO *_sapo = &lista_sapos[*indice_sapo];

    /* --  ITEM A  ---------------------------------------------------------- */
    for (int i = 0; i < NUM_VEICULOS; i++) {
        if (testa_colisao(lista_veiculos[i], *_sapo)) {
            /* --  ITEM B.1  ------------------------------------------------ */
            explosao(
                _sapo->envelope[0],
                _sapo->envelope[1]);

            Beep(400, 100);
            Beep(100, 150);
            gotoxy(44, 14);
            textcolor(WHITE);
            printf("MAIS CUIDADO NA PROXIMA, QUE TAL?");
            gotoxy(X_MAX, Y_MAX);
            Sleep(1500);

            gotoxy(42, 15);
            textcolor(WHITE);
            printf("Aperte qualquer tecla para continuar");
            getch();
            gotoxy(44, 14);
            textcolor(COR_FUNDO);
            printf("MAIS CUIDADO NA PROXIMA, QUE TAL?");
            gotoxy(42, 15);
            printf("Aperte qualquer tecla para continuar");
            /* Apaga explosão */
            desenha_sapo(_sapo->envelope[0], _sapo->envelope[1], COR_FUNDO);

            _sapo->status = MORTO;
            _sapo->envelope[0].x = POS_INICIAL_SAPO_X;
            _sapo->envelope[1].x = POS_INICIAL_SAPO_X + 7;
            _sapo->envelope[0].y = POS_INICIAL_SAPO_Y;
            _sapo->envelope[1].y = POS_INICIAL_SAPO_Y + 1;

            if (*indice_sapo < NUM_SAPO - 1) {
                *indice_sapo += 1;
                SAPO *novo_sapo = &lista_sapos[*indice_sapo];
                novo_sapo->envelope[0].x = DEFAULT_PLAYER_X;
                novo_sapo->envelope[1].x = DEFAULT_PLAYER_X + 7;
                novo_sapo->envelope[0].y = DEFAULT_PLAYER_Y;
                novo_sapo->envelope[1].y = DEFAULT_PLAYER_Y + 1;
                desenha_sapo(novo_sapo->envelope[0], novo_sapo->envelope[1], COR_SAPO);
                Beep(100, 150);
                Beep(400, 100);
                return;
            } else {
                SAPO *novo_sapo = &lista_sapos[*indice_sapo];
                novo_sapo->envelope[0].x = DEFAULT_PLAYER_X;
                novo_sapo->envelope[1].x = DEFAULT_PLAYER_X + 7;
                novo_sapo->envelope[0].y = DEFAULT_PLAYER_Y;
                novo_sapo->envelope[1].y = DEFAULT_PLAYER_Y + 1;
                desenha_sapo(novo_sapo->envelope[0], novo_sapo->envelope[1], COR_SAPO);
                Beep(100, 150);
                Beep(400, 100);
                if (estado->jogador.sapos_salvos > 0) {
                    estado->status = WIN;
                } else {
                    estado->status = LOOSE;
                }
                return;
            }
        }
    }
    return;
}

void move_sapo_borda(SAPO *sapo, int indice) {
    sapo->envelope[0].x = X_MAX + 2;
    sapo->envelope[1].x = X_MAX + 9;

    sapo->envelope[0].y = Y_MIN + (2 * indice) + indice - 1;
    sapo->envelope[1].y = Y_MIN + (2 * indice) + indice;

    desenha_sapo(sapo->envelope[0], sapo->envelope[1], WHITE);
}

void salva_sapo(ESTADO *estado) {
    bool colide_com_borda_superiora = false;
    SAPO *sapo = &estado->lista_sapos[estado->indice_sapo];

    colide_com_borda_superiora = is_a_and_b_colliding_in_one_axis(
        sapo->envelope[0].y,
        2,
        0,
        Y_MIN + 2);

    if (colide_com_borda_superiora) {
        // Atualiza posição do sapo
        desenha_sapo(sapo->envelope[0], sapo->envelope[1], COR_FUNDO);
        move_sapo_borda(sapo, estado->indice_sapo + 1);

        /* Incrementa sapos salvos */
        estado->jogador.sapos_salvos++;

        /* Atualiza status sapo */
        sapo->status = SALVO;

        // Atualiza indice sapo
        estado->indice_sapo++;

        // SE último sapo
        if (estado->indice_sapo >= NUM_SAPO) {
            estado->status = WIN;
            return;
        }

        SAPO *novo_sapo = &estado->lista_sapos[estado->indice_sapo];
        novo_sapo->status = ATIVO;
        novo_sapo->envelope[0].x = DEFAULT_PLAYER_X;
        novo_sapo->envelope[1].x = DEFAULT_PLAYER_X + 7;
        novo_sapo->envelope[0].y = DEFAULT_PLAYER_Y;
        novo_sapo->envelope[1].y = DEFAULT_PLAYER_Y + 1;
        desenha_sapo(novo_sapo->envelope[0], novo_sapo->envelope[1], COR_SAPO);
        Beep(100, 150);
        Beep(400, 100);

        return;
    }
    return;
}
