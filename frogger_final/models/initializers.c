#include "headers/models.h"
/* . */
#include "../constants.h"

void get_coord_veic(COORDENADA env[], TIPO_VEICULO tipo, short x, PISTA pista) {
    COORDENADA env1;
    COORDENADA env2;
    short width, height;
    switch (tipo) {
        case ESPORTE:
            width = 4;
            height = 3;
            break;
        case SEDAN:
            width = 7;
            height = 3;
            break;
        case ONIBUS:
            width = 10;
            height = 3;
            break;
    }
    env1.x = x;
    env2.x = x + width - 1;
    env1.y = PISTA_1_Y;
    env2.y = env1.y + height - 1;

    switch (pista) {
        case PISTA_1:
            env1.y = PISTA_1_Y;
            env2.y = env1.y + height - 1;
            break;
        case PISTA_2:
            env1.y = PISTA_2_Y;
            env2.y = env1.y + height - 1;
            break;
        case PISTA_3:
            env1.y = PISTA_3_Y;
            env2.y = env1.y + height - 1;
            break;
        case PISTA_4:
            env1.y = PISTA_4_Y;
            env2.y = env1.y + height - 1;
            break;
            return;
    }

    env[0] = env1;
    env[1] = env2;
}

void inicializa_veiculos(ESTADO estado, VEICULO lista_veiculos[], DIRECAO_MOVIMENTO dir, PISTA pista) {
    TIPO_VEICULO tipo = ESPORTE;
    short posicao[NUM_VEICULOS] = {0};

    switch (pista) {
        case PISTA_1:
            posicao[0] = 2;
            posicao[1] = 50;
            posicao[2] = 80;
            break;
        case PISTA_2:
            posicao[0] = 8;
            posicao[1] = 24;
            posicao[2] = 46;
            break;
        case PISTA_3:
            posicao[0] = 22;
            posicao[1] = 64;
            posicao[2] = 85;
            break;
        case PISTA_4:
            posicao[0] = 3;
            posicao[1] = 40;
            posicao[2] = 95;
            break;
    }

    for (int i = 0; i < NUM_VEICULOS; i++) {
        VEICULO tmp;
        if (i == 0) {
            tmp.tipo = SEDAN;
        } else if (i == 1) {
            tmp.tipo = ESPORTE;
        } else {
            tmp.tipo = ONIBUS;
        }
        get_coord_veic(tmp.envelope, tmp.tipo, posicao[i], pista);

        tmp.dir = dir;

        tmp.distancia = 0;
        tmp.pista = pista;
        tmp.valido = 1;
        tmp.fase = 0;

        if (estado.fase == 1) {
            tmp.velocidade = VEL_1;
        } else {
            tmp.velocidade = VEL_2;
        }

        switch (pista) {
        case PISTA_1:
            tmp.velocidade = tmp.velocidade - 1;
            break;
        case PISTA_2:
            tmp.velocidade = tmp.velocidade;
            break;
        case PISTA_3:
            tmp.velocidade = tmp.velocidade - 2;
            break;
        case PISTA_4:
            tmp.velocidade = tmp.velocidade -1;
            break;
    }

        lista_veiculos[i] = tmp;
    }
    return;
}

void inicializa_jogador(JOGADOR* jog) {
    jog->sapos_salvos = 0;
    jog->inicio_jogo = time(NULL);
    jog->tempo_jogo = 0;
    jog->score = 0;

    for (int i = 0; i < TAM_MAX_NOME_JOGADOR; i++) {
        jog->nome[i] = '\0';
    }
    return;
}

void inicializa_sapos(SAPO lista_sapos[]) {
    COORDENADA env1 = {
        .x = POS_INICIAL_SAPO_X,
        .y = POS_INICIAL_SAPO_Y,
    };
    COORDENADA env2 = env1;
    env2.x += 7;
    env2.y += 1;

    for (int i = 0; i < NUM_SAPO; i++) {
        SAPO tmp_s;
        tmp_s.envelope[0] = env1;
        tmp_s.envelope[1] = env2;
        tmp_s.status = ESPERA;
        tmp_s.cor = COR_SAPO;
        tmp_s.fase = 1;
        lista_sapos[i] = tmp_s;
    }
    return;
}
