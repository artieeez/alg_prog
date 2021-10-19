/*
TAREFA 10

Feito por:
Artur Webber de Oliveira
João Pedro Telles Fava


*/

#include <conio2.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define TAM_MAX_NOME_JOGADOR 20
#define NUM_VEICULOS 3
#define NUM_SAPO 6
#define VEIC_SPEED 2
#define SAPO_SPEED_X 8
#define SAPO_SPEED_Y 2
#define PISTA_1_Y 10

#define X_MIN 12
#define X_MAX 108
#define Y_MIN 3
#define Y_MAX 28

#define DEFAULT_PLAYER_X 50
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
#define QNT_TIPOS_VEIC 3

typedef enum
// constantes com o id de cada entidade do jogo
{
    ESPORTE = 0,
    SEDAN = 1,
    ONIBUS = 2,
} TIPO_VEICULO;
#define QNT_TIPOS_VEIC 3

typedef enum {
    ESPERA = 1,
    ATIVO = 2,
    SALVO = 3,
    MORTO = 4
} STATUS_SAPO;

typedef enum {
    CIMA = 1,
    BAIXO = 2,
    ESQ = 3,
    DIR = 4
} DIRECAO_MOVIMENTO;

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
    int tamanho;
    TIPO_VEICULO tipo;
    int distancia;
    DIRECAO_MOVIMENTO dir;
    int pista;
    short valido;
    int fase;
} VEICULO;

/* Prototipos */
void desenha_borda(int x_min, int y_min, int x_max, int y_max);
short desenha_veiculo(VEICULO carro, COLORS cor);
void explosao(COORDENADA env1, COORDENADA env2);
void inicializa_jogador(JOGADOR *jog);
void desenha_sapo(COORDENADA pos1, COORDENADA pos2, COLORS color);
void inicializa_sapos(SAPO lista_sapos[]);
void ativa_sapo(SAPO *s);
void game_loop(
    JOGADOR *jog,
    SAPO lista_sapos[],
    VEICULO lista_veiculos[]);

int main() {
    VEICULO lista_veiculos[NUM_VEICULOS];
    SAPO lista_sapos[NUM_SAPO];
    inicializa_sapos(lista_sapos);

    /* --  QUESTÃO 5  ------------------------------------------------------- */
    JOGADOR jog;
    inicializa_jogador(&jog);

    /* clear the screen */
    clrscr();
    /* Desenha a borda */
    desenha_borda(X_MIN, Y_MIN, X_MAX, Y_MAX);

    game_loop(
        &jog,
        lista_sapos,
        lista_veiculos);

    getch();
    return 0;
}

bool is_out_of_boundary(COORDENADA pos1, COORDENADA pos2) {
    short xc1 = pos1.x;
    short yc1 = pos1.y;
    short xc2 = pos2.x;
    short yc2 = pos2.y;

    short width = xc2 - xc1;
    short height = yc2 - yc1;

    bool a = yc1 <= Y_MIN;
    bool b = (xc1 + width) >= X_MAX + 1;
    bool c = (yc1 + height) >= Y_MAX + 1;
    bool d = xc1 <= X_MIN;

    return (a || b || c || d);
}

/* --  QUESTÃO 1  ----------------------------------------------------------- */
void desenha_esporte(VEICULO carro, COLORS cor) {
    short x1 = carro.envelope[0].x;
    short y1 = carro.envelope[0].y;
    short x2 = carro.envelope[1].x;
    short y2 = carro.envelope[1].y;
    short width = x2 - x1;
    short height = y2 - y1;

    char *content[3] = {
        "o o ",
        "HHH>",
        "o o "};

    textcolor(cor);

    for (int i = 0; i < height; i++) {
        gotoxy(x1, y1);

        for (int j = 0; j < width; j++) {
            // Handle render crop at x axis when out of boundary
            if (((x1 + j) - 1) > X_MIN && (x1 + j) < X_MAX) {
                putch(content[i][j]);
            } else {
                gotoxy(x1 + j, y1);
            }
        }
        y1 += 1;
    }
}

short desenha_veiculo(VEICULO carro, COLORS cor) {
    short out_of_boundary = (short)is_out_of_boundary(carro.envelope[0],
                                                      carro.envelope[1]);

    switch (carro.tipo) {
        case ESPORTE:
            desenha_esporte(carro, cor);
            break;
    }

    return out_of_boundary;
}

/* --  QUESTÃO 2  ----------------------------------------------------------- */
void desenha_lista_veiculos(VEICULO lista_veiculos[]) {
    for (int i = 0; i < NUM_VEICULOS; i++) {
        VEICULO *tmp_veiculo = &lista_veiculos[i];
        COORDENADA *tmp_envelope1 = &lista_veiculos[i].envelope[0];
        COORDENADA *tmp_envelope2 = &lista_veiculos[i].envelope[1];

        /* --  ITEM A  ------------------------------------------------------ */
        desenha_veiculo(*tmp_veiculo,
                        COR_FUNDO);

        /* --  ITEM B  ------------------------------------------------------ */
        if (lista_veiculos[i].dir == DIR) {
            tmp_envelope1->x += VEIC_SPEED;
            tmp_envelope2->x += VEIC_SPEED;
        } else if (lista_veiculos[i].dir == ESQ) {
            tmp_envelope1->x -= VEIC_SPEED;
            tmp_envelope2->x -= VEIC_SPEED;
        }

        /* --  ITEM C / ITEM D  --------------------------------------------- */
        tmp_veiculo->valido = desenha_veiculo(*tmp_veiculo,
                                              COR_VEIC);

        /* Reinicia posição do veículo */
        if (!tmp_veiculo->valido) {
            if (tmp_envelope1->x >= X_MAX && tmp_veiculo->dir == DIR) {
                tmp_envelope2->x -= tmp_envelope1->x - 1;
                tmp_envelope1->x = 1;
            } else if (tmp_envelope2->x <= X_MIN && tmp_veiculo->dir == ESQ) {
                tmp_envelope1->x += X_MAX;
                tmp_envelope2->x += X_MAX;
            }
        }
    }  // Fim for loop

    return;
}

/* --  QUESTÃO 3  ----------------------------------------------------------- */
bool is_a_and_b_colliding_in_one_axis(int a, int a_length, int b, int b_length) {
    return !(b > (a + a_length) || (b + b_length) < a);
}

short testa_colisao(VEICULO carro, SAPO s) {
    bool x_axis_colission = is_a_and_b_colliding_in_one_axis(
        carro.envelope[0].x,
        carro.envelope[1].x - carro.envelope[0].x,
        s.envelope[0].x,
        s.envelope[1].x - s.envelope[0].x);

    bool y_axis_colission = is_a_and_b_colliding_in_one_axis(
        carro.envelope[0].y,
        carro.envelope[1].y - carro.envelope[0].y,
        s.envelope[0].y,
        s.envelope[1].y - s.envelope[0].y);

    return (short)(x_axis_colission && y_axis_colission);
}

/* --  QUESTÃO 4  ----------------------------------------------------------- */
int mata_sapo(SAPO lista_sapos[], short *indice_sapo, VEICULO lista_veiculos[]) {
    SAPO *_sapo = &lista_sapos[*indice_sapo];

    /* --  ITEM A  ---------------------------------------------------------- */
    for (int i = 0; i < NUM_VEICULOS; i++) {
        if (testa_colisao(lista_veiculos[i], *_sapo)) {
            /* --  ITEM B.1  ------------------------------------------------ */
            explosao(
                _sapo->envelope[0],
                _sapo->envelope[1]);
            /* --  ITEM B.2  ------------------------------------------------ */
            _sapo->status = MORTO;
            _sapo->envelope[0].x = POS_INICIAL_SAPO_X;
            _sapo->envelope[1].x = POS_INICIAL_SAPO_X + 7;
            _sapo->envelope[0].y = POS_INICIAL_SAPO_Y;
            _sapo->envelope[1].y = POS_INICIAL_SAPO_Y + 1;

            /* --  ITEM B.3  ------------------------------------------------ */
            if (*indice_sapo <= NUM_SAPO - 1) {
                *indice_sapo += 1;
                return 1;
            } else {
                return 2;
            }
        }
    }
    return 0;
}

/* --  QUESTÃO 5  ----------------------------------------------------------- */
void inicializa_jogador(JOGADOR *jog) {
    /* --  ITEM A  ---------------------------------------------------------- */
    jog->sapos_salvos = 0;
    /* --  ITEM B  ---------------------------------------------------------- */
    jog->inicio_jogo = time(NULL);
    /* --  ITEM C  ---------------------------------------------------------- */
    jog->tempo_jogo = 0;
    /* --  ITEM D  ---------------------------------------------------------- */
    jog->score = 0;
    return;
}

/* --  QUESTÃO 6  ----------------------------------------------------------- */
void calcula_score(JOGADOR *jog) {
    /* --  ITEM A  ---------------------------------------------------------- */
    printf("Digite o seu nome: ");
    scanf(" %s", jog->nome);
    /* --  ITEM B  ---------------------------------------------------------- */
    jog->tempo_jogo = time(NULL) - jog->inicio_jogo;
    /* --  ITEM C  ---------------------------------------------------------- */
    jog->score = (1000 * jog->sapos_salvos) / jog->tempo_jogo;
    return;
}

/* --  RENDERS  ------------------------------------------------------------- */
void desenha_borda(int x_min, int y_min, int x_max, int y_max) {
    /*  x1, y1 : canto superior esquerdo da tela.
        x2, y2 : canto inferior direito da tela.
    */
    int i;
    gotoxy(x_min, y_min);
    for (i = x_min; i <= x_max; i++) {
        putch('=');
    }

    gotoxy(x_min, y_max);
    for (i = x_min; i < x_max; i++) {
        putch('=');
    }

    for (i = (y_min + 1); i < y_max; i++) {
        putchxy(x_min, i, '|');
        putchxy(x_max, i, '|');
    }
    return;
}

void explosao(COORDENADA env1, COORDENADA env2) {
    int height = (env2.y - env1.y) + 1;
    int width = (env2.x - env1.x) + 1;

    textcolor(RED);

    for (int i = 0; i < height; i++) {
        gotoxy(env1.x, env1.y);

        for (int j = 0; j < width; j++) {
            // Handle render crop at x axis when out of boundary
            if (((env1.x + j) - 1) > X_MIN && (env1.x + j) < X_MAX) {
                putch('X');
            } else {
                gotoxy(env1.x + j, env1.y);
            }
        }
        env1.y += 1;
    }

    gotoxy(X_MAX, Y_MAX);
}

void desenha_sapo(COORDENADA pos1, COORDENADA pos2, COLORS color) {
    short x1 = pos1.x;
    short y1 = pos1.y;
    short x2 = pos2.x;
    short y2 = pos2.y;

    int height = (y2 - y1) + 1;
    int width = (x2 - x1) + 1;

    char *content[2] = {
        "  (00)  ",
        "\\^{  }^/"};

    textcolor(color);

    for (int i = 0; i < height; i++) {
        gotoxy(x1, y1);

        for (int j = 0; j < width; j++) {
            // Handle render crop at x axis when out of boundary
            if (((x1 + j) - 1) > X_MIN && (x1 + j) < X_MAX) {
                putch(content[i][j]);
            } else {
                gotoxy(x1 + j, y1);
            }
        }
        y1 += 1;
    }

    gotoxy(X_MAX, Y_MAX);

    return;
}

/*  CONTROLLERS  --------------------------------------------------

*/
int capture_action() {
    if (kbhit()) {
        char c = getch();

        if (c == ESC) {
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

void get_coord_veic(COORDENADA env[], TIPO_VEICULO tipo, short x) {
    COORDENADA env1;
    COORDENADA env2;
    short width;
    switch (tipo) {
        case ESPORTE:
            width = 4;
            break;
    }
    env1.x = x;
    env2.x = x + width - 1;
    env1.y = PISTA_1_Y;
    env2.y = env1.y + 1;
    env[0] = env1;
    env[1] = env2;
    return;
}

void inicializa_veiculos(VEICULO lista_veiculos[], DIRECAO_MOVIMENTO dir) {
    TIPO_VEICULO tipo = ESPORTE;
    short posicao[NUM_VEICULOS] = {
        2, 50, 80
    };
    for(int i = 0; i < NUM_VEICULOS; i++) {
        VEICULO tmp;
        get_coord_veic(tmp.envelope, tipo, posicao[i]);
        tmp.tipo = ESPORTE;
        tmp.dir = DIR;
        tmp.tamanho = 4;
    }
    return;
}

void ativa_sapo(SAPO *s) {
    s->envelope[0].x = DEFAULT_PLAYER_X;
    s->envelope[0].y = DEFAULT_PLAYER_Y;
    s->envelope[1].x = DEFAULT_PLAYER_X + 7;
    s->envelope[1].y = DEFAULT_PLAYER_Y + 1;
    s->status = ATIVO;
    return;
}

/* --  GAME LOOP  ----------------------------------------------------------- */
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

    while (indice_sapo < NUM_SAPO) {
        desenha_lista_veiculos(lista_veiculos);

        int action = capture_action();
        if (action) {
            // Mover sapo
            move_sapo(&lista_sapos[indice_sapo], action);
        }

        mata_sapo(lista_sapos, &indice_sapo, lista_veiculos);
    }
}