#include "estruturas.h"

void salva_jogo(ESTADO estado) {
    char nome[TAM_MAX_NOME_JOGADOR] = {0};
    strcpy(nome, estado.jogador.nome);
    strcat(nome,".bin");

    FILE *f_estado = fopen(nome, "wb");
    if (f_estado == NULL) {
        fclose(f_estado);
        printf("Erro na escrita");
        getchar();
        return;  // ERRO
    }
    if (fwrite(&estado, sizeof(ESTADO), 1, f_estado) != 1) {
        fclose(f_estado);
        return;  // ERRO
    }
    fclose(f_estado);
    return;
}

int le_jogo_salvo(ESTADO *estado, char nome[]) {
    char _nome[TAM_MAX_NOME_JOGADOR] = {0};
    strcpy(_nome,nome);
    strcat(_nome,".bin");

    FILE *f_estado;
    f_estado = fopen(_nome, "rb");
    ESTADO buffer;

    if (f_estado == NULL) {
        fclose(f_estado);
        printf(
            "Erro ao carregar.\n"
            "Aperte para continuar");
        getchar();
        return 0;  // ERRO
    }

    if (fread(&buffer, sizeof(ESTADO), 1, f_estado) != 1) {
        if (!feof(f_estado)) {
            fclose(f_estado);
            printf(
                "Erro ao carregar.\n"
                "Aperte para continuar");
            getchar();
            return 0;  // ERRO
        }
    }
    *estado = buffer;
    fclose(f_estado);

    return 1;
}