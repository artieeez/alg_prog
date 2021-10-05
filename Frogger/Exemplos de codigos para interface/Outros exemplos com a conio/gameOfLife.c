/*
Author: Joel Luís Carbonera
This is a C implementation of the Conway's game of life. More information inf the following link:
https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

This implementation is focused on the windows platform
This implementation displays the dead and alive cells in a console (textual) application, using conio.h
*/


#include <conio2.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define WAIT_TIME 50
#define MAX 1000
#define MAX_X 80
#define MAX_Y 25
#define DEAD_COLOR 0
#define ALIVE_COLOR 10
#define DEAD 0
#define ALIVE 1

void initializeMatrix(int matrix[MAX_Y][MAX_X], int lines, int columns){
    int i,j,color;
    for(i=0;i<lines;i++){
        for(j=0;j<columns;j++){
            matrix[i][j] = rand()&1;
        }
    }
}

int equals(int matrix1[MAX_Y][MAX_X], int matrix2[MAX_Y][MAX_X], int lines, int columns){
    int i,j;
    int equal = 1;
    for(i=0;i<lines && equal==1;i++){
        for(j=0;j<columns && equal==1;j++){
            if(matrix1[i][j]!=matrix2[i][j]){
                equal = 0;
            }
        }
    }
    return equal;
}

void draw(int matrix[MAX_Y][MAX_X], int lines, int columns){
    int x,y;
    for(x=0;x<columns;x++){
        for(y=0;y<lines;y++){
            if(matrix[y][x] == DEAD){
                textbackground(DEAD_COLOR);
            }else{
                textbackground(ALIVE_COLOR);
            }
            gotoxy(x+1,y+1);
            cprintf(" ");
        }
    }
}

int countAliveNeighbors(int state[MAX_Y][MAX_X],int linha, int coluna, int lines, int columns){
    int x,y,count = 0;

    for(x=coluna-1; x<=coluna+1; x++){
        for(y=linha-1; y<=linha+1; y++){
            if(x>=0 && x< columns && y>=0 && y< lines){
                if(!(x==coluna && y==linha)){
                    count = count+state[y][x];
                }
            }
        }
    }
    return count;
}

void updateState(int oldState[MAX_Y][MAX_X], int newState[MAX_Y][MAX_X],int lines, int columns){
    int x,y,count;

    for(x=0;x<columns;x++){
        for(y=0;y<lines;y++){
            count = countAliveNeighbors(oldState,y,x,lines, columns);
            //newState[y][x] = oldState[y][x];
            if(oldState[y][x] == ALIVE){
                if(count < 2 || count > 3){
                    newState[y][x]= DEAD;
                }else{
                    newState[y][x]= ALIVE;
                }
            }else if(oldState[y][x] == DEAD){
                if(count == 3){
                    newState[y][x]= ALIVE;
                }else{
                    newState[y][x]= DEAD;
                }
            }
        }
    }
}

void copyState(int original[MAX_Y][MAX_X], int copy[MAX_Y][MAX_X],int lines, int columns){
    int x,y;
    for(x=0;x<columns;x++){
        for(y=0;y<lines;y++){
            copy[y][x] = original[y][x];
        }
    }
}

int main(){
    int x,y,i,color,count,finish;
    int currentState[MAX_Y][MAX_X],newState[MAX_Y][MAX_X];
    srand(time(NULL));

    finish = 0;
    srand(time(NULL));
    initializeMatrix(currentState,MAX_Y,MAX_X);
    while(!finish){
        draw(currentState,MAX_Y,MAX_X);
        updateState(currentState,newState,MAX_Y,MAX_X);
        finish = equals(currentState,newState,MAX_Y,MAX_X);
        if(!finish){
            copyState(newState,currentState,MAX_Y,MAX_X);
        }
    }
    /*Wait the user to provide some input for finishing the program*/
    _getche();
}
