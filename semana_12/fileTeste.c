#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    FILE *f = fopen("teste.txt", "r");
    if (f == NULL) {
        printf("deu ruim");
        return 0;
    }

    char linha[200] = {0};
    fscanf(f, "%s", linha);
    bool eof = feof(f);

    fclose(f);
    return 0;
}