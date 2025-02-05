#include <stdio.h>
#include <stdlib.h>

int sum(int a, int b)
{
    return a + b;
}

int remainder(int a, int b, int* rem)
{
    *rem = a % b;
    return (a - *rem) / b;
}

int main()
{
    int a = 0, b = 0;
    printf("Įveskite 2 skaičius:\n");
    scanf("%d%d", &a, &b);

    if(b == 0)
    {
        printf("Dalyba iš 0 negalima\n");
        return 1;
    }

    int* rem;
    int s = sum(a, b);
    int dal = remainder(a, b, &rem);
    printf("Suma: %d\nDalmuo su liekana: %d liekana %d\n", s, dal, rem);

    return 0;
}
