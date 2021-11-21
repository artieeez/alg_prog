#include <stdbool.h>
#include "../models/headers/models.h"
#include "../constants.h"

bool is_out_of_boundary(COORDENADA pos1, COORDENADA pos2) {
    short xc1 = pos1.x;
    short yc1 = pos1.y;
    short xc2 = pos2.x;
    short yc2 = pos2.y;

    short width = xc2 - xc1;
    short height = yc2 - yc1;

    bool a = yc1 <= Y_MIN;
    bool b = (xc1 + width) >= X_MAX + 1;
    bool c = (yc1 + height) >= Y_MAX + 1;
    bool d = xc1 <= X_MIN;

    return (a || b || c || d);
}

bool is_a_and_b_colliding_in_one_axis(int a, int a_length, int b, int b_length) {
    return !(b > (a + a_length) || (b + b_length) < a);
}

short testa_colisao(VEICULO carro, SAPO s) {
    bool x_axis_colission = is_a_and_b_colliding_in_one_axis(
        carro.envelope[0].x,
        carro.envelope[1].x - carro.envelope[0].x,
        s.envelope[0].x,
        s.envelope[1].x - s.envelope[0].x);

    bool y_axis_colission = is_a_and_b_colliding_in_one_axis(
        carro.envelope[0].y,
        carro.envelope[1].y - carro.envelope[0].y,
        s.envelope[0].y,
        s.envelope[1].y - s.envelope[0].y);

    return (short)(x_axis_colission && y_axis_colission);
}
