#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>

int getPositiveNumber(char *msg)
{
    int result = 0;
    int num = 0;

    do
    {
        printf("%s", msg);
        result = scanf("%d", &num);
        while((getchar()) != '\n');
    }while(result != 1);

    return num;
}

int main()
{
    return 0;
}

