#include <stdio.h>
#include <ctype.h>


#define CHAPA1 1
#define CHAPA2 2
#define CHAPA3 3
#define CHAPABRANCO 0

int main()
{

    int voto, vencedor;
    int somavotos1=0, somavotos2=0, somavotos3=0;
    int somavotosbrancos=0, somavotoinvalido=0;
    int totalchapa1=0, totalchapa2=0, totalchapa3=0;
    int totalbranco=0, totalinvalido=0;
    int totalvotos=0, totalvotosvalidos=0;
    float porcentagemvencedor;
    char continuar;

    printf("Escolha uma das chapas para votar:\n");
    printf("Para votar na Chapa 1 - Digite 1\n");
    printf("Para votar na Chapa 2 - Digite 2\n");
    printf("Para votar na Chapa 3 - Digite 3\n");
    printf("Para votar em branco - Digite 0\n");

    do
    {
        printf("Digite seu voto:\n");
        scanf("%d",&voto);
        switch(voto)
        {
        case CHAPABRANCO:
            somavotosbrancos++;
            printf("Voce votou em branco!\n");
            break;
        case CHAPA1:
            somavotos1++;
            printf("Voce votou na chapa 1!\n");
            break;
        case CHAPA2:
            somavotos2++;
            printf("Voce votou na chapa 2!\n");
            break;
        case CHAPA3:
            somavotos3++;
            printf("Voce votou na chapa 3!\n");
            break;
        default:
            somavotoinvalido++;
            printf("Chapa invalida!\n");
        }
        printf("Deseja continuar? (S - sim N - nao)\n");
        do
        {
            scanf("%c",&continuar);
            continuar=toupper(continuar);
        }
        while(continuar !='S' && continuar !='N');

    }
    while(continuar == 'S');

    //Define o total de votos para cada chapa e o total de brancos e invalidos

    totalchapa1=somavotos1;
    printf("Total de votos para a chapa 1: %d\n",totalchapa1);

    totalchapa2=somavotos2;
    printf("Total de votos para a chapa 2: %d\n",totalchapa2);

    totalchapa3=somavotos3;
    printf("Total de votos para a chapa 3: %d\n",totalchapa3);

    totalbranco=somavotosbrancos;
    printf("Total de votos em branco: %d\n",totalbranco);

    totalinvalido=somavotoinvalido;
    printf("Total de votos invalidos: %d\n",totalinvalido);

    totalvotosvalidos = totalchapa1+totalchapa2+totalchapa3;


//Para casos de empate

    if(totalchapa1==totalchapa2 && totalchapa2==totalchapa3)
    {
        printf("Houve empate entre as tres chapas. Havera segundo turno.\n");
    }
    else if (totalchapa1==totalchapa2)
    {
        printf("Houve empate entre chapa 1 e 2. Havera segundo turno\n");
    }
    else if(totalchapa1==totalchapa3)
    {
        printf("Houve empate entre chapa 1 e 3. Havera segundo turno\n");
    }
    else if(totalchapa2==totalchapa3)
    {
        printf("Houve empate entre chapa 2 e chapa 3, Havera segundo turno\n");
    }

//Para casos de vitoria de alguma das chapas

    if(totalchapa1 >totalchapa2 && totalchapa1 > totalchapa3)
    {
        vencedor=1;
        porcentagemvencedor = (float) totalchapa1/totalvotosvalidos * 100;
    }
    else if(totalchapa2 > totalchapa1 && totalchapa2 > totalchapa3)
    {
        vencedor=2;
        porcentagemvencedor = totalchapa2/(totalvotosvalidos/100);
    }
    else if(totalchapa3 > totalchapa1 && totalchapa3 > totalchapa2)
    {
        vencedor=3;
        porcentagemvencedor = totalchapa3/(totalvotosvalidos/100);
    }

    switch(vencedor)
    {
    case 1:
        if(porcentagemvencedor>=50)
        {
            printf("O vencedor foi a chapa 1 com mais de %.2f dos votos\n",porcentagemvencedor);
        }
        else
        {
            printf("Devera haver segundo turno, pois a porcentagem de votos foi %.2f");
        }
    case 2:
        if(porcentagemvencedor>=50)
        {
            printf("O vencedor foi a chapa 1 com mais de %.2f dos votos\n",porcentagemvencedor);
        }
        else
        {
            printf("Devera haver segundo turno, pois a porcentagem de votos foi %.2f");
        }
    case 3:
        if(porcentagemvencedor>=50)
        {
            printf("O vencedor foi a chapa 1 com mais de %.2f dos votos\n",porcentagemvencedor);
        }
        else
        {
            printf("Devera haver segundo turno, pois a porcentagem de votos foi %.2f");
        }
    }



    return 0;

}
