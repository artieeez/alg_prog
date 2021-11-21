#ifndef CONSTANTS
#define CONSTANTS

#define TAM_MAX_NOME_JOGADOR 20
#define NUM_VEICULOS 3
#define NUM_SAPO 6
#define VEIC_SPEED 4
#define SAPO_SPEED_X 8
#define SAPO_SPEED_Y 2
#define PISTA_1_Y 10

#define X_MIN 12
#define X_MAX 108
#define Y_MIN 3
#define Y_MAX 28

#define DEFAULT_PLAYER_X 55
#define DEFAULT_PLAYER_Y 26

#define POS_INICIAL_SAPO_X 12
#define POS_INICIAL_SAPO_Y 27

typedef enum
// constantes dos valores das teclas.
{
    ESPECIAL = -32,
    SETA_ESQ = 75,
    SETA_DIR = 77,
    SETA_CIMA = 72,
    SETA_BAIXO = 80,
    ENTER = 13,
    ESC = 27
} TECLAS;

typedef enum
// constantes com o id de cada entidade do jogo
{
    COR_VEIC = RED,
    COR_SAPO = GREEN,
    COR_FUNDO = BLACK,
} CORES;

typedef enum
// constantes com o id de cada entidade do jogo
{
    ESPORTE = 0,
    SEDAN = 1,
    ONIBUS = 2,
} TIPO_VEICULO;

typedef enum {
    ESPERA = 1,
    ATIVO = 2,
    SALVO = 3,
    MORTO = 4
} STATUS_SAPO;

typedef enum {
    RUNNING = 1,
    LOOSE = 2,
    HALT = 3,
    WIN = 4
} STATUS_JOGO;

typedef enum {
    CIMA = 1,
    BAIXO = 2,
    ESQ = 3,
    DIR = 4
} DIRECAO_MOVIMENTO;

#endif
