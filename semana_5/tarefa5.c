#include <time.h> // necessaria para a função srand() e rand()
#include <stdlib.h>
#include <stdio.h>

#define TAMANHO 15
// tamanho do arranjo a ser adaptado para o uso necessario na tarefa
#define VALOR_MAXIMO 10
//Define o intervalo de randomizacao de acordo com requisito da tarefa

/* função rand() retorna um número aleatório entre 0 e o valor definido na variável de
   sistema RAND_MAX o calculo abaixo converte para [0, VALOR_MAXIMO]  */
int main() {
     int arr[TAMANHO]; // declaracao de arranjo
     int i;
     srand(time(0));
     //"Semente"  da randomizacao, deve ser executado fora do laço e apenas uma vez.Usa o clock do Windows para randomizar

     for (i = 0; i < TAMANHO; i++) {
          arr[i] = (int)(rand() / (double) RAND_MAX * (VALOR_MAXIMO + 1));
          printf(" %d", arr[i]);
     }
     printf("\n");

     int aux = arr[0];
     int temp = 0;
     for (i = 1; i < 15; i++)
          if (arr[i] > aux)
          {
               aux = arr[i];
               temp = i;
          }
     printf ("%d %d", aux,temp); 

     return 0;
} // fim da main
