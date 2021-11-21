/*
Frooger

Feito por:
Artur Webber de Oliveira
João Pedro Telles Fava

*/

#include <conio2.h>
#include "constants.h"
#include "render/render.h"
#include "controllers/headers/game_loop.h"
#include "models/headers/models.h"
#include "models/headers/initializers.h"

int main(void) {
    VEICULO lista_veiculos[NUM_VEICULOS];
    SAPO lista_sapos[NUM_SAPO];
    JOGADOR jog;

    /* Inicializacoes */
    inicializa_sapos(lista_sapos);
    inicializa_jogador(&jog);

    /* clear the screen */
    clrscr();
    /* Desenha a borda */
    desenha_borda(X_MIN, Y_MIN, X_MAX, Y_MAX);

    /* Game loop */
    game_loop(
        &jog,
        lista_sapos,
        lista_veiculos);

    getch();
    return 0;
}
