#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PROFISSAO_LENGTH 30
#define MAX_CONTRIBUINTES 20
#define ARQ_CONTRIBUINTES "contribuintes.bin"

typedef struct TRABALHADOR {
    int codigo;
    char profissao[PROFISSAO_LENGTH];
    float taxaDesconto;
} TRABALHADOR;

void clear_screen();
void flush_in();

void preenche_arranjo(TRABALHADOR contribuintes[]);
void mostra_arranjo(TRABALHADOR contribuintes[]);
int salva_arranjo(char *fileName, TRABALHADOR contribuintes[]);
void filtra_dados(char *fileName, TRABALHADOR contribuintes[]);

int main(void) {
    TRABALHADOR contribuintes[MAX_CONTRIBUINTES] = {0};
    bool exit = false;
    char option = 0;

    /* --  Questao 6  --------------------------------------------- */
    while (!exit) {
        clear_screen();
        printf(
            "Escolha uma opcao:\n"
            "(P) preencher o arranjo\n"
            "(M) mostrar o arranjo\n"
            "(S) salvar em arquivo\n"
            "(C) carregar o arquivo\n"
            "(F) filtrar dados\n");
        option = getchar();
        flush_in();
        switch (option) {
            case 'p':
                preenche_arranjo(contribuintes);
                printf(
                    "Arranjo (p)reenchido com sucesso!\n"
                    "Aperte para continuar");
                getchar();
                break;
            case 'm':
                mostra_arranjo(contribuintes);
                printf("\nAperte para continuar");
                getchar();
                break;
            case 's':
                if (salva_arranjo(ARQ_CONTRIBUINTES, contribuintes)) {
                    printf(
                        "Dados (s)alvos com sucesso!\n"
                        "Aperte para continuar");
                } else {
                    printf(
                        "Falha ao salvar dados.\n"
                        "Aperte para continuar");
                }
                getchar();
                break;
            case 'c':
                filtra_dados(ARQ_CONTRIBUINTES, contribuintes);
                printf(
                    "Dados (c)arregados com sucesso!\n"
                    "Aperte para continuar");
                getchar();
                break;
            case 'f':
                printf(
                    "Dados (f)iltrados com sucesso!\n"
                    "Aperte para continuar");
                getchar();
                break;
            default:
                break;
        }
    }

    return 0;
}

/* --  Questao 2  --------------------------------------------- */
void preenche_arranjo(TRABALHADOR contribuintes[]) {
    TRABALHADOR a = {
        .codigo = 100,
        .profissao = "alfaiate",
        .taxaDesconto = 2.4};
    contribuintes[0] = a;

    TRABALHADOR b = {
        .codigo = 101,
        .profissao = "analista",
        .taxaDesconto = 10.8};
    contribuintes[1] = b;

    TRABALHADOR c = {
        .codigo = 200,
        .profissao = "antropologo",
        .taxaDesconto = 1.6};
    contribuintes[2] = c;

    TRABALHADOR d = {
        .codigo = 1600,
        .profissao = "domestico",
        .taxaDesconto = 8};
    contribuintes[3] = d;

    TRABALHADOR e = {
        .codigo = 2342,
        .profissao = "padeiro",
        .taxaDesconto = 5.5};
    contribuintes[4] = e;

    for (int i = 5; i < MAX_CONTRIBUINTES; i++) {
        TRABALHADOR empty = {0};
        contribuintes[i] = empty;
    }

    return;
}

/* --  Questao 2  --------------------------------------------- */
void mostra_arranjo(TRABALHADOR contribuintes[]) {
    char *headers[] = {
        "codigo",
        "profissao",
        "desconto",
    };
    printf("-------------------------------------------\n");
    printf("| %-12s| %-12s| %-12s|\n",
           headers[0],
           headers[1],
           headers[2]);
    printf("| %-12s| %-12s| %-12s|\n", "", "", "");
    int i = 0;
    while (contribuintes[i].codigo != 0) {
        printf("| %-12d| %-12s| %-12.2f|\n",
               contribuintes[i].codigo,
               contribuintes[i].profissao,
               contribuintes[i].taxaDesconto);
        i++;
    };
    printf("-------------------------------------------\n");
    return;
}

/* --  Questao 3  --------------------------------------------- */
int salva_arranjo(char *fileName, TRABALHADOR contribuintes[]) {
    int count = 0;
    FILE *f_contribuintes = fopen(fileName, "wb");
    if (f_contribuintes == NULL) {
        printf("Erro na escrita");
        getchar();
        return 0;  // ERRO
    }
    int i = 0;
    while (contribuintes[i].codigo != 0) {
        if (fwrite(&contribuintes[i], sizeof(TRABALHADOR), 1, f_contribuintes) != 1) {
            return 0;  // ERRO
        }
        count++;
        i++;
    };

    fclose(f_contribuintes);
    return count;
}

/* --  Questao 4  --------------------------------------------- */
void filtra_dados(char *fileName, TRABALHADOR contribuintes[]) {
    TRABALHADOR contBuffer[MAX_CONTRIBUINTES] = {0};
    FILE *f_contribuintes = fopen(fileName, "rb");
    if (f_contribuintes == NULL) {
        printf("Erro na leitura");
        getchar();
        return;  // ERRO
    }

    int i = 0;
    while (!feof(f_contribuintes)) { // enquanto nao for eof

        // Zera a posição no buffer
        contBuffer[i].codigo = 0;
        for (int j = 0; j < PROFISSAO_LENGTH; j++) {
            contBuffer[i].profissao[j] = '\0';
        }
        contBuffer[i].taxaDesconto = 0;
        contribuintes[i] = contBuffer[i];

        // Le um contribuinte
        if (fread(&contBuffer[i], sizeof(TRABALHADOR), 1, f_contribuintes) != 1) {
            return;  // ERRO
        }

        // Salva no arranjo
        if (contBuffer[i].taxaDesconto < 5) {
            contribuintes[i] = contBuffer[i];
            i++;
        }
    }

    // Zera as posições restantes do arranjo
    for(int j = 0; j < MAX_CONTRIBUINTES; j++) {
        contribuintes[i].codigo = 0;
        for (int j = 0; j < PROFISSAO_LENGTH; j++) {
            contribuintes[i].profissao[j] = '\0';
        }
        contribuintes[i].taxaDesconto = 0;
    }


    getchar();

    fclose(f_contribuintes);
}

/* Limpa a tela */
void clear_screen() {
#ifdef _WIN32
    system("cls");
#endif

#ifdef linux
    system("clear");
#endif
}

/* Limpa buffer de entrada */
void flush_in() {
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}