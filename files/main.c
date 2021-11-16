#include <stdio.h>

/* int main(void) {
    FILE *f = fopen("teste.txt", "r");
    if (f == NULL) {
        return 1;
    }
    char str[20] = {0};

    //fgets(str, sizeof(str), f);
    //fscanf(f, "%s", str);
    char c = fgetc(f);
    if (c == 't') {
      printf("deu certo");
    } else {
      printf("erro");
    }

    fclose(f);
    return 0;
} */


// C program to illustrate fgetc() function
#include <stdio.h>
 
int main ()
{
    // open the file
    FILE *fp = fopen("teste.txt","r");
 
    // Return if could not open file
    if (fp == NULL)
      return 0;
 
    do
    {
        // Taking input single character at a time
        char c = fgetc(fp);
 
        // Checking for end of file
        if (feof(fp))
            break ;
 
        printf("%c", c);
    }  while(1);
 
    fclose(fp);
    return(0);
}