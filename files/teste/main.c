#include <stdio.h>

int main(void) {
    FILE *f = NULL;
    if ((f = fopen("teste.txt", "r")) == NULL) {
        return 1;
    }
    char str[20] = { '\0' };
    char c = fgetc(f);
    if (c == 't') {
        printf("deu certo");
    } else {
        printf("erro");
    }
    fclose(f);
    getchar();
    return 0;
}