#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(void)
{
    char name[6] = {'A', 'r', 't', 'u', 'r', '\0'};
    char name1[] = "Artur";
    char *name2 = "Artur";
    char *name3 = malloc(7 * sizeof(char));
    fgets(name3, 7, stdin);
    char *pos;
    if ((pos=strchr(name3, '\n')) != NULL)
    {
        *pos = '\0';
    }

    int x = strlen(name);
    int x1 = strlen(name1);
    int x2 = strlen(name2);
    int x3 = strlen(name3);
    printf("%s\n%i\n", name, x);
    printf("%s\n%i\n", name1, x1);
    printf("%s\n%i\n", name2, x2);
    printf("%s\n%i\n", name3, x3);
    free(name3);
    return 0;
}