#include <conio2.h>
#include <stdlib.h>

typedef struct coordinates {
   int x;
   int y;
} coordinates;

typedef struct sapo {
   coordinates *pos;
   coordinates *previous_pos;
   int height;
   int width;
   int status;
   // colocar cor
} sapo;

struct text_info info;

void desenha_sapo(int x, int y);
void desenha_borda(int x_min, int y_min, int x_max, int y_max);
int colide_com_a_borda(sapo player, coordinates nova_pos);

#define X_MIN 1
#define X_MAX 120
#define Y_MIN 1
#define Y_MAX 30

#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_RIGHT 77
#define ARROW_LEFT 75

#define VERTICAL_SPEED 1
#define HORIZONTAL_SPEED 2

#define SAPO_WIDTH 8
#define SAPO_HEIGHT 2

#define DEFAULT_PLAYER_X 10
#define DEFAULT_PLAYER_Y 10

#define DEFAULT_PLAYER_STATUS 0


int main()
{
    coordinates default_pos = {
        .x = DEFAULT_PLAYER_X,
        .y = DEFAULT_PLAYER_Y
    };
    coordinates default_pos2 = {
        .x = DEFAULT_PLAYER_X,
        .y = DEFAULT_PLAYER_Y
    };
    sapo player = {
        .pos = &default_pos,
        .previous_pos = &default_pos2,
        .height = SAPO_HEIGHT,
        .width = SAPO_WIDTH,
        .status = DEFAULT_PLAYER_STATUS,
    };



    /* get the info about screen */
    gettextinfo( &info );

    /* set normal cursor */
    _setcursortype( _NORMALCURSOR );

    /* clear the screen */
    clrscr();

    /* Desenha a borda */
    desenha_borda(X_MIN, Y_MIN, X_MAX, Y_MAX);
    desenha_sapo(10, 10);


    int exit = 0;
    putchxy( player.pos->x, player.pos->y, '*' );
    do
    {
        if (kbhit())
        {
            char c = getch();
            if ((int) c == -32)
            {

                switch(getch())
                {
                case ARROW_UP:
                    player.pos->y -= VERTICAL_SPEED;
                    putchxy( 12, 13, ((char)player.pos->y  + 48) );
                    putchxy( 12, 14, ((char)player.previous_pos->y  + 48) );
                    if (!colide_com_a_borda(player)) {
                        putchxy( player.pos->x, player.pos->y, '^' );
                        player.previous_pos->x = player.pos->x;
                        player.previous_pos->y = player.pos->y;
                    } else {
                        player.pos->x = player.previous_pos->x;
                        player.pos->y += 1;
                        colide_com_a_borda(player);
                    }
                    // code for arrow up
                    break;
                case ARROW_DOWN:
                    player.pos->y += VERTICAL_SPEED;
                    if (!colide_com_a_borda(player)) {
                        putchxy( player.pos->x, player.pos->y, 'v' );
                        player.previous_pos->x = player.pos->x;
                        player.previous_pos->y = player.pos->y;
                    } else {
                        player.pos->x = player.previous_pos->x;
                        player.pos->y = player.previous_pos->y;
                    }
                    // code for arrow down
                    break;
                case ARROW_RIGHT:
                    player.pos->x += HORIZONTAL_SPEED;
                    if (!colide_com_a_borda(player)) {
                        putchxy( player.pos->x, player.pos->y, '>' );
                        player.previous_pos->x = player.pos->x;
                        player.previous_pos->y = player.pos->y;
                    } else {
                        player.pos->x = player.previous_pos->x;
                        player.pos->y = player.previous_pos->y;
                    }
                    // code for arrow right
                    break;
                case ARROW_LEFT:
                    player.pos->x -= HORIZONTAL_SPEED;
                    if (!colide_com_a_borda(player)) {
                        putchxy( player.pos->x, player.pos->y, '<' );
                        player.previous_pos->x = player.pos->x;
                        player.previous_pos->y = player.pos->y;
                    } else {
                        player.pos->x = player.previous_pos->x;
                        player.pos->y = player.previous_pos->y;
                    }
                    // code for arrow left
                    break;
                }
                gotoxy( info.screenwidth, info.screenheight);
            }

        }
        // gotoxy( 2, 10 );
    }
    while(!exit);

    return 0;
}

void desenha_borda(int x_min, int y_min, int x_max, int y_max) {
/*  x1, y1 : canto superior esquerdo da tela.
    x2, y2 : canto inferior direito da tela.
*/
    int i;
    gotoxy( x_min, y_min );
    for (i = 1; i <= x_max; i++) {
            putch( '=');
    }

    gotoxy( x_min, y_max );
    for (i = 1; i < x_max; i++) {
            putch( '=' );
    }

    for (i = 2; i < y_max; i++)
    {
        putchxy( x_min, i, '|');
        putchxy( x_max, i, '|');
    }

    return;
}

void desenha_sapo(int x, int y) {
    gotoxy( x, y );
    putch(' ');
    putch(' ');
    putch('(');
    putch('0');
    putch('0');
    putch(')');

    gotoxy( x, y + 1 );
    putch('\\');
    putch('^');
    putch('{');
    putch(' ');
    putch(' ');
    putch('}');
    putch('^');
    putch('/');

    return;
}

int colide_com_a_borda(sapo player, coordinates nova_pos) {
   /*   Borda em colisão:
        0 : Não colide
        1 : Cima
        2 : Direita
        3 : Baixo
        4 : Esquerda
   */
   if (nova_pos->y <= Y_MIN) {
    return 1;
   } else if (nova_pos->x >= (X_MAX - player.width)) {
    return 2;
   } else if (nova_pos->y >= (Y_MAX - player.height)) {
    return 3;
   } else if (nova_pos->x <= Y_MIN) {
    return 4;
   }
   return 0;
}

coordinates construct_new_position(char direction, int speed, coordinates current_pos, coordinates new_pos) {
    if ()
}


