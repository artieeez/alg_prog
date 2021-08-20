#include <stdlib.h>
#include <stdio.h>


/* Declaracao de Constantes */
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
#define GRENDENE_VALOR 1.20

/* Declaracao function prototypes */
void clear_screen();
void flush_in();

int main(void) {
    /* Declaracao de variaveis */
    int opcao_selecionada, acoes_compradas;
    float acoes_compradas_total;

    /* Declaracao e inicializacao de listas com informacoes das acoes */
    const char *name_arr[QUANTIDADE_OPCOES] = {
        "Gerdau",
        "Petrobras",
        "Lojas Renner",
        "Grendene"
    };
    const int disponivel_arr[QUANTIDADE_OPCOES] = {
        GERDAU_DISPONIVEL,
        PETROBRAS_DISPONIVEL,
        RENNER_DISPONIVEL,
        GRENDENE_DISPONIVEL
    };
    const float valor_arr[QUANTIDADE_OPCOES] = {
        GERDAU_VALOR,
        PETROBRAS_VALOR,
        RENNER_VALOR,
        GRENDENE_VALOR
    };
    int quantidade_vendida_arr[QUANTIDADE_OPCOES] = { [ 0 ... QUANTIDADE_OPCOES - 1] = 0 };

    opcao_selecionada = 0;
    acoes_compradas = 0;
    int scanf_success = 0; // Usado para checar retorno de scanf

    /* While loop ate entrada ser valida */
    while(!opcao_selecionada) {
        clear_screen();

        /* Apresentacao de quadro de acoes */
        printf("Código Opção        Disponível Valor(R$)\n");
        for (int i = 0; i < 4; i++) {
            printf("%-6d %-12s %-10d %.2f \n",
            i + 1, // Codigo
            name_arr[i], // Opcao
            disponivel_arr[i], // Disponivel
            valor_arr[i]); // Valor
        }

        /* Obtencao de valores pelo usuario */
        printf("Selecione um codigo e quantidade a ser adquirida (Ex.: \"2 570\"):\n");
        scanf_success = scanf(" %d %d", &opcao_selecionada, &acoes_compradas);

        /* Input check */
        if(!scanf_success) { // ERRO scanf nao obtem 2 valores
            clear_screen();
            printf("Entrada invalida. Insira o codigo e quantidade a ser adquirida!\
                \nEx.: \"2 570\"\nPressione enter para continuar.\n");
            opcao_selecionada = 0;
            acoes_compradas = 0;
            flush_in();
            getchar();
            continue;
        } else if(opcao_selecionada < 1 || opcao_selecionada > QUANTIDADE_OPCOES) { // ERRO opcao selecionada invalida
            clear_screen();
            printf("Opcao invalida. Selecione um numero entre 1 e %d.\
                \nPressione enter para continuar.\n", QUANTIDADE_OPCOES);
            opcao_selecionada = 0;
            acoes_compradas = 0;
            flush_in();
            getchar();
            continue;
        } else if(acoes_compradas > disponivel_arr[opcao_selecionada - 1]) { // ERRO quantidade de acoes nao disponivel
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
    }
    clear_screen();
    quantidade_vendida_arr[opcao_selecionada - 1] = acoes_compradas;
    printf("Sucesso!\nPressione enter para continuar.");
    flush_in();
    getchar();
    clear_screen();

    /* Apresentacao de relatorio final */
    printf("RELATÓRIO DE VENDAS DO DIA\n\n");
    const char *header[3] = { // Uso de lista no printf p/ facilitar a formatacao
        "Acao",
        "Quantidade vendida",
        "Total faturado",
    };
    printf("%-13s %-19s %-12s\n", header[0], header[1], header[2]);

    /* Declaracao e Inicializacao de variaveis p/ calculo final */
    int quantidade_total_vendida = 0;
    float total_faturado = 0;

    /* Confecao de quadro final e calculo final */
    for (int i = 0; i < QUANTIDADE_OPCOES; i++) {
        printf("%-13s %18d  R$ %11.2f \n",
        name_arr[i], // acao
        quantidade_vendida_arr[i], // Quantidade vendida
        quantidade_vendida_arr[i] * valor_arr[i]); // Total faturado
        /* Calculo de soma final */
        quantidade_total_vendida += quantidade_vendida_arr[i];
        total_faturado += quantidade_vendida_arr[i] * valor_arr[i];
    }
    /* Apresentacao de soma final */
    printf("TOTAL         %18d  R$ %11.2f\n\n", quantidade_total_vendida, total_faturado);
    return 0;
}


/* Limpa a tela */
void clear_screen() {
    #ifdef _WIN32
    system("cls");
    #endif

    #ifdef linux
    system("clear");
    #endif
}

/* Limpa buffer de entrada */
void flush_in() {
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}