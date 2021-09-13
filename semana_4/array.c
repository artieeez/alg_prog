#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/* Declaracao function prototypes */
void flush_in();
void print_array(int *array);

/* Constantes */
#define ARRAY_SIZE 10

int main(void) {
    /* Inicializações */
    srand(time(NULL));
    int r = rand();
    int array[ARRAY_SIZE];
    int novo_valor;
    /* Preencher array com numeros aleatorios */
    for(int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 100;
    }
    print_array(array);
    /* Pede ao usuario novo valor */
    printf("\nInsira um novo valor: ");
    scanf(" %d", &novo_valor);
    /* Insire valor no array */
    for(int i = 0; i < ARRAY_SIZE - 1; i++) {
        array[i] = array[i + 1];
    }
    array[ARRAY_SIZE - 1] = novo_valor;
    print_array(array);
    /* Substitui itens de posicao par para o proprio index */
    for(int i = 0; i < ARRAY_SIZE; i += 2) {
        array[i] = i;
    }
    printf("\n");
    print_array(array);
    printf("\n");
    /* Calcula média de valores */
    float media_valores_array = 0;
    for(int i = 0; i < ARRAY_SIZE; i++) {
        media_valores_array += array[i];
    }
    media_valores_array /= ARRAY_SIZE;
    /* Calcula quantidade de valores maiores que a media */
    int itens_maiores_que_media = 0;
    for(int i = 0; i < ARRAY_SIZE; i++) {
        if (array[i] > media_valores_array) itens_maiores_que_media++;
    }
    /* Imprime resultado */
    printf("Numero de elementos do array com valor maior que a media: %d\n",
        itens_maiores_que_media);
    return 0;
}

/* Limpa buffer de entrada */
void flush_in()
{
    int ch;
    do
    {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}

void print_array(int *array) {
    for(int i = 0; i < ARRAY_SIZE; i++) {
        printf("%-5d", array[i]);
    }
}