#include <stdbool.h>
#include <conio.h>

#include "../models/headers/models.h"
#include "../constants.h"
#include "../render/render.h"
#include "../colission/main.h"

short desenha_veiculo(VEICULO carro, COLORS cor) {
    short out_of_boundary = (short)is_out_of_boundary(carro.envelope[0],
                                                      carro.envelope[1]);

    switch (carro.tipo) {
        case ESPORTE:
            desenha_esporte(carro, cor);
            break;
    }

    return out_of_boundary;
}

void desenha_lista_veiculos(VEICULO lista_veiculos[], bool apagar) {
    for (int i = 0; i < NUM_VEICULOS; i++) {
        VEICULO *tmp_veiculo = &lista_veiculos[i];
        COORDENADA *tmp_envelope1 = &lista_veiculos[i].envelope[0];
        COORDENADA *tmp_envelope2 = &lista_veiculos[i].envelope[1];

        desenha_veiculo(*tmp_veiculo,
                        COR_FUNDO);

        if (!apagar) {
            if (lista_veiculos[i].dir == DIR) {
                tmp_envelope1->x += tmp_veiculo->velocidade;
                tmp_envelope2->x += tmp_veiculo->velocidade;
            } else if (lista_veiculos[i].dir == ESQ) {
                tmp_envelope1->x -= tmp_veiculo->velocidade;
                tmp_envelope2->x -= tmp_veiculo->velocidade;
            }

            tmp_veiculo->valido = desenha_veiculo(*tmp_veiculo,
                                                  COR_VEIC);

            if (tmp_veiculo->valido) {
                if (tmp_envelope1->x >= X_MAX && tmp_veiculo->dir == DIR) {
                    tmp_envelope2->x -= tmp_envelope1->x - 1;
                    tmp_envelope1->x = 1;
                } else if (tmp_envelope2->x <= X_MIN && tmp_veiculo->dir == ESQ) {
                    tmp_envelope1->x += X_MAX;
                    tmp_envelope2->x += X_MAX;
                }
            }
        }
    }  // Fim for loop
    return;
}
