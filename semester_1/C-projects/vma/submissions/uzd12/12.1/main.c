#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "func.h"

int main()
{
    int data[ARRAY_SIZE];
    int temp[ARRAY_SIZE];

    fillArray(data, 0, 37);

    void (*funcArr[])(int[]) = {bubbleSort, quickSort, insertionSort, selectionSort, mergeSort};

    for(int i = 0; i < 5; i++)
    {
        memcpy(temp, data, ARRAY_SIZE * sizeof(int));
        funcArr[i](data);
        checkArray(data, true);
        memcpy(data, temp, ARRAY_SIZE * sizeof(int));
    }


    return 0;
}
