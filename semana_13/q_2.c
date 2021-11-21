int verificaExpressaoAuxiliar(char *expressao, int *n);
int verificaExpressao(char *expressao);

int main(void) {
  char *a = "( 38*(20+x)/80 )/128+(4/(38+85*(32-x)))";
  char *b = "( 38*(20+x)/80 )/128+(4/(38+85*(32-x))";
  char *c = ") 38*(20+x)/80 )/128+(4/(38+85*(32-x))(";
  char *d = "(38*(20+x)/80)/128*(4/x))-38+85*(32-x)*(33/y)";

  int resA = 0;
  int resB = 0;
  int resC = 0;
  int resD = 0;
  resA = verificaExpressao(a);
  resB = verificaExpressao(b);
  resC = verificaExpressao(c);
  resD = verificaExpressao(d);

  return 0;
}

int verificaExpressao(char *expressao) {
  int n = 0;
  n += verificaExpressaoAuxiliar(expressao, &n);

  if (n != 0) {
    return 1;
  }
  return 0;
}

int verificaExpressaoAuxiliar(char *expressao, int *n) {
  if (*expressao == '\0') {
    return 0;
  }
  
  if (*expressao == '(') {
    (*n)++;
  } else if (*expressao == ')') {
    (*n)--;
  }

  if (*n < 0) {
    return 0;
  } else {
    char *a = expressao;
    a++;

    return verificaExpressaoAuxiliar(a, n);
  }
}
