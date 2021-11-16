#include <conio2.h>
#include <time.h>

#include "constants.h"
#include "estruturas.h"

#define NOME_ARQUIVO "FROGGERJog.txt"
#define MAX_RECORDS 5
#define NUM_TXT_COLUMNS 5

void divide_string(char str[], char *columns[NUM_TXT_COLUMNS], char separador);

/* Questão 1 */
int AbreArqJog(FILE *arqtxt) {
    arqtxt = fopen("teste.txt", "r");
    if (arqtxt == NULL) {
        printf("deu ruim");
        return 0;
    }

    return 1;
}

int LeArqTexto(FILE *arqtxt, JOGADOR lista_jogadores[]) {
    char linha[MAX_RECORDS][200] = {0};
    int line_count = 0;
    char linhaTeste[200] = {0};
    char name[20] = {0};
    char a[20] = {0};
    char b[20] = {0};
    char c[20] = {0};
    char d[20] = {0};
    FILE *f = fopen("nome.txt", "r");
    int cont = 0;
    fgets(linha[cont], 1, f);
    printf("%s", linha[line_count]);
    char *columns[NUM_TXT_COLUMNS] = {0};
    divide_string(linha[line_count], columns, '#');
    JOGADOR *jog = &lista_jogadores[line_count];
    *jog->nome = *columns[0];
    line_count = line_count + 1;
    cont++;

    fclose(arqtxt);
    return line_count;
}

void divide_string(char str[], char *columns[NUM_TXT_COLUMNS], char separador) {
    int word_count = 0;
    int j = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == separador || str[i] == '\n') {
            if (columns[word_count][j - 1] == ' ') {
                columns[word_count][j - 1] = '\0';
            }
            j = 0;
            word_count++;
        } else {
            columns[word_count][j] = str[i];
            j++;
        }
    }
}