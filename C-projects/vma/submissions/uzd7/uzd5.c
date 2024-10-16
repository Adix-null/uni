#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>

long getFileSize(char *fileName)
{
    FILE* file;
    file = fopen(fileName, "r");

    if (file == NULL)
    {
       return -1;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    return size;
}

int main()
{
    return 0;
}
