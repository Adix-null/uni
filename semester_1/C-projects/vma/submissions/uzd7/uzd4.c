#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>
#include <time.h>

void generateArray(int data[], int size, int low, int high)
{
    srand(time(NULL));
    for(int i = 0; i < size; i++)
    {
        data[i] = low + rand() % (high - low + 1);
    }
}

int main()
{
    return 0;
}
