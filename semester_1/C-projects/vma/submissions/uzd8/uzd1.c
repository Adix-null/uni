#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>

int* createArray(int size, int low, int high)
{
    int* arr = (int*)malloc(size * sizeof(int));

    if (arr == NULL)
    {
        return NULL;
    }

    srand(time(NULL));

    for (int i = 0; i < size; i++)
    {
        arr[i] = (rand() % (high - low + 1)) + low;
    }

    return arr;
}

int* createArrayAlt(int size, int low, int high)
{
    int* arr = (int*)malloc(size * sizeof(int));

    if (arr == NULL)
    {
        return NULL;
    }

    srand(time(NULL));

    for (int i = 0; i < size; i++)
    {
        *(arr + i) = (rand() % (high - low + 1)) + low;
    }

    return arr;
}


int main()
{
    return 0;
}
