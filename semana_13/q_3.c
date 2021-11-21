#include <stdio.h>

int contem_string(char string[], char substring[], int n);

int main(void) {
    char *s1 = "ababa";
    char *ss1 = "aba";
    char *s2 = "thor";
    char *ss2 = "r";
    char *s3 = "baba";
    char *ss3 = "aba";
    char *s4 = "";
    char *ss4 = "aba";
    int ex1 = 0, ex2, ex3, ex4;
    ex1 = contem_string(s1, ss1, 0);
    ex2 = contem_string(s2, ss2, 0);
    ex3 = contem_string(s3, ss3, 3);
    ex4 = contem_string(s4, ss4, 0);
    printf("ex1: %d\n", ex1);
    printf("ex2: %d\n", ex2);
    printf("ex3: %d\n", ex3);
    printf("ex4: %d\n", ex4);

    return 0;
}

int contem_string(char string[], char substring[], int n) {
    char *stringTmp = {'\0'};
    char *substringTmp = {'\0'};

    substringTmp = substring;

    if (*string == '\0') {
        return n;
    } else if (*string == *substring) {
        substringTmp++;
        n++;
    }
    
    stringTmp = string;
    stringTmp++;

    if (contem_string(stringTmp, substringTmp, n) != 0) {
      return 1;
    } else {
      return 0;
    }
}
