#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>

int splitData(int data[], int size, int size_part, int **arr1, int **arr2)
{
     *arr1 = (int*)malloc(size_part * sizeof(int));
     *arr2 = (int*)malloc((size - size_part) * sizeof(int));

     if(*arr1 == NULL || *arr2 == NULL || size_part > size)
     {
        return -1;
     }

     for(int i = 0; i < size_part; i++)
     {
        (*arr1)[i] = data[i];
     }
     for(int i = 0; i < size - size_part; i++)
     {
        (*arr2)[i] = data[i + size_part];
     }

     return 0;
}

int main(int argc, char** argv)
{
    return 0;
}
