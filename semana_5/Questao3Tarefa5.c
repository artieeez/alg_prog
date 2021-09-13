#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* constantes */
#define TAMANHO_VETOR_STRING 100
#define QNT_PALAVRAS 10
#define TAMANHO_MAXIMO_PALAVRA 10

int main()
{
    /* Declaracoes e inicializacoes */
    char texto[TAMANHO_VETOR_STRING + 1] = {0};
    char palavra[TAMANHO_MAXIMO_PALAVRA + 1] = {0};
    int frequencias[TAMANHO_MAXIMO_PALAVRA] = {0};
    int i = 0, j;
    int tamanho_temp = 0;

    /* le o texto */
    puts("Forneca um texto:");
    gets(texto);
    printf("O texto digitado foi: ");
    puts(texto);

    /* Contabiliza as palavras */
    while (texto[i] != '\0' && i < TAMANHO_VETOR_STRING + 1)
    {
        while (texto[i] != ' ' && texto[i] != '\0')
        {
            palavra[j] = texto[i];
            i++;
            j++;
        }
        palavra[j] = '\0';
        j = 0;
        i++;

        tamanho_temp = strlen(palavra);
        if (tamanho_temp <= TAMANHO_MAXIMO_PALAVRA) // Evita erro de acesso
            frequencias[tamanho_temp - 1]++;
    }
    printf("\n");

    /* Imprime o vetor com as frequencias */
    for (i = 0; i < TAMANHO_MAXIMO_PALAVRA; i++)
    {
        printf("%2d palavras com %2d letras\n", frequencias[i], i + 1);
    }

    return 0;
}
