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
    SAPO lista_sapos[NUM_SAPO];
    JOGADOR jog;

    /* Inicializacoes */
    inicializa_jogador(&jog);

    /* Game loop */
    game_loop(
        &jog,
        lista_sapos);

    getch();
    return 0;
}

/*
Itens não atendidos: 

16. Ranking

*/

