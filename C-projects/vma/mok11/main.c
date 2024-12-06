#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "file.h"

int main()
{
    int data_write[ARRAY_SIZE];
    int data_read[ARRAY_SIZE];
    int size = 0;
    char* file_name = "inp";

    fillArray(data_write, ARRAY_SIZE, 0, 73);
    printArray(data_write, ARRAY_SIZE);
    saveToFile(file_name, data_write, ARRAY_SIZE);
    loadFromFile(file_name, data_read, &size);
    printf("\n");
    printArray(data_read, size);
    compArrays(data_write, data_read);

    return 0;
}
