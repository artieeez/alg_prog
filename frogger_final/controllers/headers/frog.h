#ifndef CON_FROG
#define CON_FROG

void move_sapo(SAPO *s, DIRECAO_MOVIMENTO dir);
int mata_sapo(ESTADO *estado, SAPO lista_sapos[], short *indice_sapo, VEICULO lista_veiculos[]);
void salva_sapo(ESTADO *estado);

#endif
