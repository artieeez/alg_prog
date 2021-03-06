#ifndef MODELS
#define MODELS

#include <conio2.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../constants.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

typedef struct
{
    int x;
    int y;
} COORDENADA;

typedef struct
{
    char nome[TAM_MAX_NOME_JOGADOR];
    int sapos_salvos;
    time_t inicio_jogo;
    int tempo_jogo;
    int score;
} JOGADOR;

typedef struct
{
    COORDENADA envelope[2];
    STATUS_SAPO status;
    COLORS cor;
    DIRECAO_MOVIMENTO dir;
    int fase;
} SAPO;

typedef struct
{
    COORDENADA envelope[2];
    TIPO_VEICULO tipo;
    int distancia;
    DIRECAO_MOVIMENTO dir;
    int pista;
    short valido;
    int fase;
    VELOCIDADE velocidade;
} VEICULO;

typedef struct
{
    int fase;
    short indice_sapo;
    JOGADOR jogador;
    VEICULO lista_veiculos[NUM_PISTAS][NUM_VEICULOS];
    SAPO lista_sapos[NUM_SAPO];
    STATUS_JOGO status;
} ESTADO;

#endif
