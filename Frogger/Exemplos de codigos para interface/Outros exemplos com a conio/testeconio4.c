/*Inclui funcoes para manipular o terminal*/
#include <conio2.h>
/*Incluida apenas para usar a funcao Sleep*/
#include <windows.h>
/*Incluida apenas para usar a funcao time*/
#include <time.h>
#include <stdlib.h>

#define WAIT_TIME 50
#define MAX 1000
#define MAX_X 80
#define MAX_Y 25
#define MAX_COLOR 15

/*Inicializa a matriz com valores de cores aleatórias entre 0 e 15*/
void initializeMatrix(int matrix[MAX_Y][MAX_X], int linhas, int colunas){
    int i,j,color;
    for(i=0;i<linhas;i++){
        for(j=0;j<colunas;j++){
            matrix[i][j] = rand()%MAX_COLOR;
        }
    }
}

/*Verifica para todas as colunas, se cada uma delas está com uma única cor*/
int isHomogeneous(int matrix[MAX_Y][MAX_X], int linhas, int colunas){
    int i,j;
    int equal = 1;
    int reference;//elemento na primeira posição
    for(j=0;j<colunas && equal==1;j++){
        reference = matrix[0][j];
        for(i=1;i<linhas && equal==1;i++){
            if( matrix[i][j]!=reference ){
                equal = 0;
            }
        }
    }
    return equal;
}

/*Desenha a matrix na tela*/
void draw(int matrix[MAX_Y][MAX_X], int linhas, int colunas){
    int x,y;
    for(x=0;x<colunas;x++){
        for(y=0;y<linhas;y++){
            textbackground(matrix[y][x]);
            gotoxy(x+1,y+1);
            cprintf(" ");
        }
    }
}

int main(){
    int x,y,i,color,count,finish;
    int matrix[MAX_Y][MAX_X];

    finish = 0;
    srand(time(NULL));
    initializeMatrix(matrix,MAX_Y,MAX_X);
    draw(matrix,MAX_Y,MAX_X);

    while(!finish){
        x = rand()%MAX_X;
        y = rand()%MAX_Y;
        color = matrix[y][x];

        if(y>0){
            color = matrix[y-1][x];
        }

        matrix[y][x] = color;

        textbackground(color);
        gotoxy(x+1,y+1);
        cprintf(" ");

        finish = isHomogeneous(matrix,MAX_Y,MAX_X);
    }
    /*Espera o usuario digitar algo para finalizar o programa*/
    _getche();
}
