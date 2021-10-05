/*
 *  INF01202 - Algoritmos e Programacao
 *  Intituto de Informatica - UFRGS
 *  Material cedido pelo Prof. Dr. Gabriel Luca Nazar.
 *
 *  Descricao:
 *  Programa espera uma tecla ser pressionada e a imprime na tela
 *
 *  Como todos os programas de exemplo os comentarios usando '//' explicam as funcoes
 *  da plataforma e nao estariam presentes em um programa comum
 */

#include <stdio.h>

// incluida somente pela funcao Sleep
#include <windows.h>

// header que declara funcoes _kbhit() e _getch()
#include <conio.h>


int
main() {
    int stop = 0;

    printf("Digite uma tecla:\n");

    while (!stop) {
        /* se alguma entrada for detectada tenta ler byte por byte da entrada usando
         * _getch(), no caso comum somente um byte sera lido, porem teclas como as setas
         * do teclado geram multiplos byte de entrada */
        if (_kbhit()) {
            stop = 1;
            printf("Recebi ");

            while (_kbhit()) {
                int c = _getch();
                /*Exibe o valor de c em hexadecimal*/
                printf("0x%2x ", c);
            }

            printf("\n");
        }

        // 500 ms sleep
        Sleep(500);
    }

    return 0;
}
