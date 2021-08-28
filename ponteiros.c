#include <stdio.h>

int main(void) {

    char string_a[5] = {
        "Adam"
    };

    char string_b[] = {
        "Adam"
    };

    char *string_c = {
        "Adam"
    };


    char string_array__a[][6] = {
        "Adam",
        "Mike",
        "Artur",
    };

    char *string_array__b[3] = {
        "Adam",
        "Mike",
        "Artur",
    };

    char *string_array__c[] = {
        "Adam",
        "Mike",
        "Artur",
    };

    printf("Tamanho strings\n");
    printf("%lu\n", sizeof(string_a));
    printf("%lu\n", sizeof(string_b));
    printf("%lu\n\n", sizeof(string_c));
    printf("Tamanho vetores bidimensionais\n");
    printf("%lu\n", sizeof(string_array__a));
    printf("%lu\n", sizeof(string_array__b));
    printf("%lu\n\n", sizeof(string_array__c));
    printf("Conteudo vetores de strings\n");
    const ITERATION_COUNT = 3;
    for (int i = 0; i < ITERATION_COUNT; i++) {
        printf("%s\n", string_array__a[i]);
    }
    printf("\n");
    for (int i = 0; i < ITERATION_COUNT; i++) {
        printf("%s\n", string_array__b[i]);
    }
    printf("\n");
    for (int i = 0; i < ITERATION_COUNT; i++) {
        printf("%s\n", string_array__c[i]);
    }
}