#ifndef RENDER
#define RENDER

#include "../models/headers/models.h"

void desenha_borda(int x_min, int y_min, int x_max, int y_max);
void desenha_esporte(VEICULO carro, COLORS cor);
void desenha_sedan(VEICULO carro, COLORS cor);
void desenha_onibus(VEICULO carro, COLORS cor);
void explosao(COORDENADA env1, COORDENADA env2);
void desenha_sapo(COORDENADA pos1, COORDENADA pos2, COLORS color);
void display_game_status(ESTADO estado, JOGADOR *jog, short indice_sapo);

#endif