//JOGO FROGGER ERIC D ARRIAGA(TURMA C) ISAAC BUENO(TURMA D).
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <windows.h>
#include <math.h>


#define FILA1 6
#define MAXIMO 10
#define NUM_SAPOS 6
#define NUM_VEICULOS 4
#define TAMX  7
#define TAMY  2
#define TAM  10
#define PASSO_FASE1 1

typedef enum
//CODIGOS DE TIPO DE CARRO.
{
    SPORT  = 4,
    ONIBUS = 7,
    SEDAN  = 6
}TIPOS;
typedef enum
//VALORES DAS TECLAS.
{
    ESPECIAL   = -32,
    SETA_ESQ   = 75,
    SETA_DIR   = 77,
    SETA_CIMA  = 72,
    SETA_BAIXO = 80,
    ENTER      = 13,
    ESC        = 27
}TECLAS;
typedef enum
//LIMITES DO MOVIMENTO DO SAPO.
{
    LIM_ESQ = 1,
    LIM_DIR = 70,
    LIM_CIMA  = 3,
    LIM_BAIXO = 25
}LIMITES_MOVIMENTO;
typedef enum
//MOLDURA.
{
    PAREDE_ESQ  = 1,
    PAREDE_DIR  = 75,
    TETO  = 3,
    CHAO = 25
}COORD_FRAME;
typedef enum
//COORDENADAS DO PLORE INICIAL DO SAPO.
{
    X1S_I = 37,
    Y1S_I = 24
}POSICOES_I_SAPO;
typedef enum
//CODIGOS DE STATUS DO SAPO.
{
    ESPERA = 1,
    ATIVO = 2,
    SALVO = 3,
    MORTO = 4
} STATUS_SAPO;
typedef enum
//CODIGOS DE DIRECOES.
{
    CIMA = 0,
    BAIXO = 1,
    ESQ = 2,
    DIR = 3
} DIRECAO_MOVIMENTO;
typedef struct
//DECLARACAO DO TIPO COOORDENADA.(conjunto de dois pontos).
{
    int x;
    int y;
} COORDENADA;
typedef struct
//DECLARACAO DO TIPO JOGADOR.
{
    char nome[TAM];
    int sapos_salvos;
    time_t inicioJogo; //tipo definido na bibliote time.h. inicialize com time(NULL)
    int tempoJogo;
    int score;
} JOGADOR;
typedef struct
//DECLARACAO DO TIPO SAPO.
{
    COORDENADA ponto;
    int tamanhoEmX;
    int tamanhoEmY;
    STATUS_SAPO status;
    COLORS cor;
    DIRECAO_MOVIMENTO dir; //indica que direcao o sapo vai
} SAPO;
typedef struct
//DECLARACAO DO TIPO VEICULO.
{
    COORDENADA envelope; //pontos do envelope do veiculo
    int tamanho;
    int tipo; //sedan, onibus, esporte - pode definir a enumeracao TIPO_VEICULO
    int distancia;
    DIRECAO_MOVIMENTO dir; //que direcao o veiculo vai
    int pista; //opcional se quiser tratr pista junto com o carro
    int valido; //opcional 1 se veiculo esta na area de jogo, 0 se nao
} VEICULO;
typedef struct
//DECLARACAO DO TIPO ESTADO.
{
    JOGADOR jog;
    int fase;
    SAPO sapos[NUM_SAPOS];
    VEICULO veiculos[NUM_VEICULOS];
}ESTADO;


double randBetween(double min, double max);

void gera_coordenadas(int distancias[], int coordenadas_x[], int tamanho);

void instancia_veiculos(VEICULO lista_veiculos[], int tipo);

void desenha_sport(int x, int y, int dir, int col_fora);

short desenha_veiculo(VEICULO veiculo, COLORS cor);

void desenha_lista_veiculos(VEICULO lista_veiculos[]);

void frame(void);

void plota_sapo (SAPO sapo);

void plota_sapo_morto (SAPO sapo);

void morte_sapo (SAPO sapo);

void testa_move (SAPO *sapo, int tecla);

void move_sapo (SAPO *sapo, int tecla);

short testa_colisao (SAPO sapo, VEICULO carro);

short testa_colisao_faixa(SAPO sapo, VEICULO lista_veiculos[]);

void plota_sapos_iniciais(SAPO sapos[]);

void cria_sapos (SAPO sapos[]);

void mostra_veiculo(VEICULO veiculo);

void mostra_sapo(SAPO sapo);

short testa_ativo(SAPO lista_sapos[]);

short salva_sapo(SAPO lista_sapo[]);

void mostra_jogador(JOGADOR jog);

void pausa(VEICULO veiculos[], SAPO sapos[], JOGADOR jog, int fase);

void loop_jogo(VEICULO lista_veiculos[],SAPO lista_sapos[], JOGADOR *jog);

void inicializa_jogador(JOGADOR *jog);

void calcula_escore(JOGADOR *jog);

int escreveArquivo(FILE *arq, ESTADO estado, char nome_arquivo[]);

int gravaArquivo(char nome_arquivo[], ESTADO buffer);

int criaArquivo (char nome[], ESTADO estado);

void instanciaEstado(ESTADO *estado);

int leArquivo(char nome_arquivo[], ESTADO *estado);


int salva_estado_jogo(ESTADO e);

int le_jogo_salvo(char nome_usuario[], ESTADO *estado);

void instancia_jogo(ESTADO estado, SAPO sapos[], VEICULO veiculos[], JOGADOR *jog);

int main()
{
    int cond = 0;
    char nome[TAM];
    ESTADO estado;
    SAPO sapos[NUM_SAPOS] = {0};
    VEICULO lista_veiculos[NUM_VEICULOS] = {0};
    JOGADOR jog;
    instancia_veiculos(lista_veiculos, SPORT);
    cria_sapos(sapos);
    inicializa_jogador(&jog);
    frame();

    gotoxy(80,14);
    printf("TECLE <1> PARA CARREGAR JOGO.");
    gotoxy(80,15);
    printf("TECLE <0> PARA COMECAR NOVO JOGO.");
    gotoxy(80,16);
    scanf("%i",&cond);
    gotoxy(80,14);
    printf("                                  ");
    gotoxy(80,15);
    printf("                                  ");
    gotoxy(80,16);
    printf("                                  ");


    if(cond)
    {
        gotoxy(80,14);
        printf("SEU NOME:");
        gotoxy(80,15);
        fflush(stdin);
        gets(nome);
        le_jogo_salvo(nome, &estado);
        instancia_jogo(estado, sapos, lista_veiculos, &jog);
    }

    gotoxy(20,14);
    printf("Pressione qualquer tecla para iniciar");
    getch();
    gotoxy(20,14);
    printf("                                      ");

    plota_sapos_iniciais(sapos);
    loop_jogo(lista_veiculos,sapos,&jog);
    gotoxy(1,27);
    return(0);
}

void instancia_jogo(ESTADO estado, SAPO sapos[], VEICULO veiculos[], JOGADOR *jog)
{
    int i;
    for(i=0;i<NUM_SAPOS;i++)
    {
        sapos[i] = estado.sapos[i];
    }
    for(i=0;i<NUM_VEICULOS;i++)
    {
        veiculos[i] = estado.veiculos[i];
    }
    *jog = estado.jog;
}
double randBetween(double min, double max)
//FUNCAO QUE GERA NUMERO ALEATORIO.
{
    return ((double)rand()/RAND_MAX) * (max - min) + min;
}
void gera_coordenadas(int distancias[], int coordenadas_x[], int tamanho)
//GERA UMA LISTA COM AS COORDENADAS DOS CARROS.
{
    int r;
    r = randBetween(5, 10);
    coordenadas_x[0] = r;

    //GERA AS DISTÂNCIAS COM VALORES ENTRE 10 E 20
    for(int i =0; i < NUM_VEICULOS; i++)
    {
        r = randBetween(10, 20);
        distancias[i] = r;
        if(i < NUM_VEICULOS-1)
        {
            //GERA AS COORDENADAS INICIAIS DOS CARROS = COORDENADA DO ANTERIOR + TAMANHO DO VEICULO + DISTANCIA GERADA
            coordenadas_x[i+1] = coordenadas_x[i] + tamanho + r;
        }
    }
}
void instancia_veiculos(VEICULO lista_veiculos[], int tipo) //por enquanto gera arranjos de um tipo de veiculo
//MONTA UMA LISTA DE VEICULOS.
{
    int distancias[NUM_VEICULOS];
    int coordenadas_x[NUM_VEICULOS];
    int tamanho = tipo;
    gera_coordenadas(distancias, coordenadas_x, tamanho);
    VEICULO veiculo;
    for(int i=0; i<NUM_VEICULOS; i++)
    {
        veiculo.envelope.x = coordenadas_x[i];
        veiculo.envelope.y = FILA1;
        veiculo.tipo = tipo;
        veiculo.distancia = distancias[i];
        veiculo.dir = ESQ;
        veiculo.tamanho = tamanho;

        lista_veiculos[i] = veiculo;
    }
}
void desenha_sport(int x, int y, int dir, int col_fora)
//PLOTA UM CARRO DO TIPO SPORT.
{
    char carro_esq[3][SPORT] = {{' ', 'O', ' ', 'O'},
                                {'<', 'H', 'H', 'H'},
                                {' ', 'O', ' ', 'O'}};//carro sport virado para esquerda

    char carro_dir[3][SPORT] = {{'O', ' ', 'O', ' '},
                                {'H', 'H', 'H', '>'},
                                {'O', ' ', 'O', ' '}};//carro sport virado para direita

    int i, j;

    switch(dir)
    {
    case ESQ:
        for(i=0; i<3; i++)
        {
            gotoxy(x, y+i);
            for(j=col_fora; j<SPORT; j++)
                printf("%c", carro_esq[i][j]);
        }
        break;

    case DIR:
        for(i=0; i<3; i++)
        {
            gotoxy(x, y+i);
            for(j=0; j<SPORT-col_fora; j++)
                printf("%c", carro_dir[i][j]);
        }
        break;

    }
}
short desenha_veiculo(VEICULO veiculo, COLORS cor)
//DESENHA UM VEICULO.
{
    int col_fora;
    textcolor(cor);

    //SE VEICULO COMPLETAMENTE DENTRO DA AREA DE JOGO
    if(veiculo.envelope.x>PAREDE_ESQ && (veiculo.envelope.x+veiculo.tipo) < PAREDE_DIR)
    {
        desenha_sport(veiculo.envelope.x, veiculo.envelope.y, veiculo.dir, 0);
        return 1;
    }

    switch(veiculo.dir)
    {
    case ESQ:
        //SE VEICULO PARCIALMENTE DENTRO DA AREA DE JOGO
        if(veiculo.envelope.x<=PAREDE_ESQ && (veiculo.envelope.x+veiculo.tipo) > PAREDE_ESQ)
        {
            col_fora = sqrt(veiculo.envelope.x*veiculo.envelope.x);
            if(veiculo.envelope.x<=0)
                col_fora = col_fora+2 ;
            desenha_sport(2, veiculo.envelope.y, ESQ, col_fora);
            return 1;
        }
        else
            return 0;
        break;

    case DIR:
        //SE VEICULO PARCIALMENTE DENTRO DA AREA DE JOGO
        if((veiculo.envelope.x+veiculo.tipo) >= PAREDE_DIR && veiculo.envelope.x < PAREDE_DIR)
        {
            col_fora = (veiculo.envelope.x+veiculo.tipo) - PAREDE_DIR;
            desenha_sport(veiculo.envelope.x, veiculo.envelope.y, ESQ, col_fora);
            return 1;
        }
        else
            return 0;
        break;
    }
}
void desenha_lista_veiculos(VEICULO lista_veiculos[])
//DESENHA OS VEICULOS DE UMA FAIXA.
{
    for(int i=0; i<NUM_VEICULOS; i++)
    {
        desenha_veiculo(lista_veiculos[i], BLACK);
        switch(lista_veiculos[i].dir)
        {
        case ESQ:
            lista_veiculos[i].envelope.x = lista_veiculos[i].envelope.x - PASSO_FASE1;

            if((lista_veiculos[i].envelope.x + SPORT) <=1)
            {
                lista_veiculos[i].envelope.x = lista_veiculos[i].envelope.x + PAREDE_DIR;
            }
            break;

        case DIR:
            lista_veiculos[i].envelope.x = lista_veiculos[i].envelope.x + PASSO_FASE1;

            if((lista_veiculos[i].envelope.x) >= PAREDE_DIR)
            {
                lista_veiculos[i].envelope.x = PAREDE_ESQ+1;
            }
            break;

        }

        desenha_veiculo(lista_veiculos[i], WHITE);
    }
}
void frame(void)
//FUNCAO QUE MONTA MOLDURA.
{
    int i;
    for (i = TETO - 1; i < PAREDE_DIR + 1; i++)//teto
    {
        gotoxy(i,TETO);
        printf("%c", 205);
    }
    for (i = TETO; i < CHAO + 1; i++)//parede esquerda
    {
        gotoxy(PAREDE_ESQ,i);
        printf("%c",186);
    }
    for (i = TETO; i < CHAO + 1; i++)//chao
    {
        gotoxy( PAREDE_DIR + 1,i);
        printf("%c",186);
    }
    for (i = TETO - 1; i < PAREDE_DIR + 1; i++)//parede direita
    {
        gotoxy(i,CHAO + 1);
        printf("%c",205);
    }
    //caracteres dos cantos da moldura de jogo
    gotoxy(PAREDE_ESQ,TETO);//superior esquerdo
    printf("%c",201);
    gotoxy(PAREDE_ESQ,CHAO +1);//inferior direito
    printf("%c",200);
    gotoxy(PAREDE_DIR + 1,CHAO + 1);//inferior direito
    printf("%c",188);
    gotoxy(PAREDE_DIR + 1,TETO);//superior direito
    printf("%c",187);

}
void plota_sapo (SAPO sapo)
//PLOTA UM SAPO.
{
    textcolor(sapo.cor);
    gotoxy(sapo.ponto.x,sapo.ponto.y);
    printf(" /%c_%c\\ " ,169,169);
    gotoxy(sapo.ponto.x,sapo.ponto.y+1);
    printf("(_\\ /_)");
    textcolor(WHITE);
}
void plota_sapo_morto (SAPO sapo)
//PLOTA UM SAPO MORTO.
{
    textcolor(RED);
    gotoxy(sapo.ponto.x,sapo.ponto.y);
    printf(" /X_X\\ ");
    gotoxy(sapo.ponto.x,sapo.ponto.y+1);
    printf("(_\\ /_)");
    textcolor(WHITE);
}
void morte_sapo (SAPO sapo)
//ANIMACAO DE UM SAPO MORTO.
{
    plota_sapo_morto (sapo);
    Sleep(500);
    sapo.cor = BLACK;
    plota_sapo(sapo);
}
void testa_move (SAPO *sapo, int tecla)
//TESTA SE O MOVIMENTO DO SAPO SERA VALIDO.
{
    switch (tecla)
    {
        case SETA_ESQ :
            if(((*sapo).ponto.x -1) > LIM_ESQ && (*sapo).ponto.y != Y1S_I && (*sapo).ponto.y != Y1S_I -1 )//condicao de limite da parede esquerda.
            {
                (*sapo).ponto.x = (*sapo).ponto.x -1;
                gotoxy(80,25);
                printf("ESQUERDA");
                (*sapo).dir = ESQ;
            }
            break;
        case SETA_DIR :
            if((*sapo).ponto.x+1 < LIM_DIR)  //condicao de limite da parede direita.
            {
                (*sapo).ponto.x = (*sapo).ponto.x+1;
                gotoxy(80,25);
                printf("DIREITA ");
                (*sapo).dir = DIR;
            }
            break;
       case SETA_CIMA :
            if((*sapo).ponto.y -1 > LIM_CIMA) //condicao de limite do teto.
            {
                (*sapo).ponto.y = (*sapo).ponto.y -1;
                gotoxy(80,25);
                printf("CIMA      ");
                (*sapo).dir = CIMA;
            }
            break;
        case SETA_BAIXO :
            if((*sapo).ponto.y +1 < LIM_BAIXO && (*sapo).ponto.y != Y1S_I -2) //condicao de limite do chao.
            {
                (*sapo).ponto.y = (*sapo).ponto.y +1;
                gotoxy(80,25);
                printf("BAIXO    ");
                (*sapo).dir = BAIXO;
            }
            break;
    }
}
void move_sapo (SAPO *sapo, int tecla)
//FUNCAO DE MOVIMENTO DO SAPO.
{
    (*sapo).cor = BLACK;
    plota_sapo((*sapo)); // apaga sapo.
    testa_move( sapo,tecla); // testa movimento do sapo.
    (*sapo).cor = GREEN;
    plota_sapo((*sapo)); // desenha novo sapo.
}

short testa_colisao (SAPO sapo, VEICULO carro)
//TESTA COLISAO ENTRE O SAPO E UM VEICULO.
{
    int x1Obj1, x2Obj1, y1Obj1, y2Obj1, x1Obj2, x2Obj2, y1Obj2, y2Obj2;

    x1Obj1 = sapo.ponto.x;
    x2Obj1 = sapo.ponto.x + 6;
    y1Obj1 = sapo.ponto.y;
    y2Obj1 = sapo.ponto.y + 1;

    x1Obj2 = carro.envelope.x;
    x2Obj2 = carro.envelope.x + (carro.tamanho -1);
    y1Obj2 = carro.envelope.y;
    y2Obj2 = carro.envelope.y + 2;

    if(x1Obj2 <= x2Obj1 && x2Obj2 >= x1Obj1 && y1Obj2 <= y2Obj1 && y2Obj2>= y1Obj1)
    {
        return 1;
    }
    else
        return 0;
}

short testa_colisao_faixa(SAPO sapo, VEICULO lista_veiculos[])
//TESTA SE UM SAPO COLIDE COM ALGUM VEICULO DE UMA FAIXA.
{
    int i;
    for(i=0;i<NUM_VEICULOS;i++)
    {
        if(testa_colisao(sapo,lista_veiculos[i]))
            return 1;
    }
    return 0;
}

int mata_sapo(SAPO lista_sapos[], VEICULO lista_veiculos[])
//TESTA COLISAO ENTRE SAPO E UMA LISTA DE VEICULOS E FAZ AS MANIPULACOES CASO OCORRA COLISAO.
{
    int i;
    for(i=0;i<NUM_SAPOS;i++)
    {
        if(lista_sapos[i].status == ATIVO) //testa com o sapo ativo da lista.
        {
            if(testa_colisao_faixa(lista_sapos[i],lista_veiculos))//colidiu.
            {
                gotoxy(80,24);
                textcolor(RED);
                printf("SAPO %i MORREU!!",i+1); //printa a morte do sapo.
                textcolor(WHITE);
                morte_sapo(lista_sapos[i]);     //animacao de morte do sapo.
                lista_sapos[i].status = MORTO;  //atualiza o status do sapo.
                if(i+1<NUM_SAPOS)//se tem mais sapos para ativar
                {
                    lista_sapos[i+1].status = ATIVO;
                    //plota um novo sapo nas coordenadas iniciais.
                    lista_sapos[i+1].cor = BLACK;
                    plota_sapo(lista_sapos[i+1]);
                    lista_sapos[i+1].ponto.x = X1S_I;
                    lista_sapos[i+1].ponto.y = Y1S_I;
                    lista_sapos[i+1].cor = GREEN;
                    plota_sapo(lista_sapos[i+1]);
                    return 1;//retorna 1
                }
                if(i == NUM_SAPOS-1)
                    return 2;
             }
        }
    }
}

void move_faixa (VEICULO lista_veiculos[], int velo_faixa)
//MOVE UMA LISATA DE VEICULOS NA FAIXA NA VELOCIDADE ENTRADA.
{
    desenha_lista_veiculos(lista_veiculos);
    Sleep(velo_faixa);
}
void plota_sapos_iniciais(SAPO sapos[])
//DESENHA OS SAPOS DO INICIO DE JOGO.
{
    int i;
    for(i=0;i<NUM_SAPOS;i++)
    {
        if(!(sapos[i].status==4))
            plota_sapo(sapos[i]);
    }
}
void cria_sapos (SAPO sapos[])
//CRIA A LISTA DE SAPOS COM OS DADOS INICIAIS DOS SAPOS.
{
    int i,x;
    x =  X1S_I;
    for(i=0;i<NUM_SAPOS;i++)
    {
        sapos[i].ponto.x =  x;
        sapos[i].ponto.y =  Y1S_I;
        sapos[i].tamanhoEmX = TAMX;
        sapos[i].tamanhoEmY = TAMY;
        sapos[i].status = 1;
        sapos[i].cor = BLUE;
        sapos[i].dir = CIMA;
        if(i == 0)
        {
            sapos[i].status = 2;
            sapos[i].cor = GREEN;
        }
        x = x - 7;
    }
}
void mostra_veiculo(VEICULO veiculo)
//PRINTA AS INFORMACOES DE UM VEICULO UMA A UMA.
{
    printf("\n X DO VEICULO: %d", veiculo.envelope.x);
    printf("\n Y DO VEICULO: %d", veiculo.envelope.y);
    printf("\n TAMANHO : %d",veiculo.tamanho);
    printf("\n DIRECAO: %d",veiculo.dir);
    printf("\n DISTANCIA: %d",veiculo.distancia);
    printf("\n TIPO: %d",veiculo.tipo);
    printf("\n Y DA PISTA: %d",veiculo.pista);
}
void mostra_sapo(SAPO sapo)
//PRINTA AS INFORMACOES DE UM SAPO UMA A UMA.
{
    printf("\n X DO SAPO: %d", sapo.ponto.x);
    printf("\n Y DO SAPO: %d", sapo.ponto.y);
    printf("\n TAMANHO EM X: %d",sapo.tamanhoEmX);
    printf("\n TAMANHO EM Y: %d",sapo.tamanhoEmY);
    printf("\n STATUS DO SAPO: %d",sapo.status);
    printf("\n COR DO SAPO: %d",sapo.cor);
    printf("\n DIRECAO DO SAPO: %d",sapo.dir);
}
short testa_ativo(SAPO lista_sapos[])
//RETORNA O INDICE DO SAPO COM STATUS ATIVO.
{
    int i;
    i=0;
    for(i=0;i<NUM_SAPOS;i++)
    {
        if(lista_sapos[i].status == 2)
            return i;
    }
}
short salva_sapo(SAPO lista_sapo[])
//AINDA NAO TERIMINADA(FUNCAO QUE SALVA O SAPO QUANDO SUA COORDENADA Y FOR IGUAL AO TETO +1).
{
        if(lista_sapo[testa_ativo(lista_sapo)].ponto.y == TETO + 1)
        {
            lista_sapo[testa_ativo(lista_sapo)].cor = YELLOW;
            plota_sapo(lista_sapo[testa_ativo(lista_sapo)]);
            gotoxy(80,24);
            textcolor(YELLOW);
            printf("SAPO ESTA SALVO!",testa_ativo(lista_sapo) + 1);
            Sleep(1000);
            lista_sapo[testa_ativo(lista_sapo)].cor = BLACK;
            plota_sapo(lista_sapo[testa_ativo(lista_sapo)]);
            lista_sapo[testa_ativo(lista_sapo)].status = SALVO;
            return 1;
        }
        else
            return 0;
}
void mostra_jogador(JOGADOR jog)
//PRINTA AS INFORMACOES DE UM JOGADOR UMA A UMA.
{
    gotoxy(1, 33);
    printf("\n\nEstatisticas do jogador %s:\n", jog.nome);
    printf(" SAPOS SALVOS: %d\n", jog.sapos_salvos);
    printf(" TEMPO DE JOGO: %d s\n", jog.tempoJogo);
    printf(" SCORE: %d\n", jog.score);
}

void pausa(VEICULO veiculos[], SAPO sapos[], JOGADOR jog, int fase)
//DENTRO DO LOOP DE JOGO QUANDO TECLA P É ATIVADA SALVA AS INFORMACOES DE ESTADO DE JOGO EM UM ARQUIVO BINARIO.
{
    FILE *arq;
    ESTADO e;
    int i;

    gotoxy(80,8);
    printf("INSIRA SEU NOME:");
    gotoxy(80,9);
    gets(jog.nome);
    gotoxy(80,8);
    printf("                ");
    gotoxy(80,9);
    printf("                ");
    e.fase = fase;
    e.jog = jog;
    for(i=0; i<NUM_SAPOS; i++)
    {
        e.sapos[i] = sapos[i];
    }
    for(i=0;i<NUM_VEICULOS;i++)
    {
        e.veiculos[i] = veiculos[i];
    }
    salva_estado_jogo(e);
}
void loop_jogo(VEICULO lista_veiculos[],SAPO lista_sapos[], JOGADOR *jog)
//LOOP DE JOGO.
{
    int cond;
    cond = 0;
    char tecla = 'o'; //para interação.
    do{
        move_faixa(lista_veiculos,50);
        fflush(stdin);
        if(kbhit())
        {
            fflush(stdin);
            tecla = getch();
            if(tecla == 'p' || tecla == 'P')
            {
                pausa(lista_veiculos,lista_sapos,*jog,1);
            }
            if(tecla == ESPECIAL)
            {
                tecla = getch();
                move_sapo(&lista_sapos[testa_ativo(lista_sapos)], tecla);//chamada da funcao move sapo com as coordenadas e tecla especifica
            }
        }
        if(mata_sapo(lista_sapos,lista_veiculos) == 2)
        {
            cond = 1;
            clrscr();
            frame();
            gotoxy(32,14);
            textcolor(MAGENTA);
            printf("FIM DE JOGO!");
            Sleep(1500);
            textcolor(WHITE);
        }
    }while(tecla != ESC && cond != 1);
}
void inicializa_jogador(JOGADOR *jog)
//DADOS INICIAIS DE UM JOGADOR.
{
    (*jog).sapos_salvos = 0;
    (*jog).inicioJogo = time(NULL);
    (*jog).tempoJogo = 0;
    (*jog).score = 0;
}
void calcula_escore(JOGADOR *jog)
//A PARTIR DE UM JOGADOR RETORNA SUA PONTUACAO.
{
    gotoxy(1, 32);
    printf("Digite seu nome: ");
    gets((*jog).nome);
    (*jog).tempoJogo = time(NULL) - (*jog).inicioJogo;
    (*jog).score = (*jog).tempoJogo / (*jog).sapos_salvos;
}




/*FUNCOES DE MANIPULACAO DE ARQUIVOS BINARIOS*/



int escreveArquivo(FILE *arq, ESTADO estado, char nome_arquivo[])
{
    if(fwrite(&estado, sizeof(ESTADO), 1, arq))
    {
        return 1;
    }
    else
    {
        printf("Erro na escrita!");
        return 0;
    }
}
int gravaArquivo(char nome_arquivo[], ESTADO buffer)
//GRAVA
{
    FILE *arq;
    arq = fopen(nome_arquivo, "wb");
    if(fwrite(&buffer, sizeof(ESTADO), 1, arq))
    {
        fclose(arq);
        return 1;
    }
    else
    {
        printf("erro na escrita!");
        return 0;
    }


}

int leArquivo(char nome_arquivo[], ESTADO *estado)
{
    FILE *arq;
    arq = fopen(nome_arquivo, "rb");
    ESTADO buffer;

    if(arq)
    {
      if(fread(&buffer, sizeof(ESTADO), 1, arq)==1)
      {
        *estado = buffer;
        fclose(arq);
        return 1;
      }
      else
      {
        printf("Erro leitura!!");
        return 0;
      }
    }
    else
    {
        printf("\nErro de leitura");
        fclose(arq);
        return 0;
    }
}

int criaArquivo (char nome[], ESTADO estado)
{
    FILE *arq;
    arq = fopen(nome, "wb");
    if(arq==0)
    {
        printf("Erro na criacao");
        return 0;
    }
    else
    {
        fclose(arq);
        gravaArquivo(nome, estado);
        return 1;
    }
}

int salva_estado_jogo(ESTADO e)
{
    char nome[TAM];
    strcpy(nome,e.jog.nome);
    strcat(nome,".bin");
    criaArquivo(nome, e);
}

int le_jogo_salvo(char nome_usuario[], ESTADO *estado)
{
    FILE *arq;
    char nome[TAM];
    strcpy(nome,nome_usuario);
    strcat(nome,".bin");
    leArquivo(nome, estado);




}











