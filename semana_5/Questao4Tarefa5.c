/* Este programa retorna quantidade de ações compradas na bolsa de valores e valor pago.*/

#include <stdio.h>

#define IDGERDAU 1
#define IDPETROBRAS 2
#define IDRENNER 3
#define IDGRENDENE 4

#define QTDGERDAU 2000
#define QTDPETROBRAS 5000
#define QTDRENNER 4500
#define QTDGRENDENE 500

#define VALORGERDAU 4.00
#define VALORPETROBRAS 22.50
#define VALORRENNER 2.50
#define VALORGRENDENE 1.20

#define PEDIDOS 4
#define MEDIA 5


int main()
{

    int codigo,quantidade;//Declaracao de variavel do tipo int
    int contador=0;//Declaracao variavel para controle do for do tipo int
    int estoquegerdau, estoquepetrobras, estoquerenner, estoquegrendene;//Declaracao de variavel do tipo int
    int qtdvendidagerdau, qtdvendidapetrobras, qtdvendidarenner, qtdvendidagrendene; //Declaracao de variavel do tipo int
    float pgtgerdau, pgtpetrobras, pgtrenner, pgtgrendene;//Declaracao de variavel do tipo float
    float faturamentogerdau=0,faturamentopetrobras=0,faturamentorenner=0,faturamentogrendene=0;//Declaração de variaveis do tipo float inicializadas em 0
    float totalfaturado=0,totalmedia=0;//Declaracao de variavel do tipo float incializadas em 0

    pgtgerdau = 0;//Incializa variavel para 0
    pgtpetrobras = 0;//Incializa variavel para 0
    pgtrenner = 0;//Incializa variavel para 0
    pgtgrendene = 0;//Incializa variavel para 0

    qtdvendidagerdau = 0;//Incializa variavel para 0
    qtdvendidapetrobras = 0;//Incializa variavel para 0
    qtdvendidarenner = 0;//Incializa variavel para 0
    qtdvendidagrendene = 0;//Incializa variavel para 0


    estoquegerdau = QTDGERDAU;//Atribui valor da constante definida na variavel
    estoquepetrobras = QTDPETROBRAS;//Atribui valor da constante definida na variavel
    estoquerenner = QTDRENNER;//Atribui valor da constante definida na variavel
    estoquegrendene = QTDGRENDENE;//Atribui valor da constante definida na variavel


    do //comando do while para repetir codigo abaixo repetidas vezes de acordo com o valor inserido pelo usuario na variavel codigo
    {

        /*Retorna na tela Tabela incial com as quantidades de acoes e seus valores*/
        printf("\nAbaixo, selecione o codigo de uma empresa e escolha quantidade de acoes que deseja comprar:\n\n");
        printf("CODIGO\tOPCAO\t\tDISPONIVEL\tVALOR(R$)\n");
        printf("1\tGerdau\t\t%d\t\t4.00\n",estoquegerdau);
        printf("2\tPetrobras\t%d\t\t22.50\n",estoquepetrobras);
        printf("3\tLojas Renner\t%d\t\t2.50\n",estoquerenner);
        printf("4\tGrendene\t%d\t\t1.20\n",estoquegrendene);

        printf("\nDigite o codigo da empresa da qual voce deseja comprar uma acao, ou digite 5 para sair:\n");//Retorna mensagem na tela
        scanf("%d",&codigo);//leitura do valor digitado pelo usuario
        if(codigo==5) //Condicao para se comando digitado for igual a 5
        {
            printf("Programa cancelado\n"); //Resposta para o usuario
        }
        else
        {
            printf("Digite a quantidade de acoes que deseja comprar dessa empresa:\n");//Retorna mensagem na tela
            scanf("%d",&quantidade);//leitura do valor digitado pelo usuario
        }

        switch(codigo)//Inicia função switch
        {
        case IDGERDAU://Primeiro caso
            if(estoquegerdau >0 && estoquegerdau>=quantidade)//condicao logica que define estoque como sendo maior ou igual a quantidade
            {
                estoquegerdau -= quantidade;//Diminui o valor de acoes compradas pelo estoque
                pgtgerdau = quantidade*VALORGERDAU;//Calcula preco
                printf("Acoes compradas:%10d\n",quantidade);//Retorna mensagem na tela com a quantidade de acoes compradas
                printf("Valor a pagar: R$%10.2f\n",pgtgerdau);//Retorna mensagem na tela com resultado da operacao
                break;//Encerra caso
            }
            else
            {
                printf("\nVoce excedeu o limite de acoes disponiveis para compra!\n");//retorna na tela mensagem de erro
                printf("Acoes da Gerdau disponiveis: %d\n", estoquegerdau);//Retorna para o usuario numero de acoes disponiveis
                break;//Encerra switch
            }
        case IDPETROBRAS://Segundo Caso
            if(estoquepetrobras>0 && quantidade<=QTDPETROBRAS)//condicao logica que define estoque como sendo maior ou igual a quantidade
            {
                estoquepetrobras -= quantidade;//Diminui o valor de acoes compradas pelo estoque
                pgtpetrobras = quantidade*VALORPETROBRAS;//Calcula preco
                printf("Acoes compradas:%10d\n",quantidade);//Retorna mensagem na tela com a quantidade de acoes compradas
                printf("Valor a pagar: R$%10.2f\n",pgtpetrobras);//Retorna mensagem na tela com resultado da operacao
                break;//Encerra caso
            }
            else
            {
                printf("Voce excedeu o limite de acoes disponiveis para comprar!\n");//retorna na tela mensagem de erro
                printf("Acoes da Petrobras disponiveis: %d\n", estoquepetrobras);//Retorna para o usuario numero de acoes disponiveis
                break;//Encerra switch
            }
        case IDRENNER://Terceiro caso
            if(estoquerenner>0 && quantidade<=QTDRENNER)//condicao logica que define estoque como sendo maior ou igual a quantidade
            {
                estoquerenner -= quantidade;///Diminui o valor de acoes compradas pelo estoque
                pgtrenner = quantidade*VALORRENNER;//Calcula preco
                printf("Acoes compradas: %10d\n",quantidade);//Retorna mensagem na tela com a quantidade de acoes compradas
                printf("Valor a pagar: R$%8.2f\n",pgtrenner);//Retorna mensagem na tela com resultado da operacao
                break;//Encerra caso
            }
            else
            {
                printf("Voce excedeu o limite de acoes disponiveis para comprar!\n");//retorna na tela mensagem de erro
                printf("Acoes da Petrobras disponiveis: %d\n", estoquerenner);//Retorna para o usuario numero de acoes disponiveis
                break;//Encerra caso
            }
        case IDGRENDENE://Quarto Caso
            if(estoquegrendene && quantidade<=QTDGRENDENE)
            {
                estoquegrendene -= quantidade;//Diminui o valor de acoes compradas pelo estoque
                pgtgrendene = quantidade*VALORGRENDENE;//Calcula preco
                printf("Acoes compradas: %10d\n",quantidade);//Retorna mensagem na tela com a quantidade de acoes compradas
                printf("Valor a pagar:R$%8.2f\n",pgtgrendene);//Retorna mensagem na tela com resultado da operacao
                break;//Encerra caso
            }
            else
            {
                printf("Voce excedeu o limite de acoes disponiveis para comprar!\n");//retorna na tela mensagem de erro
                printf("Acoes da Petrobras disponiveis: %d\n", estoquegrendene);//Retorna para o usuario numero de acoes disponiveis
                break;//Encerra caso
            default:
                printf("Acao Invalida\n");//Retorna acao invalida

            }

        }//fecha switch
    }
    while(codigo!=5); //fecha do while

    //Atribui quantidade e acoes vendidas da Gerdau
    qtdvendidagerdau = QTDGERDAU - estoquegerdau;
    //Atribui valor total do faturamento das acoes Gerdau
    faturamentogerdau = qtdvendidagerdau * VALORGERDAU;

    //Atribui quantidade de acoes vendidas da petrobras
    qtdvendidapetrobras = QTDPETROBRAS - estoquepetrobras;
    //Atribui valor total do faturamento das acoes Petrobras
    faturamentopetrobras = qtdvendidapetrobras * VALORPETROBRAS;

    //Atribui quantidade de acoes vendidas da renner
    qtdvendidarenner = QTDRENNER - estoquerenner;
    //Atribui valor total do faturamento das acoes Renner
    faturamentorenner = qtdvendidarenner * VALORRENNER;

    //Atribui quantidade de acoes vendidas da grendene;
    qtdvendidagrendene = QTDGRENDENE - estoquegrendene;
    //Atribui valor total do faturamento das acoes Grendene
    faturamentogrendene = qtdvendidagrendene * VALORGRENDENE;


    //Soma faturamento total das vendas das acoes
    totalfaturado = faturamentogerdau + faturamentopetrobras + faturamentorenner + faturamentogrendene;//Calcula total faturado


    /* TABELA DE RELATORIO DE FATURMENTO TOTAL E MEDIA DAS VENDAS */

    printf("\nRELATORIO DE VENDAS DO DIA\n");//Retorna mensagem na tela
    printf("\nACAO\t\tQUANTIDADE VENDIDA\tTOTAL FATURADO(R$)\n");//Retorna mensagem na tela
    printf("Gerdau\t\t%d\t\t\t\t%10.2f\n",qtdvendidagerdau,faturamentogerdau);//Retorna quantidade vendida da opção e total faturado
    printf("Petrobras\t%d\t\t\t\t%10.2f\n",qtdvendidapetrobras,faturamentopetrobras);//Retorna quantidade vendida da opção e total faturado
    printf("Lojas Renner\t%d\t\t\t\t%10.2f\n",qtdvendidarenner,faturamentorenner);//Retorna quantidade vendida da opção e total faturado
    printf("Grendene\t%d\t\t\t\t%10.2f\n",qtdvendidagrendene,faturamentogrendene);//Retorna quantidade vendida da opção e total faturado
    printf("TOTAL DE VENDAS DO DIA\t\t\t\t%10.2f\n",totalfaturado);//Retorna total faturado




    return(0);//Encerra programa
}


