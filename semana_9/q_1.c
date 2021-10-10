#include <stdbool.h>

bool is_a_and_b_colliding_in_one_axis(int a, int a_length, int b, int b_length) {
    return (b <= (a + a_length) || (b + b_length) <= a);
}

short testa_colisao(int x1Obj1, int x2Obj1, int y1Obj1, int y2Obj1,
                    int x1Obj2, int x2Obj2, int y1Obj2, int y2Obj2) {
    
    bool x_axis_colission = is_a_and_b_colliding_in_one_axis(x1Obj1,
                                         x2Obj1 - x1Obj1,
                                         x1Obj2,
                                         x2Obj2 - x1Obj2);

    bool y_axis_colission = is_a_and_b_colliding_in_one_axis(y1Obj1,
                                         y2Obj1 - y1Obj1,
                                         y1Obj2,
                                         y2Obj2 - y1Obj2);

    return (short) (x_axis_colission && y_axis_colission);
}