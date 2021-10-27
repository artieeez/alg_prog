/*
Programa que utiliza arquivos indexados para armazenar registros sobre pessoas e facilitar a busca de pessoas por CPF.
-O programa utiliza dosi arquivos:
--Arquivo bin�rio que armazena registros que representam pessoas. Neste arquivo, pessoas s�o inclu�das � medida que s�o cadastradas,
sem qualquer ordenamento.
--Arquivo bin�rio que representa o �ndice do arquivo de pessoas. Cada registro neste arquivo armazena o CPF e a posi��o do registro da 
pessoa com esse CPF no arquivo de pessoas.

As informa��es sobre pessoas est�o sempre em arquivo, e s� s�o traziadas para a mem�ria sob demanda. Ou seja, as informa��es sobre pessoas
n�o s�o armazenadas em um vetor de pessoas em tempo de execu��o. Cada pessoa cadastrada � inserida diretamente no arquivo. Quando o usu�rio
deseja listar todas as pessoas, o arquivo � percorrido sequencialmente e as informa��es de cada pessoa s�o exibidas na tela, sem precisar
carregar todas as pessoas na mem�ria principal.

As informa��es do �ndice, por outro lado, s�o sempre mantidas na mem�ria principal. Um registro de �ndice  menor (em bytes) do que
um registro de pessoa. Quando � inserida, � criado um novo registro de �ndice, que � inclu�do ordenadamente no vetor de registros de �ndice.
Ou seja, este vetor est� sempre ordenado por CPF. Quando o programa � finalizado, os registros de �ndice s�o gravados em arquivo sequencialmente,
eliminando o arquivo anterior. Esses �ndices s�o gravados de modo ordenado por cpf no arquivo de �ndices.

Quando o usu�rio deseja buscar uma pessoa por CPF:
-Realiza-se uma busca bin�ria no vetor de registros de �ndice, encontrando a posi��o do registro com o CPF buscado. Essa busca � r�pida.
-Caso o CPF conste na base, a posi��o do registro da pessoa no arquivo de pessoas � obtido do registro de �ndice.
-� realizado acesso aleat�rio ao arquivo de pessoas, posicionando o cursor do arquivo na posi��o correta, e � realizada a leitura dos dados
 da pessoa nessa posi��o.
-Por fim, as informa��es da pessoa s�o exibidas.

Note que essa abordagem facilita a busca por CPF.
Mas seria poss�vel criar arquivos de �ndice para outros campos tamb�m, facilitando a busca por outros campos.
*/

#include <locale.h>
#include <stdio.h>
#include <string.h>

#define MAX_NOME 80
#define MAX_PESSOAS 1000
#define ARQ_PESSOAS "pessoas.bin"
#define ARQ_INDICE "indice.bin"

/*Estrutura que representa data*/
typedef struct {
    int dia, mes, ano;
} DATA;

/*Estrutura que representa registro no banco de pessoas*/
typedef struct {
    char nome[MAX_NOME];
    char cpf[12];
    DATA data_nasc;
} PESSOA;

/*Estrutura que representa registro no arquivo de �ndice*/
typedef struct {
    char cpf[11];
    int endereco;
} REGISTRO_INDICE;

/*Fun��es*/
int le_indice(REGISTRO_INDICE indice[], int *cont, char nome_arq_indice[]);
int grava_indice(REGISTRO_INDICE indice[], int cont, char nome_arq_indice[]);
void insere_registro_ordenado(REGISTRO_INDICE indice[], REGISTRO_INDICE novo_registro, int cont_registros);
int grava_pessoa(PESSOA pessoa, REGISTRO_INDICE indice[], int cont_registros, char nome_arq_pessoas[]);
void exibe_pessoa(PESSOA pessoa);
int exibe_pessoas(char nome_arq_pessoas[], int cont_pessoas);
void exibe_indice(REGISTRO_INDICE indice[], int cont_registros);
void exibe_registro_indice(REGISTRO_INDICE registro);
PESSOA le_pessoa();
int le_opcao();
int busca_binaria(REGISTRO_INDICE indice[], int tamanho, char cpf_buscado[]);
int recupera_pessoa(char nome_arq_pessoas[], int endereco_registro, PESSOA *pessoa);

int main() {
    setlocale(LC_ALL, "Portuguese");

    REGISTRO_INDICE indice[MAX_PESSOAS];
    int cont_pessoas = 0;
    int opcao, posicao_registro;
    char cpf_buscado[12];
    PESSOA pessoa;

    if (le_indice(indice, &cont_pessoas, ARQ_INDICE)) {
        do {
            opcao = le_opcao();

            switch (opcao) {
                case 1:
                    if (cont_pessoas == MAX_PESSOAS - 1) {
                        printf("\nO m�ximo de registros oi atingido\nN�o � poss�vel adicionar mais pessoas\n");
                    } else {
                        PESSOA pessoa = le_pessoa();
                        //exibe_pessoa(pessoa);
                        if (grava_pessoa(pessoa, indice, cont_pessoas, ARQ_PESSOAS)) {
                            cont_pessoas++;
                            printf("\nPessoa inserida com sucesso\n");
                        } else {
                            printf("\nOcorreu um erro na inser��o da pessoa\n");
                        }
                    }
                    break;

                case 2:
                    exibe_pessoas(ARQ_PESSOAS, cont_pessoas);
                    break;

                case 3:
                    exibe_indice(indice, cont_pessoas);
                    break;

                case 4:
                    printf("\nExistem %d pessoas cadastradas\n", cont_pessoas);
                    break;

                case 5:
                    printf("\nInforme o CPF buscado:\n");
                    gets(cpf_buscado);
                    posicao_registro = busca_binaria(indice, cont_pessoas, cpf_buscado);
                    if (posicao_registro == -1) {
                        printf("\nEste CPF n�o consta na base de dados.");
                    } else {
                        if (recupera_pessoa(ARQ_PESSOAS, indice[posicao_registro].endereco, &pessoa)) {
                            exibe_pessoa(pessoa);
                        }
                    }
                    break;
            }
        } while (opcao != 6);

        /*No fim, sempre grava o indice que foi mantido em mem�ria o tempo todo*/
        if (!grava_indice(indice, cont_pessoas, ARQ_INDICE)) {
            printf("N�o foi poss�vel salvar o �ndice\n");
        } else {
            printf("�ndice salvo\nFechando aplica��o\n");
        }
    } else {
        printf("\nN�o foi poss�vel ler o �ndice\nO programa ser� finalizado\n");
    }
    return 0;
}

/*Fun��o que obt�m op��o desejada pelo usu�rio*/
int le_opcao() {
    int op;
    do {
        printf("\nSelecione uma opcao:\n");
        printf("1-Adicionar uma nova pessoa\n");
        printf("2-Listar todas as pessoas\n");
        printf("3-Listar o �ndice\n");
        printf("4-Consultar quantidade de pessoas no banco de dados\n");
        printf("5-Buscar pessoa por CPF\n");
        printf("6-Sair\n");

        scanf("%d", &op);
        getchar();
        if (op < 1 || op > 6) {
            printf("Op��o inv�lida\n");
        }
    } while (op < 1 || op > 6);
}

/*Fun��o que requisita as informa��es necess�rias e retorna um registro de pessoa com estas informa��es*/
PESSOA le_pessoa() {
    PESSOA p;
    printf("Informe o nome da pessoa:\n");
    gets(p.nome);
    printf("Informe o CPF da pessoa:\n");
    gets(p.cpf);
    printf("Informe o dia, o mes e o ano de nascimento:\n");
    scanf("%d%d%d", &p.data_nasc.dia, &p.data_nasc.mes, &p.data_nasc.ano);
    getchar();
    return p;
}

/*Fun��o que l� o arquivo de �ndices, ou cria um novo caso o arquivo n�o exista.*/
int le_indice(REGISTRO_INDICE indice[], int *cont, char nome_arq_indice[]) {
    int result = 1;
    int tamanho = 0;
    FILE *arq_indice = fopen(nome_arq_indice, "rb");
    *cont = 0;

    if (arq_indice == NULL) {
        /*Assume que se a abertura para leitura falhou, o arquivo n�o existe,
        ent�o cria um novo arquivo de �ndice.*/
        arq_indice = fopen(nome_arq_indice, "wb");
        if (arq_indice == NULL) {
            /*Caso a cria��o do novo arquivo tamb�m falhe, ent�o a fun��o retorna
            um valor que representa falha*/
            result = 0;
        }
    } else {
        while (!feof(arq_indice)) {
            if (fread(&indice[*cont], sizeof(REGISTRO_INDICE), 1, arq_indice) == 1) {
                (*cont)++;
            }
        }
        fclose(arq_indice);
    }
    return result;
}

/*Fun��o que grava o vetor de registros de �ndice em arquivo*/
int grava_indice(REGISTRO_INDICE indice[], int cont, char nome_arq_indice[]) {
    int i, result = 1;
    FILE *arq_indice = fopen(nome_arq_indice, "wb");

    if (arq_indice == NULL) {
        result = 0;
    } else {
        /*Grava todo o vetor em uma �nica opera��o*/
        if (fwrite(indice, sizeof(REGISTRO_INDICE), cont, arq_indice) != cont) {
            result = 0;
        }
        fclose(arq_indice);
    }
    return result;
}

/*Fun��o que insere um novo registro de �ndice no vetor de �ndices de forma ordenada*/
void insere_registro_ordenado(REGISTRO_INDICE indice[], REGISTRO_INDICE novo_registro, int cont_registros) {
    int i, j, inseriu = 0;
    if (cont_registros == 0) {
        indice[0] = novo_registro;
    } else {
        i = 0;
        while (i < cont_registros && !inseriu) {
            if (strcmp(novo_registro.cpf, indice[i].cpf) < 0) {
                inseriu = 1;
                /*desloca todos os registros maiores para uma posi��o para a direita
                abrindo espa�o para colocar o registro na posi��o correta*/
                for (j = cont_registros; j > i; j--) {
                    indice[j] = indice[j - 1];
                }
                indice[i] = novo_registro;
            }
            i++;
        }
        /*Caso n�o tenha sido inserido ainda, significa que deve ser inserido no fim*/
        if (!inseriu) {
            indice[cont_registros] = novo_registro;
        }
    }
}

/*Abre o arquivo e insere os dados da pessoa no fim do arquivo j� existente*/
int grava_pessoa(PESSOA pessoa, REGISTRO_INDICE indice[], int cont_registros, char nome_arq_pessoas[]) {
    int result = 1;
    REGISTRO_INDICE ri;
    FILE *arq_pessoas = fopen(nome_arq_pessoas, "ab");
    if (arq_pessoas == NULL) {
        result = 0;
    } else {
        if (fwrite(&pessoa, sizeof(PESSOA), 1, arq_pessoas) != 1) {
            result = 0;
        } else {
            strcpy(ri.cpf, pessoa.cpf);
            /*O endre�o da pessoa gravada no arquivo � a posi��o corrente do arquivo (em bytes)
            menos o tamanho em bytes de um registro do tipo PESSOA*/
            ri.endereco = ftell(arq_pessoas) - sizeof(PESSOA);

            /*Chama a fun��o que insere o registro no vetor de �ndices*/
            insere_registro_ordenado(indice, ri, cont_registros);
        }
        fclose(arq_pessoas);
    }
    return result;
}

/*Fun��o que recupera informa��es sobre uma pessoa, em fun��o da posi��o em que essa posi��o
est� no arquivo de pessoas*/
int recupera_pessoa(char nome_arq_pessoas[], int endereco_registro, PESSOA *pessoa) {
    int result = 1;
    FILE *arq_pessoas = fopen(nome_arq_pessoas, "rb");
    if (arq_pessoas == NULL) {
        result = 0;
    } else {
        if (fseek(arq_pessoas, endereco_registro, SEEK_SET) == 0) {
            if (fread(pessoa, sizeof(PESSOA), 1, arq_pessoas) != 1) {
                result = 0;
            }
        } else {
            result = 0;
        }
        fclose(arq_pessoas);
    }
    return result;
}

/*Fun��o que abre o arquivo de pessoas e exibe as informa��es de todas as pessoas armazenadas.*/
int exibe_pessoas(char nome_arq_pessoas[], int cont_pessoas) {
    int i, result = 1;
    PESSOA pessoa;
    FILE *arq_pessoas = fopen(nome_arq_pessoas, "rb");
    if (arq_pessoas == NULL) {
        result = 0;
    } else {
        /*L� e exibe cada pessoa individualmente*/
        for (i = 0; i < cont_pessoas; i++) {
            if (fread(&pessoa, sizeof(PESSOA), 1, arq_pessoas) == 1) {
                exibe_pessoa(pessoa);
            } else {
                result = 0;
            }
        }
        fclose(arq_pessoas);
    }
    return result;
}

/*Fun��o que exibe informa��es de uma pessoa espec�fica*/
void exibe_pessoa(PESSOA pessoa) {
    printf("NOME:%s\n", pessoa.nome);
    printf("CPF:%s\n", pessoa.cpf);
    printf("DATA DE NASCIMENTO:%d/%d/%d\n", pessoa.data_nasc.dia, pessoa.data_nasc.mes, pessoa.data_nasc.ano);
    printf("\n");
}

/*Fun��o que exibe informa��es do �ndice*/
void exibe_indice(REGISTRO_INDICE indice[], int cont_registros) {
    int i;
    for (i = 0; i < cont_registros; i++) {
        exibe_registro_indice(indice[i]);
    }
}

/*Fun��o que exibe informa��es de um registro espec�fico do �ndice*/
void exibe_registro_indice(REGISTRO_INDICE registro) {
    printf("CPF:%s\n", registro.cpf);
    printf("ENDERE�O:%d\n", registro.endereco);
    printf("\n");
}

/*Fun��o que realiza a busca bin�ria no vetor de �ndices, buscando o registro com um dado CPF*/
int busca_binaria(REGISTRO_INDICE indice[], int tamanho, char cpf_buscado[]) {
    int primeiro, ultimo, meio, localizacao = -1;

    primeiro = 0;
    ultimo = tamanho - 1;
    meio = (primeiro + ultimo) / 2;

    while ((primeiro <= ultimo) && localizacao == -1) {
        if (strcmp(indice[meio].cpf, cpf_buscado) < 0) {
            primeiro = meio + 1;
        } else if (strcmp(indice[meio].cpf, cpf_buscado) > 0) {
            ultimo = meio - 1;
        } else {
            localizacao = meio;
        }
        meio = (primeiro + ultimo) / 2;
    }
    return localizacao;
}
