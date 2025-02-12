#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int compare(const void* a, const void* b)
{
   return (*(int*)b - *(int*)a);
}

int main()
{
    int x1, y1, x2, y2, x3, y3;
    printf("x1: ");
    scanf("%d", &x1);
    printf("y1: ");
    scanf("%d", &y1);
    printf("x2: ");
    scanf("%d", &x2);
    printf("y2: ");
    scanf("%d", &y2);
    printf("x3: ");
    scanf("%d", &x3);
    printf("y3: ");
    scanf("%d", &y3);

    int distarr[3] = {
    (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2),
    (x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3),
    (x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1)
    };

    qsort(distarr, 3, sizeof(int), compare);

    int area = (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2;
    if(area != 0)
    {
        if(distarr[0] == distarr[1] + distarr[2])
        {
            printf("Trikampis status\n");
        }
        else
        {
            printf("Trikampis nėra status\n");
        }
    }
    else
    {
        printf("Blogas trikampis");
    }

    return 0;
}
