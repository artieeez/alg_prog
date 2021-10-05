#include <conio2.h>
#include <stdlib.h>
#include <stdbool.h>

#define X_MIN 1
#define X_MAX 120
#define Y_MIN 1
#define Y_MAX 30

#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_RIGHT 77
#define ARROW_LEFT 75

#define DEFAULT_HORIZONTAL_SPEED 1
#define DEFAULT_VERTICAL_SPEED 2

#define SAPO_WIDTH 8
#define SAPO_HEIGHT 2

#define DEFAULT_PLAYER_X 10
#define DEFAULT_PLAYER_Y 10

#define DEFAULT_PLAYER_STATUS 0
#define DEFAULT_PLAYER_IS_ACTIVE true
#define DEFAULT_ENTITY_IS_ACTIVE false

#define RENDERED_OBJECT_MAX_WIDTH 10
#define RENDERED_OBJECT_MAX_HEIGHT 10

#define ENTITIES_MAX_AMOUNT 10

typedef struct coordinates {
   int x;
   int y;
} coordinates;

typedef struct render_data {
    coordinates *pos;
    coordinates *previous_pos;
    int height;
    int width;
    char *content[RENDERED_OBJECT_MAX_HEIGHT];
} render_data;

typedef struct physics_data {
    int x_speed;
    int y_speed;
} physics_data;

typedef struct entity {
   render_data *render;
   physics_data *physics;
   bool is_active;
} entity;

struct text_info info;

entity *initialize_player();
void draw_prop(render_data *obj);
void desenha_borda(int x_min, int y_min, int x_max, int y_max);
render_data *create_render_data(
                    coordinates *pos,
                    int height,
                    int width,
                    char *content[RENDERED_OBJECT_MAX_HEIGHT] );
//int colide_com_a_borda(sapo player);
void move_prop(entity *en, int direction);

entity *entities[ENTITIES_MAX_AMOUNT];

int main()
{
    /* get the info about screen */
    gettextinfo( &info );

    /* set normal cursor */
    _setcursortype( _NORMALCURSOR );

    /* clear the screen */
    clrscr();

    /* Desenha a borda */
    desenha_borda(X_MIN, Y_MIN, X_MAX, Y_MAX);

    entity *player = initialize_player();
    draw_prop( player );

    fgets();

    move_prop(player, 1);


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


void clean_previous_pos(render_data *obj) {

    gotoxy( obj->previous_pos->x, obj->previous_pos->y );

    for( int i = 0; i < obj->height; i++) {
        gotoxy( obj->previous_pos->x, (obj->previous_pos->y + i) );
        for( int j = 0; j < obj->width; j++) {

            // Aqui vai uma função pra identificar cenário e printar cenário ao invés de caractere em branco.
            putch( ' ' );
        }
    }

    return;
}


void draw_prop(render_data *obj) {

    clean_previous_pos( obj );

    gotoxy( obj->pos->x, obj->pos->y );

    for( int i = 0; i < obj->height; i++) {
        gotoxy( obj->pos->x, (obj->pos->y + i) );
        for( int j = 0; j < obj->width; j++) {
            putch( obj->content[i][j] );
        }
    }

    return;
}


render_data *create_render_data(
                    coordinates *pos,
                    int height,
                    int width,
                    char *content[RENDERED_OBJECT_MAX_HEIGHT] ) {

    render_data *r = malloc(sizeof(render_data));
    if (r == NULL) {
        return;
    }

    // Initialize previous_pos to 0;
    coordinates *previous_pos = malloc(sizeof(coordinates));
    if (previous_pos == NULL) {
        return;
    }
    previous_pos->x = 0;
    previous_pos->y = 0;
    r->previous_pos = previous_pos;

    r->pos = pos;
    r->height = height;
    r->width = width;

    for (int i = 0; i < height; i++ ) {
        r->content[i] = content[i];
    }

    return r;
}

void update_pos(entity *en, coordinates *new_pos) {
    render_data *r = en->render;

    free(r->previous_pos);

    r->previous_pos = r->pos;
    r->pos = new_pos;

    return;
}

coordinates *get_new_pos(entity *en, int direction) {

    coordinates *pos = malloc(sizeof(pos));

    if (pos == NULL) {
        return;
    }

    switch( direction ) {
        case 0:
        pos->y -= en->physics->y_speed;
        break;

        case 1:
        pos->x += en->physics->x_speed;
        break;

        case 2:
        pos->y += en->physics->y_speed;
        break;

        case 3:
        pos->y -= en->physics->x_speed;
        break;
    }

    return pos;
}

bool is_a_and_b_colliding_in_one_axis(int a, int a_length, int b, int b_length) {
    return !(b < (a + a_length) || (b + b_length) < a);
}

bool is_a_and_b_colliding(entity *a, entity *b) {
    render_data *r_a = a->render;
    render_data *r_b = b->render;

    return (
        is_a_and_b_colliding_in_one_axis(r_a->pos->x,
                                         r_a->width,
                                         r_b->pos->x,
                                         r_b->width) &&
        is_a_and_b_colliding_in_one_axis(r_a->pos->y,
                                         r_a->height,
                                         r_b->pos->y,
                                         r_b->height));
}

bool is_out_of_boundary(entity *en) {
    render_data *r = en->render;

    return !(
            r->pos->y <= Y_MIN ||
            r->pos->x >= X_MAX ||
            r->pos->y >= Y_MAX ||
            r->pos->x <= X_MIN
            );
}

bool is_enemy_colliding( entity *en ) {
    // Requires entity list <entities>

    for( int i = 0; i < ENTITIES_MAX_AMOUNT; i++) {
        if( entities[i]->is_active ) {
            if( is_a_and_b_colliding( en, entities[i] ) ) {
                return true;
            }
        }
    }

    return false;
}

int is_move_allowed(entity *en, coordinates *goal_pos) {
    // 1 - Hit the border
    if (is_out_of_boundary( en ))
        return -1;

    // 2 - Hit something else
    if (is_enemy_colliding( en ))
        return 1;

    return 0;
}

void move_prop(entity *en, int direction) {
    /* Directions:
    0 : up
    1 : right
    2 : down
    3 : left */

    // 1 - Pega nova coordinates
    coordinates *goal_pos = get_new_pos(en, direction);

    // 2 - Pode mover?
    int movement_code = is_move_allowed( en, goal_pos );
    if (!movement_code) {
        // Handle movement block
    }

    // 3 - Update position
    update_pos(en, goal_pos);
    draw_prop( en );

    return;
}

physics_data *create_physics_data(int x_speed,
                                 int y_speed) {
    physics_data *p = malloc(sizeof(physics_data));
    if( p == NULL ) {
        return;
    }
    p->x_speed = x_speed;
    p->y_speed = y_speed;

    return p;
}

entity *pack_entity(render_data *render,
                    physics_data *physics,
                    bool *is_ac) {
    entity *en = malloc(sizeof(entity));
    if (en == NULL) {
        return;
    }
    en->render = render;
    en->physics = physics;
    en->is_active = is_ac;

    return en;
}


entity *initialize_player() {
    coordinates default_pos = {
        .x = DEFAULT_PLAYER_X,
        .y = DEFAULT_PLAYER_Y
    };

    char *content[2] = {
        "  (00)  ",
        "\\^{  }^/"
    };

    render_data *r = create_render_data(&default_pos, SAPO_HEIGHT, SAPO_WIDTH, content);

    physics_data *physics = create_physics_data(DEFAULT_HORIZONTAL_SPEED, DEFAULT_VERTICAL_SPEED);

    entity *player = pack_entity(r, physics, DEFAULT_PLAYER_IS_ACTIVE);

    return player;
}

/*  TODO

- initialize entities list


*/
