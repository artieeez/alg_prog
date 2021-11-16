Estrutura do programa:

 - Programa principal em main.c

 - Estruturas em <estruturas.h>

 - Constantes em <constants.h>

 - Corpo das funções de leitura e escrita em <pdata.c>

 - Declarações das funções de leitura e escrita em <pdata.h>

Como compilar usando gcc:

gcc -g .\main.c .\pdata.c -o .\frogger.exe -lconio