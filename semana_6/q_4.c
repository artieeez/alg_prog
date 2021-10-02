#include <time.h>    // necessaria para a função srand() e rand()
#include <stdlib.h>  //
#include <stdio.h>
#include <string.h>

/* Constantes */
#define N 6 // Numero de opcoes
#define NAME_MAX_LENGTH 21
#define NUM_MESES 12
#define VALOR_MAXIMO_VENDAS 100
#define INDEX_NOT_FOUND_DEFAULT -1
#define COLUMN_AMOUNT 3

void clear_screen();
int acha_indice_da_string(  char chave[],
                            char vetor_alvo[][NAME_MAX_LENGTH],
                            int tamanho_vetor);
void print_horizontal_line(char c, int width, int solid);
void print_padded_border(char c, int padding_size, int left);
void print_centered_string(char border_char, char *str, int width);
void print_cell(char *str, int width, char align);

int main(void) {
    srand(time(0));
    char user_input[NAME_MAX_LENGTH] = {0};
    float vendas[N][NUM_MESES] = {0};
    float soma[N] = {0};
    double soma_ano = 0;
    char acoes[N][NAME_MAX_LENGTH] = {
        "Gerdau",
        "Petrobras",
        "Lojas Renner",
        "Vivo",
        "Vale",
        "Metalsinos",
    };

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < NUM_MESES; j++) {
            vendas[i][j] = (
                (float) rand() / (float) RAND_MAX) * (VALOR_MAXIMO_VENDAS + 1);
        }
    }

    /* 1
    Leia um string do teclado  e retorne o índice desse string no arranjo Acoes.
    Se o string não existir retorne -1. */
    int acao_index = INDEX_NOT_FOUND_DEFAULT;
    do {
        printf("Digite o nome de um acao: ");
        gets(user_input);

        acao_index = acha_indice_da_string(user_input, acoes, N);

        clear_screen();
        if (acao_index < 0) {
            printf("Não foi possível encontrar a ação.\n");
        } else {
            printf("Índice da ação: %d\n", acao_index);
        }
    } while (acao_index == INDEX_NOT_FOUND_DEFAULT);
    
    
    /* 2
    Some e retorne o número de ações vendidas registrado no arranjo Vendas asso-
    ciado ao índice retornado em 3. Se for retornado -1 no item 3 de uma mensa-
    gem ao usuário. */
    printf("O número de acoes vendidas associadas ao indice 3 do vetor vendas são:\n");
    float soma3 = 0;
    for (int i = 0; i < NUM_MESES; i++) {
        printf("mes %2d: %10.2f\n", i + 1, vendas[3][i]);
        soma3 += vendas[3][i];
    }
    printf("Soma da acao associada ao indice 3 e: %.2f\n", soma3);

    /* 3
    Identifique a ação mais vendida no ano (use um vetor auxiliar para guardar
    resultados intermediários).  Zere todos os meses de venda deste produto na
    matriz. */
    int indice_acao_mais_vendida = 0;
    
    for (int i = 0; i < N; i++) {

        for (int j = 0; j < NUM_MESES; j++) {
            soma[i] += vendas[i][j];
        }

        if (soma[i] > soma[indice_acao_mais_vendida])
            indice_acao_mais_vendida = i;

        soma_ano += soma[i];
    }

    soma[indice_acao_mais_vendida] = 0;
    for (int i = 0; i < NUM_MESES; i++) {
        vendas[indice_acao_mais_vendida][i] = 0;
    }

    /* 4
    mostre o mesmo relatorio da semana passada, agora mostrando o codigo e o
    nome das ações lidas do arranjo de strings.  */
    /*
        APRESENTACAO DE RELATORIO FINAL */

    /* Informacoes sobre tabela */
    const char border_char = '*';
    const int table_padding = 4;
    const int column_width = 24;
    const int table_width = column_width * COLUMN_AMOUNT + table_padding * 2;

    /* Titulo da tabela */
    print_horizontal_line(border_char, table_width, 1); // Linha horizontal
    print_horizontal_line(border_char, table_width, 0); // White space
    print_centered_string(border_char, "RELATORIO DE VENDAS DO DIA ", table_width);
    print_horizontal_line(border_char, table_width, 0); // White space
    print_horizontal_line(border_char, table_width, 1); // Linha horizontal

    /* Cabecalho da tabela */
    char *header[COLUMN_AMOUNT] = {
        // Uso de lista no printf p/ facilitar a formatacao
        "Codigo da Acao",
        "Nome da Acao",
        "Total faturado",
    };
    print_padded_border(border_char, table_padding, 1); // Padded border
    for (int i = 0; i < COLUMN_AMOUNT; i++)
    {
        print_cell(header[i], column_width, 'l');
    }
    print_padded_border(border_char, table_padding, 0); // Padded border
    print_horizontal_line(border_char, table_width, 1); // White space

    /* Confecao de quadro final */
    for (int i = 0; i < N; i++)
    {
        print_padded_border(border_char, table_padding, 1); // Padded border
        printf("%-*d %-*sR$ %-*.2f",
            column_width - 1,
            i, // acao
            column_width,
            acoes[i], // Quantidade vendida
            column_width - 3,
            soma[i]);   // Total faturado
        print_padded_border(border_char, table_padding, 0); // Padded border
    }
    print_horizontal_line(border_char, table_width, 1); // Linha horizontal

    /* Apresentacao de soma final */
    print_padded_border(border_char, table_padding, 1); // Padded border
    printf("%-*sR$ %-*.2f",
           column_width * 2,
           "TOTAL DE VENDAS DO ANO",
           column_width - 3,
           soma_ano);
    print_padded_border(border_char, table_padding, 0); // Padded border

    /* Apresentação da acao mais vendida */
    print_padded_border(border_char, table_padding, 1); // Padded border
    printf("%-*s %-*.2d",
           column_width * 2,
           "CODIGO DA ACAO MAIS VENDIDA",
           column_width - 1,
           indice_acao_mais_vendida);
    print_padded_border(border_char, table_padding, 0); // Padded border
    print_horizontal_line(border_char, table_width, 1); // Linha horizontal
    return 0;

    return 0;
}


/* Acha indice de uma string num vetor bidimensional de char
*/
int acha_indice_da_string(  char chave[],
                            char vetor_alvo[][NAME_MAX_LENGTH],
                            int tamanho_vetor) {
    int indice = INDEX_NOT_FOUND_DEFAULT;
    int i = 0;
    while(indice == INDEX_NOT_FOUND_DEFAULT && i < tamanho_vetor) {
        if (!strcmp(chave, vetor_alvo[i])) {
            indice = i;
        }
        i++;
    };
    return indice;
}

/* Limpa a tela */
void clear_screen()
{
#ifdef _WIN32
    system("cls");
#endif

#ifdef linux
    system("clear");
#endif
}

/* Print da tabela */
/* Imprime linha horizontal */
void print_horizontal_line(char c, int width, int solid)
{
    if (solid)
    {
        for (int i = 0; i < width; i++)
        {
            printf("%c", c);
        }
    }
    else
    {
        printf("%c%*c", c, width - 1, c);
    }

    printf("\n");
}

/* Imprime a borda da tabela */
void print_padded_border(char c, int padding_size, int left)
{
    if (left)
    {
        printf("%-*c", padding_size, c);
    }
    else
    {
        printf("%*c\n", padding_size, c);
    }
}

/* Imprime string centralizada */
void print_centered_string(char border_char, char *str, int width)
{
    int str_length = strlen(str);
    int right_padding = width / 2 - str_length / 2;
    int left_padding = (str_length % 2 == 0)
                           ? right_padding
                           : right_padding - 1;
    printf("%-*c%s%*c\n",
           left_padding,
           border_char,
           str,
           right_padding,
           border_char);
}

/* Imprime cedula da tabela */
void print_cell(char *str, int width, char align)
{
    switch (align)
    {
    case 'l':
        printf("%-*s", width, str);
        break;

    case 'r':
        printf("%*s", width, str);
    }
}