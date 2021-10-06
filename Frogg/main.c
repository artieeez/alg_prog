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

#define DEFAULT_HORIZONTAL_SPEED 8
#define DEFAULT_VERTICAL_SPEED 2

#define SAPO_WIDTH 8
#define SAPO_HEIGHT 2

#define DEFAULT_PLAYER_X 50
#define DEFAULT_PLAYER_Y 28

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

typedef struct box_model {
    coordinates *top_left;
    coordinates *bottom_right;
} box_model;

typedef struct render_data {
    coordinates *pos;
    coordinates *previous_pos;
    int height;
    int width;
    box_model *full_size;
    box_model *cropped;
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

coordinates *create_pos(int x, int y);
coordinates *get_new_pos(entity *en, int direction);
entity *initialize_player();
void draw_prop(int x, int y, int width, int height, char *content[RENDERED_OBJECT_MAX_HEIGHT]);
void desenha_borda(int x_min, int y_min, int x_max, int y_max);
render_data *create_render_data(
                    coordinates *pos,
                    int height,
                    int width,
                    char *content[RENDERED_OBJECT_MAX_HEIGHT] );
bool is_out_of_boundary( entity *en );
void move_prop(entity *en, int direction);
entity *pack_entity(render_data *render,
                    physics_data *physics,
                    bool is_ac);
void game_loop( entity *player);
int capture_action();

entity *entities[ENTITIES_MAX_AMOUNT];
int ENTITY_COUNT;

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
    ENTITY_COUNT = 0;

    draw_prop(player->render->pos->x,
              player->render->pos->y,
              player->render->width,
              player->render->height,
              player->render->content );

    game_loop( player );

    return 0;
}



/*  RENDERS  -----------------------------------------------------

*/
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


void draw_prop(int x, int y, int width, int height, char *content[RENDERED_OBJECT_MAX_HEIGHT]) {

    for( int i = 0; i < height; i++) {
        gotoxy( x, y );

        for( int j = 0; j < width; j++) {

            // Handle render crop at x axis when out of boundary
            if ( x > X_MIN && x < X_MAX) {
                putch( content[i][j] );
            }
        }

        y += 1;
    }

    return;
}


/*  COLISSION  ----------------------------------------------------

*/
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

bool is_out_of_boundary( entity *en ) {
    coordinates *pos = en->render->pos;
    int width = en->render->width;
    int height = en->render->height;

    bool a = pos->y            <= Y_MIN;
    bool b = (pos->x + width)  >= X_MAX + 1;
    bool c = (pos->y + height) >= Y_MAX + 1;
    bool d = pos->x            <= X_MIN;

    return ( a || b || c || d );
}

bool is_enemy_colliding( entity *en ) {
    // Requires entity list <entities>

    for( int i = 0; i < ENTITY_COUNT; i++) {
        if( entities[i]->is_active ) {
            if( is_a_and_b_colliding( en, entities[i] ) ) {
                return true;
            }
        }
    }

    return false;
}

int is_move_allowed(entity *en, coordinates *goal_pos) {
    render_data *render = create_render_data(goal_pos,
                                            en->render->height,
                                            en->render->width,
                                            en->render->content);
    physics_data *physics = en->physics;
    bool is_active = en->is_active;

    entity *tmp = pack_entity(render,
                              physics,
                              is_active);

    // 1 - Hit the border
    if (is_out_of_boundary( tmp )) {
        free(tmp->render->previous_pos);
        free(tmp->render);
        free(tmp);
        return -1;
    }

    // 2 - Hit something else
    if (is_enemy_colliding( tmp )) {
        free(tmp->render->previous_pos);
        free(tmp->render);
        free(tmp);
        return 1;
    }

    return 0;
}



/*  MOVEMENT  -----------------------------------------------------

*/
void move_prop(entity *en, int direction) {
    /* Directions:
    1 : up
    2 : right
    3 : down
    4 : left */

    // 1 - Pega nova coordinates
    coordinates *goal_pos = get_new_pos(en, direction);

    // 2 - Pode mover?
    int movement_code = is_move_allowed( en, goal_pos );
    if (movement_code) {
        // Handle movement block
        free(goal_pos);
        return;
    }

    // 3 - Update position
    update_pos(en, goal_pos);
    clean_previous_pos( en->render );
    draw_prop(en->render->pos->x,
              en->render->pos->y,
              en->render->width,
              en->render->height,
              en->render->content );

    return;
}



/*  CONSTRUCTORS  -------------------------------------------------

*/
// cropped box_model
void calculate_box_model(entity *en) {
    return;
}

// physics_data
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

// entity
entity *pack_entity(render_data *render,
                    physics_data *physics,
                    bool is_ac) {
    entity *en = malloc(sizeof(entity));
    if (en == NULL) {
        return;
    }
    en->render = render;
    en->physics = physics;
    en->is_active = is_ac;

    return en;
}

// pos
coordinates *create_pos(int x, int y) {
    coordinates *p = malloc(sizeof(coordinates));
    if( p == NULL ) {
        return;
    }
    p->x = x;
    p->y = y;
}

// box_model
box_model *create_box_model(coordinates *top_left, coordinates *bottom_right) {
    box_model *b = malloc(sizeof(box_model));
    if( b == NULL ) {
        return;
    }
    b->top_left = top_left;
    b->bottom_right = bottom_right;
    return b;
}

// render_data
render_data *create_render_data(
                    coordinates *pos,
                    int height,
                    int width,
                    char *content[RENDERED_OBJECT_MAX_HEIGHT] ) {

    render_data *r = malloc(sizeof(render_data));
    if (r == NULL) {
        return;
    }

    r->pos = pos;

    // Initialize previous_pos
    r->previous_pos = create_pos(pos->x, pos->y);

    r->height = height;
    r->width = width;

    for (int i = 0; i < height; i++ ) {
        r->content[i] = content[i];
    }

    // Box model
    coordinates *top_left = create_pos(r->pos->x, r->pos->y);
    coordinates *bottom_right = create_pos(r->pos->x + width,
                                           r->pos->y + height);
    r->full_size = create_box_model(top_left, bottom_right);


    return r;
}

// pos
void update_pos(entity *en, coordinates *new_pos) {
    render_data *r = en->render;

    free(r->previous_pos);

    r->previous_pos = r->pos;
    r->pos = create_pos( new_pos->x, new_pos->y );
    // Possível memory leak aqui

    return;
}

//
coordinates *get_new_pos(entity *en, int direction) {

    int x = en->render->pos->x;
    int y = en->render->pos->y;
    coordinates *pos = create_pos( x, y);

    switch( direction ) {
        case 1:
        pos->y -= en->physics->y_speed;
        break;

        case 2:
        pos->x += en->physics->x_speed;
        break;

        case 3:
        pos->y += en->physics->y_speed;
        break;

        case 4:
        pos->x -= en->physics->x_speed;
        break;
    }

    return pos;
}



/*  INITIALIZERS  -------------------------------------------------

*/
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



/*  CONTROLLERS  --------------------------------------------------

*/
int capture_action() {
    if (kbhit())
        {
            char c = getch();
            if ((int) c == -32)
            {

                switch(getch())
                {
                case ARROW_UP:
                    return 1;
                    break;
                case ARROW_RIGHT:
                    return 2;
                    break;
                case ARROW_DOWN:
                    return 3;
                    break;
                case ARROW_LEFT:
                    return 4;
                    break;
                }
            }
        }
    return 0;
}


void game_loop( entity *player ) {
    while( player->is_active ) {
        int action = capture_action();
        if(action) {
            // Movement
            if(action >= 1 && action <= 4)
            move_prop( player, action );
        }
    }
}

/* TODO
- hide cursor position after actions




*/
