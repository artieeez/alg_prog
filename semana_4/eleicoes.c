#include <stdlib.h>
#include <stdio.h>

/* Declaracao function prototypes */
void clear_screen();
void flush_in();
void print_horizontal_line(int width, int solid);
void print_padded_border(int padding_size, int left);
void print_centered_string(char *str, int width);
void print_cell(char *str, int width, char align);
void print_table(int *vote_count);

/* Constantes */
#define TABLE_CHAR '*'
#define COLUMN_WIDTH 10
#define COLUMN_AMOUNT 4
#define TABLE_PADDING 4
const int TABLE_WIDTH = COLUMN_WIDTH * COLUMN_AMOUNT + TABLE_PADDING * 2;

/* Macros */
#define ARRAY_SIZE(x) ( sizeof(x) / sizeof((x)[0]) )

int main(void) {
    int voto = 5;
    char continuar = 's';
    int vote_count[4] = {0, 0, 0, 0};
    while(continuar == 's') {
        
        print_table(&vote_count);

        /* 
            Coleta do voto */
        printf("\nDigite o numero da chapa e aperte ENTER:\n");
        scanf(" %d", &voto);
        flush_in();
        
        /* 
            Voto invalido handler */
        if (voto < 0 || voto > 3) {
            clear_screen();
            printf("VOTO INVALIDO - Aperte enter para continuar.\n", voto);
            getchar();
            continue;
        }
        vote_count[voto]++;

        /* 
            Continuar? */
        do {
            clear_screen();
            printf("VOTOU EM %d\nContinuar votando? (s) para Sim, (n) para nao.\n", voto);
            scanf(" %c", &continuar);
        } while(continuar != 's' && continuar != 'n');
        voto = 5;
    }

    
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
void print_horizontal_line(int width, int solid)
{
    if (solid)
    {
        for (int i = 0; i < width; i++)
        {
            printf("%c", '*');
        }
    }
    else
    {
        printf("%c%*c", '*', width - 1, '*');
    }

    printf("\n");
}

/* Imprime a borda da tabela */
void print_padded_border(int padding_size, int left)
{
    if (left)
    {
        printf("%-*c", padding_size, '*');
    }
    else
    {
        printf("%*c\n", padding_size, '*');
    }
}

/* Imprime string centralizada */
void print_centered_string(char *str, int width)
{
    int str_length = strlen(str);
    int right_padding = width / 2 - str_length / 2;
    int left_padding = (str_length % 2 == 0)
                           ? right_padding
                           : right_padding - 1;
    printf("%-*c%s%*c\n",
           left_padding,
           '*',
           str,
           right_padding,
           '*');
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

/* Imprime tabela */
void print_table(int *vote_count) {
    clear_screen();
        print_horizontal_line(TABLE_WIDTH, 1);
        print_horizontal_line(TABLE_WIDTH, 0);
        print_centered_string("VOTACAO", TABLE_WIDTH);
        print_horizontal_line(TABLE_WIDTH, 0);
        print_horizontal_line(TABLE_WIDTH, 1);

        print_padded_border(TABLE_PADDING, 1); // Padded border
        print_cell("Em branco", COLUMN_WIDTH, 'r');
        print_cell("Chapa 1", COLUMN_WIDTH, 'r');
        print_cell("Chapa 2", COLUMN_WIDTH, 'r');
        print_cell("Chapa 3", COLUMN_WIDTH, 'r');
        print_padded_border(TABLE_PADDING, 0); // Padded border

        print_padded_border(TABLE_PADDING, 1); // Padded border
        for (int i = 0; i < 4; i++) {
            char str[] = {'0' + vote_count[i], '\0'};
            print_cell(str, COLUMN_WIDTH, 'r');
        }
        print_padded_border(TABLE_PADDING, 0); // Padded border
        print_horizontal_line(TABLE_WIDTH, 1);

        print_padded_border(TABLE_PADDING, 1); // Padded border
        print_cell("Situacao:", COLUMN_WIDTH, 'r');
        print_cell("", COLUMN_WIDTH, 'r');
        print_cell("", COLUMN_WIDTH, 'r');
        print_cell("", COLUMN_WIDTH, 'r');
        print_padded_border(TABLE_PADDING, 0); // Padded border
        print_horizontal_line(TABLE_WIDTH, 1);
}

/* Contabiliza votos */
void count_votes(int *vote_count[4]) {
    return;
}