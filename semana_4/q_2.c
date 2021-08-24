#include <stdio.h>
#include <stdlib.h>
#define VALOR 3

int main()
{
    float a;
    int i, k = 0;
    a = 9;

    for (i; i < VALOR; i++)
    {
        k = i;
        while (k <= (i + 1))
        {
            if (i % 2 == 0)
            {
                if (k % 2 == 0)
                    a = a + k * 2;
                a--;
            }
            else
            {
                a = a * 2;
            }
            printf("%4d,%4d,%8.2f \n", i, k, a);
            k++;
        }
    }
    int t = 2;
    if (t) {
        printf("he");
    } else if (t < 3) {
        printf("haha");
    }
    return 0;
}