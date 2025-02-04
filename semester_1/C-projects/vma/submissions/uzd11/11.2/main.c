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
    int m1[ARRAY_SIZE];
    int m2[ARRAY_SIZE];
    int m3[ARRAY_SIZE];

    char* file_name_1 = "dat1";
    char* file_name_2 = "dat2";
    int size = 0;

    fillArray(m1, ARRAY_SIZE, 0, 73);
    fillArray(m2, ARRAY_SIZE, 0, 73);
    fillArray(m3, ARRAY_SIZE, 0, 73);

    saveToFile(file_name_1, m1, ARRAY_SIZE);
    saveToFile(file_name_1, m3, ARRAY_SIZE);
    loadFromFile(file_name_1, m1, &size);

    saveToFile(file_name_2, m2, ARRAY_SIZE);
    loadFromFile(file_name_2, m3, &size);
    loadFromFile(file_name_1, m2, &size);

    printf(read_counter == 3 && write_counter == 3 ? "all good" : "something's wrong\n");

    return 0;
}
