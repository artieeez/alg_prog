#include <stdio.h>

int main(void) {
    int x=5, a;
    int *p, *q;
    int w[10]={1,3,5,7,9};
    q=&w[3];
    p=q+(w[4]/3);
    x+=*q;

    int a1 = *(w+3);
    int b1 = *(q-2);
    int c1 = *&w[1];
    int d1 = *p+1+*q;
    int e1 = *(p+1)/(*q)+*&x;
}