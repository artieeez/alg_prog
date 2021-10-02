#include <time.h> // necessaria para a função srand() e rand()
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Declaracao de Constantes */
#define VALOR_MAXIMO_COMPRAS 10000.00
#define NUMAC 4
#define ID_MIN 0
#define ID_MAX 50
#define VALOR_MAXIMO_PRECO 100
#define QUANTIDADE_MAXIMA_ACOES 10000

/* Declaracao function prototypes */
/* Controle de UI */
void clear_screen();
void flush_in();
void print_horizontal_line(char c, int width, int solid);
void print_padded_border(char c, int padding_size, int left);
void print_centered_string(char border_char, char *str, int width);
void print_cell(char *str, int width, char align);
/* Ordenar */
void swap(int* xp, int* yp);
void selectionSort(int arr[], int n);
/* Utilitarios */
int find_index(int key, int arr[], int n);

int main(void)
{
    /* Utilizado para gerar numeros aleatorios */
    srand(time(0));

    /*
        1 - INICIALIZACAO */

    /* Declaracao de variaveis */
    int compras = 0, opcao_selecionada, acoes_compradas;
    float acoes_compradas_total;
    int acao_index = NUMAC; // index invalido por padrao

    /* Declaracao e inicializacao de listas com informacoes das acoes */
    int codigo[NUMAC] = {0};        // guarda codigo das ações
    int qtade_inicial[NUMAC] = {0}; // guarda estoque inicial das ações
    int qtade_vendida[NUMAC] = {0}; // guarda unidades vendidas das ações , inicializada com 0.
    int disponivel_arr[NUMAC] = {0};
    float preco[NUMAC] = {0};       // guarda valor de venda das ações

    compras = 0,
    opcao_selecionada, acoes_compradas;
    int scanf_success = 0; // Usado para checar retorno de scanf

    /* Popula os seguintes vetores com valores aleatorios :
        <codigo[]>
        <preco[]>
        <qtdade_inicial[]>
        <disponivel_arr[]>
    */
    int valid;
    int j;
    for(int i = 0; i < NUMAC; i++) {
        do {
            valid = 1;
            preco[i] = (float)rand()/(float)(RAND_MAX/VALOR_MAXIMO_PRECO);
            codigo[i] = (int)(rand() / (double) RAND_MAX * (ID_MAX + 1));
            qtade_inicial[i] = (int)(rand() / (double) RAND_MAX * (QUANTIDADE_MAXIMA_ACOES + 1));
            disponivel_arr[i] = qtade_inicial[i];
            j = 0;
            while (valid && j < NUMAC) {
                if (codigo[i] == codigo[j] && i != j)
                    valid = 0;
                else if (preco[i] == preco[j] && i != j)
                    valid = 0;
                else if (qtade_inicial[i] == qtade_inicial[j] && i != j)
                    valid = 0;
                j++;
            }
        } while(!valid);
    }

    /* Coloca codigos em ordem */
    selectionSort(codigo, NUMAC);

    /*
        2 - COMPRA DE ACOES */

    /* While loop ate entrada ser valida */
    do
    {
        clear_screen();

        /* Apresentacao de quadro de acoes */
        printf("Compra %d\n\nCódigo Acao Disponível Valor(R$)\n", compras + 1);
        for (int i = 0; i < 4; i++)
        {
            printf("%-11d %-10d %.2f \n",
                   codigo[i],             // Codigo
                   disponivel_arr[i], // Disponivel
                   preco[i]);     // Valor
        }

        /* Obtencao de valores pelo usuario */
        printf("Selecione um codigo e quantidade a ser adquirida (Ex.: \"2 570\"):\n");
        scanf_success = scanf(" %d %d", &opcao_selecionada, &acoes_compradas);

        /* Descobre index da acao nos vetores atraves de seu codigo */
        acao_index = find_index(opcao_selecionada, codigo, NUMAC);

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
        else if (opcao_selecionada < 0 || opcao_selecionada > ID_MAX)
        { // II ERRO - opcao selecionada invalida
            clear_screen();
            printf("Opcao invalida. Selecione um numero entre %d e %d.\
                \nPressione enter para continuar.\n",
                    ID_MIN,
                    ID_MAX);
            opcao_selecionada = 0;
            acoes_compradas = 0;
            flush_in();
            getchar();
            continue;
        }
        else if (acoes_compradas > disponivel_arr[acao_index])
        { // III ERRO - quantidade de acoes nao disponivel
            clear_screen();
            printf("0 acoes compradas! Acao %d possui apenas %d acoes.\
                \nPressione enter para continuar.\n",
                   opcao_selecionada,
                   disponivel_arr[acao_index]);
            acoes_compradas = 0;
            flush_in();
            getchar();
            continue;
        }

        /*
            4 - FINALIZACAO DE COMPRA */

        /*  Registrar quantidade comprada e
            subtrair do estoque disponivel */
        qtade_vendida[acao_index] += acoes_compradas;
        disponivel_arr[acao_index] -= acoes_compradas;
        float valor_gasto_temp = acoes_compradas * preco[acao_index];
        acoes_compradas_total += valor_gasto_temp;

        clear_screen();
        if (acoes_compradas != 0)
        {
            printf("Secesso! Acoes compradas:\n%d %d  R$ %.2f\n",
                   opcao_selecionada,
                   acoes_compradas,
                   valor_gasto_temp);
        }
        printf("Sucesso!\nPressione enter para continuar.");
        acoes_compradas = 0;
        compras++;
        flush_in();
        getchar();
        clear_screen();
    } while (acoes_compradas_total < VALOR_MAXIMO_COMPRAS);

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
    print_centered_string(border_char, "RELATORIO DE VENDAS DO DIA ", table_width);
    print_horizontal_line(border_char, table_width, 0); // White space
    print_horizontal_line(border_char, table_width, 1); // Linha horizontal

    /* Cabecalho da tabela */
    char *header[3] = {
        // Uso de lista no printf p/ facilitar a formatacao
        "Codigo da Acao",
        "Quantidade",
        "Total faturado",
    };
    print_padded_border(border_char, table_padding, 1); // Padded border
    for (int i = 0; i < column_amount; i++)
    {
        print_cell(header[i], column_width, 'l');
    }
    print_padded_border(border_char, table_padding, 0); // Padded border
    print_horizontal_line(border_char, table_width, 1); // White space

    /* Confecao de quadro final */
    for (int i = 0; i < NUMAC; i++)
    {
        if (qtade_vendida[i] > 0) {
            print_padded_border(border_char, table_padding, 1); // Padded border
            printf("%-*d %-*dR$ %-*.2f",
                column_width - 1,
                codigo[i], // acao
                column_width,
                qtade_vendida[i], // Quantidade vendida
                column_width - 3,
                qtade_vendida[i] * preco[i]);   // Total faturado
            print_padded_border(border_char, table_padding, 0); // Padded border
        }   
    }
    print_horizontal_line(border_char, table_width, 1); // Linha horizontal

    /* Apresentacao de soma final */
    print_padded_border(border_char, table_padding, 1); // Padded border
    printf("%-*sR$ %-*.2f",
           column_width * 2,
           "TOTAL DE VENDAS DO DIA",
           column_width - 3,
           acoes_compradas_total);
    print_padded_border(border_char, table_padding, 0); // Padded border

    /* Apresentação da acao mais vendida */
    print_padded_border(border_char, table_padding, 1); // Padded border
    int acao_mais_vendida_index;
    int vendas_acao_mais_vendida_temp = 0;
    for (int i = 0; i < NUMAC; i++) {
        if (qtade_vendida[i] > vendas_acao_mais_vendida_temp) {
            acao_mais_vendida_index = i;
        }
    }
    printf("%-*s %-*.2d",
           column_width * 2,
           "CODIGO DA ACAO MAIS VENDIDA",
           column_width - 1,
           codigo[acao_mais_vendida_index]);
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


/* Ordenação por selecao */
void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
}

/* Acha o index de um codigo no arr */
int find_index(int key, int arr[], int n) {
    /* 
        Retorna o indice da acao no vetor, caso acao nao seja encontrada
        retorna o n (index invalido).
        Retornar o n quando a funcao nao obtive exito serve para
        testar a existencia da chave <key> no vetor <arr>.
        key   -> valor a ser buscado (codigo da acao)
        arr[] -> vetor com codigos
        n     -> tamanho do array
     */
    int i = 0;
    int index = n;
    while (index == n && i < n) {
        if (arr[i] == key) {
            index = i;
        }
        i++;
    }
    return index;
}