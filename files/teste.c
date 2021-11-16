#include <stdio.h>

void abre_arquivo(FILE **arq) {
    *arq = fopen("arquivo.txt", "r");
}

void le_arquivo(FILE *arq) {
    char c;
    c = getc(arq);
    printf("%c", c);
    fclose(arq);
}

int main() {
    FILE *arquivo;

    abre_arquivo(arquivo);
    le_arquivo(arquivo);
    return 0;
}

/* 
Resposta:  pq o parametro esta passando  o endereco fisico do arquivo, 
mas as funcoes todas de arquivos esperam uma variavel que guarda um 
endereco fisico do arquivo  e nao o proprio endereco. 
*/