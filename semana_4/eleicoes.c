#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Declaracao function prototypes */
void clear_screen();
void flush_in();
void print_horizontal_line(int width, int solid);
void print_padded_border(int padding_size, int left);
void print_centered_string(char *str, int width);
void print_cell(char *str, int width, char align);
void print_table(int *vote_count, int tem_vencedor, int tem_empate, int votos_totais, int vencedor_index, int segundo_index);

/* Constantes */
#define TABLE_CHAR '*'
#define COLUMN_WIDTH 10
#define COLUMN_AMOUNT 5
#define TABLE_PADDING 4
const int TABLE_WIDTH = COLUMN_WIDTH * COLUMN_AMOUNT + TABLE_PADDING * 2;

/* Macros */
#define ARRAY_SIZE(x) ( sizeof(x) / sizeof((x)[0]) )

int main(void) {
    int voto = 5;
    char continuar = 's';
    int vote_count[5] = {0, 0, 0, 0, 0};
    int vencedor_index = 1;
    int segundo_index = 2;
    int votos_totais = 0;
    int tem_vencedor = 0;
    int tem_empate = 0;
    while(continuar == 's') {
        /* Verifica situacao da votacao */
        tem_vencedor = vote_count[vencedor_index] > ((float) votos_totais / 2)
            ? 1 
            : 0;
        tem_empate = vote_count[vencedor_index] == vote_count[segundo_index]
            ? 1 
            : 0;

        print_table(vote_count, tem_vencedor, tem_empate, votos_totais, vencedor_index, segundo_index);

        /* 
            Coleta do voto */
        printf("\nDigite o numero da chapa e aperte ENTER:\n");
        scanf(" %d", &voto);
        flush_in();
        
        /* 
            Voto invalido handler */
        if (voto < 0 || voto > 3) {
            clear_screen();
            printf("VOTO INVALIDO - Aperte enter para continuar.\n");
            vote_count[4]++;
            getchar();
            continue;
        }

        /* Contabiliza os votos */
        vote_count[voto]++;
        votos_totais++;
        /* Atualiza a primeira e segunda colocação */
        if (voto > 0 && voto < 4) {
            if (vote_count[voto] > vote_count[vencedor_index] ||
                (vote_count[voto] == vote_count[vencedor_index] && voto != vencedor_index)) {
                segundo_index = vencedor_index;
                vencedor_index = voto;
            } else if (vote_count[voto] > vote_count[segundo_index] && voto != vencedor_index) {
                segundo_index = voto;
            }
        }
        /* 
            Continuar? */
        do {
            clear_screen();
            printf("VOTOU EM %d\nContinuar votando? (s) para Sim, (n) para nao.\n", voto);
            scanf(" %c", &continuar);
        } while(continuar != 's' && continuar != 'n');
        voto = 5;
    }
    print_table(vote_count, tem_vencedor, tem_empate, votos_totais, vencedor_index, segundo_index);
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
void print_table(int *vote_count, int tem_vencedor, int tem_empate, int votos_totais, int vencedor_index, int segundo_index) {
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
        print_cell("Nulos", COLUMN_WIDTH, 'r');
        print_padded_border(TABLE_PADDING, 0); // Padded border

        print_padded_border(TABLE_PADDING, 1); // Padded border
        for (int i = 0; i < 5; i++) {
            char str[5];
            sprintf(str, "%d", vote_count[i]);
            print_cell(str, COLUMN_WIDTH, 'r');
        }
        print_padded_border(TABLE_PADDING, 0); // Padded border
        print_horizontal_line(TABLE_WIDTH, 1);

        print_padded_border(TABLE_PADDING, 1); // Padded border

        if (tem_vencedor && votos_totais >= 2) {
            print_cell("Vencedor:", COLUMN_WIDTH, 'r');
            printf("             Chapa %d | %6.2f%% dos votos",
                vencedor_index,
                ( vote_count[vencedor_index] / (float) votos_totais ) * 100
            );
        } else if(tem_empate && votos_totais >= 2) {
            print_cell("Empate entre:", COLUMN_WIDTH, 'r');
            print_cell("", COLUMN_WIDTH, 'r');
            print_cell("", COLUMN_WIDTH, 'r');
            printf("Chapa %d e Chapa %d",
                vencedor_index, segundo_index);
        } else if(votos_totais >= 2) {
            print_cell("Segundo turno entre:", COLUMN_WIDTH, 'r');
            print_cell("", COLUMN_WIDTH, 'r');
            printf("   Chapa %d e Chapa %d",
                vencedor_index, segundo_index);
        } else {
            print_cell("", COLUMN_WIDTH, 'r');
            print_cell("", COLUMN_WIDTH, 'r');
            print_cell("", COLUMN_WIDTH, 'r');
            print_cell("", COLUMN_WIDTH, 'r');
            print_cell("", COLUMN_WIDTH, 'r');
        }

        print_padded_border(TABLE_PADDING, 0); // Padded border
        print_horizontal_line(TABLE_WIDTH, 1);
}
