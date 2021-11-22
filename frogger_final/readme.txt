Estrutura do programa:

 - Programa principal em main.c

 - Estruturas em "models/headers/models.h"

 - Inicializadores em "models/initializers.c"

 - Controllers em "controllers/*"

 - Constantes em "constants.h"

 - Funções de colisão em "colission/main.c"

 - Funções responsáveis por desenhar na tela em "render/"

 - Funções responsáveis por I/O de informações em "persistent_data/"

Como compilar usando gcc:

gcc -g .\main.c .\persistent_data\progress.c .\render\render.c .\models\initializers.c .\colission\main.c .\controllers\vehicles.c .\controllers\player.c .\controllers\frog.c .\controllers\game_loop.c -o .\main.exe -lconio
