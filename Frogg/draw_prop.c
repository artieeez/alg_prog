#include <conio2.h>
#include <stdlib.h>

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

#define RENDERED_OBJECT_MAX_WIDTH 10
#define RENDERED_OBJECT_MAX_HEIGHT 10

typedef struct coordinates {
   int x;
   int y;
} coordinates;

typedef struct render_data {
    coordinates *pos;
    coordinates *previous_pos;
    int height;
    int width;
    char content[RENDERED_OBJECT_MAX_WIDTH][RENDERED_OBJECT_MAX_HEIGHT];
} render_data;

typedef struct physics_data {
    int x_speed;
    int y_speed;
} physics_data;

typedef struct entity {
   render_data *render;
   physics_data *physics;
} entity;

struct text_info info;


void desenha_borda(int x_min, int y_min, int x_max, int y_max);


void draw_prop(render_data *obj);


int main()
{
    int i;
    coordinates default_pos = {
        .x = DEFAULT_PLAYER_X,
        .y = DEFAULT_PLAYER_Y
    };

    render_data *r = malloc(sizeof(render_data));
    if (r == NULL) {
        return;
    }

    /* get the info about screen */
    gettextinfo( &info );

    /* set normal cursor */
    _setcursortype( _NORMALCURSOR );

    /* clear the screen */
    clrscr();

    /* Desenha a borda */
    desenha_borda(X_MIN, Y_MIN, X_MAX, Y_MAX);



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

void draw_prop(render_data *obj) {

    gotoxy( *obj->pos->x, *obj->pos->y );

    for( int i = 0; i < *obj->height; i++) {
        for( int j = 0; j < *obj->width; j++) {
            putch( *obj->content[i][j] );
        }
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

