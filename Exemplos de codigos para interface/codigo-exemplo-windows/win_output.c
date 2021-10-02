/*
 *  INF01202 - Algoritmos e Programacao 
 *  Intituto de Informatica - UFRGS
 *  Material cedido pelo Prof. Dr. Gabriel Luca Nazar.
 *
 *  Descricao:
 * Imprime um padrao quadriculado na tela com cores alternadas e uma string que
 * muda de posicao
 * Este programa demonstra como usar funcoes do Windows para manipular o console
 *
 * Como todos os programas de exemplo os comentarios usando '//' explicam as funcoes
 * da plataforma e nao estariam presentes em um programa comum
 */

#include <stdio.h>
#include <stdlib.h>

// Header para plataforma Windows, inclui varios headers necessarios para compilar
// programas no windows
#include <windows.h>


/*
 * Apaga todo o conteudo da tela do console, retorna 0 se houver erro em alguma
 * parte da funcao
 */
int
clear(HANDLE console) {
    COORD coord = {0, 0};
    DWORD written;
    DWORD console_size;
    CONSOLE_SCREEN_BUFFER_INFO info;

    // pega informacoes sobre buffer de saida do console, e.g. tamanho
    if (!GetConsoleScreenBufferInfo(console, &info)) {
        return 0;
    }

    console_size = info.dwSize.X * info.dwSize.Y;

    // escreve ' ' em todas posicoes da tela do console
    if (!FillConsoleOutputCharacterA(console, ' ', console_size, coord, &written)) {
        return 0;
    }

    // reset atributos dos caracteres escritos no console, e.g. cor da fonte e cor do
    // fundo, sublinhado
    if (!FillConsoleOutputAttribute(console, info.wAttributes, console_size, coord,
                                    &written)) {
        return 0;
    }

    // posiciona o cursor do console no canto superior esquerdo
    SetConsoleCursorPosition(console, coord);

    return 1;
}

/*
 * Desenha um padrao quadriculado 4x4 com cores de fundo alternadas na tela,
 * esse padrao ocupa um espaco 60x20 na tela do console, cores de fundo sao
 * invertidas a cada frame
 */
#define DRAW_AREA_X 60
#define DRAW_AREA_Y 30
void
draw_quads(HANDLE console, int frame) {
    // tipo CHAR_INFO define uma struct com um caractere e atributos de estilo, e.g,
    // cor da fonte e cor de fundo
    CHAR_INFO buf[DRAW_AREA_Y][DRAW_AREA_X];
    COORD buf_size = {DRAW_AREA_X, DRAW_AREA_Y};
    COORD initial = {0, 0};
    SMALL_RECT area_size = {0, 0, DRAW_AREA_X, DRAW_AREA_Y};

    int i, j;
    WORD BACKGROUND_WHITE = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
    /* inicializa buffer com linhas e colunas de tamanho 4, cada CHAR_INFO recebe
     * um ' ' e uma cor vermelha ou branca */
    for (i = 0; i < DRAW_AREA_Y; ++i) {
        int line_even = (i / 2) % 2 == 0;

        for (j = 0; j < DRAW_AREA_X; ++j) {
            int col_even = (j / 4) % 2 == 0;
            buf[i][j].Char.AsciiChar = ' ';

            if ((line_even && col_even) || (!line_even && !col_even))
                buf[i][j].Attributes = (frame % 2) ?
                    BACKGROUND_WHITE : BACKGROUND_RED;
            else
                buf[i][j].Attributes = (frame % 2) ?
                    BACKGROUND_RED : BACKGROUND_WHITE;
        }
    }

    // escreve 'buf' direto no console, na area comecando em 'initial'
    // e de tamanho 'area_size'
    WriteConsoleOutput(console, (CHAR_INFO *) buf, buf_size, initial, &area_size);
}

/*
 * Escreve a string msg posicionando o primeiro caractere nas coordenadas (x, y),
 * a posicao (0, 0) esta no canto superior esquerdo da tela do terminal
 */
void
draw_text(HANDLE output, char* msg, int x, int y) {
    COORD coord = {(SHORT)x, (SHORT)y};

    SetConsoleCursorPosition(output, coord);
    printf(msg);
}

int
main() {
    HANDLE console_out;
    int framecount;

    /* desliga buffering em stdout para que mensagens sejam imprimidas na
     * funcao draw_text */
    setbuf(stdout, NULL);

    // Referencia para buffer de saida padrao do console
    console_out = GetStdHandle(STD_OUTPUT_HANDLE);

    // testa se funcao conseguiu pegar referencia
    if (console_out == INVALID_HANDLE_VALUE || console_out == NULL) {
        fprintf(stderr, "ERR_GET_CONSOLE\n");
        exit(1);
    }

    if (!clear(console_out)) {
        fprintf(stderr, "ERR_CLEAR_CONSOLE\n");
        exit(1);
    }

    for (framecount = 0; framecount < 30; ++framecount) {
        char msg[] = "<-->";

        draw_quads(console_out, framecount);
        draw_text(console_out, msg, (int) (framecount / 1.5), (int) (framecount / 3.0));

        // interrompe execucao por 500ms
        Sleep(500);
    }

    return 0;
}
