/*
 *  INF01202 - Algoritmos e Programacao 
 *  Intituto de Informatica - UFRGS
 *  Material cedido pelo Prof. Dr. Gabriel Luca Nazar.
 *
 *  Descricao:
 *  Programa espera ate que uma tecla seja pressionada, imprime os bytes correspondentes
 *  a tecla pressionada
 *
 *  Como todos os programas de exemplo os comentarios usando '//' explicam as funcoes
 *  da plataforma e nao estariam presentes em um programa comum
 */

#include <stdio.h>
#include <stdlib.h>

// inclui declaracao de funcoes read, usleep
#include <unistd.h>

// inclui declaracao de funcoes de controle do driver do terminal
#include <termios.h>


/*
 * Tenta ler um byte da stdin, file descriptor 0. Caso tenha um byte
 * disponivel retorna este byte, caso contrario retorna -1
 */
int
poll_char() {
    int c;
    int read_ret = read(0, &c, 1);
    if (read_ret == 1)
        return c;
    else
        return -1;
}

/*
 * variavel global, guarda configuracao do driver do terminal antes da execucao
 * do programa, usada para retornar o terminal para a configuracao original
 * apos terminar a execucao
 */
static struct termios saved_conf;

/*
 * Callback usado para retornar o terminal para o estado original apos execucao
 * do programa
 */
void
reset_stdin() {
    tcsetattr(STDIN_FILENO, TCSANOW, &saved_conf);
}

int
main() {
    /* confere se stdin se refere a entrada de um terminal */
    if (!isatty(STDIN_FILENO)) {
        fprintf(stderr, "Not running in a terminal\n");
        exit(1);
    }

    // salva configuracao original do terminal e registra callback usado para
    // reverter mudancas no terminal
    tcgetattr(STDIN_FILENO, &saved_conf);
    atexit(reset_stdin);

    struct termios conf;
    tcgetattr(STDIN_FILENO, &conf);

    /* remove cannonical mode, echo, torna read() nao-bloqueante */
    conf.c_lflag &= ~(ECHO | ICANON);
    conf.c_cc[VMIN] = 0;
    conf.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &conf) == -1) {
        fprintf(stderr, "tcsetattr failed\n");
        exit(1);
    }
    
    printf("Press a key:\n");

    int stop = 0;
    while (!stop) {
        int c = poll_char();

        if (c != -1) {
            stop = 1;
            printf("Key: ");
            
            // le todos os bytes disponiveis no buffer de entrada
            while (c != -1) {
                printf("0x%2x ", c);
                c = poll_char();
            }
            
            printf("\n");
        }

        // interrompe execucao do programa por 500ms, tipo do argumento para funcao
        // usleep tem que ser um inteiro unsigned que possa armazenar no minimo o valor
        // 1000000, este argumento representa o intervalo em microssegundos que o
        // programa vai ser interrompido
        unsigned int interval = 500000;
        usleep(interval);
    }

    return 0;
}


        
