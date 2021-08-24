#include <stdio.h>

int main(void) {
    int n;
    int i;
    n = 5;
    for(i = (n - 1); i >= 1; i = i - 1){
        n = n * i;
    }
    printf("%d\n", n);
    return 0;
}