#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>

int showMenu(char *menuTitle, char *menuOptions[], int menuSize, char *inputMsg)
{
    int result = 0;
    int num = 0;

    do
    {
        printf("%s", menuTitle);

        for(int i = 0; i < menuSize; i++)
        {
            printf("%s\n", menuOptions[i]);
        }

        printf("%s", inputMsg);
        result = scanf("%d", &num);
        while((getchar()) != '\n');
    }while(result != 1 || num < 1 || num > menuSize);

    return num;
}

int main()
{
    return 0;
}
