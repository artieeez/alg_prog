#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Declaracao de Constantes */
#define QUANTIDADE_DE_COMPRAS 5
#define QUANTIDADE_OPCOES 4

#define GERDAU_CODIGO 1
#define GERDAU_DISPONIVEL 2000
#define GERDAU_VALOR 4.00

#define PETROBRAS_CODIGO 2
#define PETROBRAS_DISPONIVEL 5000
#define PETROBRAS_VALOR 22.50

#define RENNER_CODIGO 3
#define RENNER_DISPONIVEL 4500
#define RENNER_VALOR 2.50

#define GRENDENE_CODIGO 4
#define GRENDENE_DISPONIVEL 500
#define GRENDENE_VALOR 1.2

/* Declaracao function prototypes */
void clear_screen();
void flush_in();
void print_horizontal_line(char c, int width, int solid);
void print_padded_border(char c, int padding_size, int left);
void print_centered_string(char border_char, char *str, int width);
void print_cell(char *str, int width, char align);

int main(void)
{
    /*
        1 - INICIALIZACAO */

    /* Declaracao de variaveis */
    int compras, opcao_selecionada, acoes_compradas;
    float acoes_compradas_total;

    /* Declaracao e inicializacao de listas com informacoes das acoes */
    const char *name_arr[QUANTIDADE_OPCOES] = {
        "Gerdau",
        "Petrobras",
        "Lojas Renner",
        "Grendene"};
    int disponivel_arr[QUANTIDADE_OPCOES] = {
        GERDAU_DISPONIVEL,
        PETROBRAS_DISPONIVEL,
        RENNER_DISPONIVEL,
        GRENDENE_DISPONIVEL};
    const float valor_arr[QUANTIDADE_OPCOES] = {
        GERDAU_VALOR,
        PETROBRAS_VALOR,
        RENNER_VALOR,
        GRENDENE_VALOR};
    int quantidade_vendida_arr[QUANTIDADE_OPCOES] = {[0 ... QUANTIDADE_OPCOES - 1] = 0};

    compras = 0, opcao_selecionada, acoes_compradas;
    int scanf_success = 0; // Usado para checar retorno de scanf

    /*
        2 - COMPRA DE ACOES */

    /* While loop ate entrada ser valida */
    while (compras < QUANTIDADE_DE_COMPRAS)
    {
        clear_screen();

        /* Apresentacao de quadro de acoes */
        printf("Compra %d de %d\n\nCódigo Opção        Disponível Valor(R$)\n", compras + 1, QUANTIDADE_DE_COMPRAS);
        for (int i = 0; i < 4; i++)
        {
            printf("%-6d %-12s %-10d %.2f \n",
                   i + 1,             // Codigo
                   name_arr[i],       // Opcao
                   disponivel_arr[i], // Disponivel
                   valor_arr[i]);     // Valor
        }

        /* Obtencao de valores pelo usuario */
        printf("Selecione um codigo e quantidade a ser adquirida (Ex.: \"2 570\"):\n");
        scanf_success = scanf(" %d %d", &opcao_selecionada, &acoes_compradas);

        /*
            3 - INPUT CHECK */
        if (!scanf_success)
        { // I ERRO - scanf nao obtem 2 valores
            clear_screen();
            printf("Entrada invalida. Insira o codigo e quantidade a ser adquirida!\
                \nEx.: \"2 570\"\nPressione enter para continuar.\n");
            opcao_selecionada = 0;
            acoes_compradas = 0;
            flush_in();
            getchar();
            continue;
        }
        else if (opcao_selecionada < 1 || opcao_selecionada > QUANTIDADE_OPCOES)
        { // II ERRO - opcao selecionada invalida
            clear_screen();
            printf("Opcao invalida. Selecione um numero entre 1 e %d.\
                \nPressione enter para continuar.\n",
                   QUANTIDADE_OPCOES);
            opcao_selecionada = 0;
            acoes_compradas = 0;
            flush_in();
            getchar();
            continue;
        }
        else if (acoes_compradas > disponivel_arr[opcao_selecionada - 1])
        { // III ERRO - quantidade de acoes nao disponivel
            clear_screen();
            printf("Ops! %s possui apenas %d acoes.\
                \nPressione enter para continuar.\n",
                   name_arr[opcao_selecionada - 1],
                   disponivel_arr[opcao_selecionada - 1]);
            opcao_selecionada = 0;
            acoes_compradas = 0;
            flush_in();
            getchar();
            continue;
        }

        /*
            4 - FINALIZACAO DE COMPRA */

        /*  Demonstação switch
            registrar quantidade comprada e
            subtrair do estoque disponivel */
        switch (opcao_selecionada)
        {
        case 1:
            quantidade_vendida_arr[0] += acoes_compradas;
            disponivel_arr[0] -= acoes_compradas;
            break;
        case 2:
            quantidade_vendida_arr[1] += acoes_compradas;
            disponivel_arr[1] -= acoes_compradas;
            break;
        case 3:
            quantidade_vendida_arr[2] += acoes_compradas;
            disponivel_arr[2] -= acoes_compradas;
            break;
        case 4:
            quantidade_vendida_arr[3] += acoes_compradas;
            disponivel_arr[3] -= acoes_compradas;
            break;
        }

        opcao_selecionada = 0;
        acoes_compradas = 0;
        compras++;
        clear_screen();
        printf("Sucesso!\nPressione enter para continuar.");
        flush_in();
        getchar();
        clear_screen();
    }

    /*
        APRESENTACAO DE RELATORIO FINAL */
    
    /* Informacoes sobre tabela */
    const char border_char = '*';
    const int table_padding = 4;
    const int column_width = 24;
    const int column_amount = 3;
    const int table_width = column_width * column_amount + table_padding * 2;

    /* Titulo da tabela */
    print_horizontal_line(border_char, table_width, 1); // Linha horizontal
    print_horizontal_line(border_char, table_width, 0); // White space
    print_centered_string(border_char, "STOCK MARKET", table_width);
    print_horizontal_line(border_char, table_width, 0); // White space
    print_horizontal_line(border_char, table_width, 1); // Linha horizontal

    /* Cabecalho da tabela */
    char *header[3] = {
        // Uso de lista no printf p/ facilitar a formatacao
        "Empresa",
        "Lotes vendidos",
        "Total faturado",
    };
    print_padded_border(border_char, table_padding, 1); // Padded border
    for (int i = 0; i < column_amount; i++)
    {
        print_cell(header[i], column_width, 'l');
    }
    print_padded_border(border_char, table_padding, 0); // Padded border
    print_horizontal_line(border_char, table_width, 1); // White space

    /* Declaracao e Inicializacao de variaveis p/ calculo final */
    int quantidade_total_vendida = 0;
    float total_faturado = 0;
    /* Confecao de quadro final e calculo final */
    for (int i = 0; i < QUANTIDADE_OPCOES; i++)
    {
        print_padded_border(border_char, table_padding, 1); // Padded border
        printf("%d.%-*s %-*dR$ %-*.2f",
               i + 1, // id da acao
               column_width - 3,
               name_arr[i], // acao
               column_width,
               quantidade_vendida_arr[i], // Quantidade vendida
               column_width - 3,
               quantidade_vendida_arr[i] * valor_arr[i]);   // Total faturado
        print_padded_border(border_char, table_padding, 0); // Padded border
        /* Calculo de soma final */
        quantidade_total_vendida += quantidade_vendida_arr[i];
        total_faturado += quantidade_vendida_arr[i] * valor_arr[i];
    }
    print_horizontal_line(border_char, table_width, 1); // Linha horizontal
    /* Apresentacao de soma final */
    print_padded_border(border_char, table_padding, 1); // Padded border
    printf("%-*sR$ %-*.2f",
           column_width * 2,
           "TOTAL DE VENDAS DO DIA",
           column_width - 3,
           total_faturado);
    print_padded_border(border_char, table_padding, 0); // Padded border
    /* Apresentação da media final */
    print_padded_border(border_char, table_padding, 1); // Padded border
    printf("%-*sR$ %-*.2f",
           column_width * 2,
           "MEDIA DAS VENDAS",
           column_width - 3,
           total_faturado / QUANTIDADE_DE_COMPRAS);
    print_padded_border(border_char, table_padding, 0); // Padded border
    print_horizontal_line(border_char, table_width, 1); // Linha horizontal
    return 0;
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

/* Limpa buffer de entrada */
void flush_in()
{
    int ch;
    do
    {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}

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
