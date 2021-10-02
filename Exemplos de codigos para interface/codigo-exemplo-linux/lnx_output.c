/*
 *  INF01202 - Algoritmos e Programacao 
 *  Intituto de Informatica - UFRGS
 *  Material cedido pelo Prof. Dr. Gabriel Luca Nazar.
 *
 *  Descricao:
 *  Imprime um padrao quadriculado na tela com cores alternadas e uma string que
 *  muda de posicao
 *  Este programa demonstra como usar codigos do terminal VT-100 para manipular o
 *  console, os codigos usados podem ser encontrados nos sites:
 *
 *  http://www.termsys.demon.co.uk/vtansi.htm
 *  http://wiki.bash-hackers.org/scripting/terminalcodes
 *
 *  Esses codigos sao strings na forma "\e<string>" onde \e representa o byte 0x1b ou
 *  o caractere ESC
 *
 *  Como todos os programas de exemplo os comentarios usando '//' explicam as funcoes
 *  da plataforma e nao estariam presentes em um programa comum
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * retorna terminal para as configuracoes de cores e cursor originais e limpa a
 * tela
 */
void
reset() {
    // codigo retorna terminal para estado anterior a execucao do programa
    printf("\ec");
    // codigo limpa a tela
    printf("\e[2J");
    // retorna cursor para origem
    printf("\e[H");
}

/*
 * Desenha um padrao quadriculado 4x4 com cores de fundo alternadas na tela,
 * esse padrao ocupa um espaco 60x20 na tela do console, cores de fundo sao
 * invertidas a cada frame
 */
#define DRAW_AREA_X 60
#define DRAW_AREA_Y 20
void
draw_quads(int frame) {
    char background_white[] = "\e[47m";
    char background_red[] = "\e[41m";
    char quad_chunk[] = "    ";

    // move cursor para posicao 0, 0
    printf("\e[H");

    /* desenha linha por linha do padrao, com cada coluna sendo desenhada em
     * cores alternadas */
    int i, j;
    for (i = 0; i < DRAW_AREA_Y; ++i) {
        int line_even = (i / 4) % 2 == 0;

        for (j = 0; j < DRAW_AREA_X / 4; ++j) {
            int col_even = j % 2 == 0;

            if (line_even ^ col_even)
                printf(frame % 2 ? background_white : background_red);
            else
                printf(frame % 2 ? background_red : background_white);

            printf(quad_chunk);
        }
        printf("\n");
    }
}

/*
 * Escreve string msg posicionando o primeiro caractere nas coordenadas (x, y),
 * a posicao (0, 0) esta no canto superior esquerdo da tela do terminal
 */
void
draw_text(char* msg, int x, int y) {
    // move cursor para posicao (x, y) na tela do terminal
    printf("\e[%d;%dH", x, y);

    // muda cor da fonte para branco e cor de fundo para preto
    printf("\e[37m\e[40m");

    printf(msg);
}

int
main() {
    /* configura a tela */
    printf("\e[2J");   // limpa a tela
    printf("\e[?25l"); // esconde o cursor
    printf("\e[H");    // move cursor para posicao 0,0 (Home)
    atexit(reset);     // registra callback para retornar terminal pro estado original

    /* desliga buffering em stdout para que mensagens sejam imprimidas na funcao
     * draw_text */
    setbuf(stdout, NULL);

    int framecount;
    for (framecount = 0; framecount < 30; ++framecount) {
        char msg[] = "Hello world!";

        draw_quads(framecount);
        draw_text(msg, (int) (framecount / 1.5), (int) (framecount / 3.0));

        // interrompe execucao do programa por 500ms
        usleep(500 * 1000);
    }
    
    return 0;
}
