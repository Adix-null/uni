#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "file.h"

int read_counter = 0;
int write_counter = 0;

void saveToFile(char* file_name, int array[ARRAY_SIZE], int size)
{
    FILE *file = fopen(file_name, "wb");
    if (file == NULL)
    {
        perror("Klaida atidarant failą");
        return;
    }
    write_counter++;

    fwrite(&size, sizeof(int), 1, file);
    fwrite(array, sizeof(int), size, file);

    fclose(file);
}

void loadFromFile(char* file_name, int array[ARRAY_SIZE], int* size)
{
    FILE *file = fopen(file_name, "rb");
    if (file == NULL)
    {
        perror("Klaida atidarant failą");
        return NULL;
    }

    if (fread(size, sizeof(int), 1, file) != 1)
    {
        perror("Klaida skaitant dydį");
        fclose(file);
        return NULL;
    }

    if (fread(array, sizeof(int), *size, file) != *size)
    {
        perror("Klaida skaitant duomenis");
        fclose(file);
        return NULL;
    }
    read_counter++;

    fclose(file);
    return array;
}

void fillArray(int array[ARRAY_SIZE], int size, int min, int max)
{
    srand(time(NULL));

    for (int i = 0; i < size; i++)
    {
        array[i] = rand() % (max - min + 1) + min;
    }
}

void printArray(int array[ARRAY_SIZE], int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void compArrays(int arr1[ARRAY_SIZE], int arr2[ARRAY_SIZE])
{
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        if(arr1[i] != arr2[i])
        {
            printf("something's wrong\n");
            return;
        }
    }
    printf("all good\n");
}