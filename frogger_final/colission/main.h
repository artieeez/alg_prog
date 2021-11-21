#ifndef COLISSION
#define COLISSION
#include "../models/headers/models.h"

bool is_out_of_boundary(COORDENADA pos1, COORDENADA pos2);
bool is_a_and_b_colliding_in_one_axis(int a, int a_length, int b, int b_length);
short testa_colisao(VEICULO carro, SAPO s);

#endif
