#include "headers/models.h"
#include "../constants.h"

void get_coord_veic(COORDENADA env[], TIPO_VEICULO tipo, short x) {
    COORDENADA env1;
    COORDENADA env2;
    short width, height;
    switch (tipo) {
        case ESPORTE:
            width = 4;
            height = 3;
            break;
    }
    env1.x = x;
    env2.x = x + width - 1;
    env1.y = PISTA_1_Y;
    env2.y = env1.y + height - 1;
    env[0] = env1;
    env[1] = env2;
    return;
}

void inicializa_veiculos(ESTADO estado, VEICULO lista_veiculos[], DIRECAO_MOVIMENTO dir) {
    TIPO_VEICULO tipo = ESPORTE;
    short posicao[NUM_VEICULOS] = {
        2, 50, 80};
    for (int i = 0; i < NUM_VEICULOS; i++) {
        VEICULO tmp;
        get_coord_veic(tmp.envelope, tipo, posicao[i]);
        tmp.tipo = ESPORTE;
        tmp.dir = DIR;
        tmp.tamanho = 4;

        tmp.distancia = 0;
        tmp.pista = 0;
        tmp.valido = 1;
        tmp.fase = 0;

        if(estado.fase == 1) {
            tmp.velocidade = VEL_1;
        } else {
            tmp.velocidade = VEL_2;
        }

        lista_veiculos[i] = tmp;
    }
    return;
}

void inicializa_jogador(JOGADOR *jog) {
    jog->sapos_salvos = 0;
    jog->inicio_jogo = time(NULL);
    jog->tempo_jogo = 0;
    jog->score = 0;

    for(int i = 0; i < TAM_MAX_NOME_JOGADOR; i++) {
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


