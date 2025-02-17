#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define ARRAY_SIZE 100
#define TEST_SIZE 100

extern int comparison_count;
extern int assignment_count;

void bubbleSort(int array[ARRAY_SIZE]);

void quickSort(int array[ARRAY_SIZE]);

void insertionSort(int array[ARRAY_SIZE]);

void selectionSort(int array[ARRAY_SIZE]);

void mergeSort(int array[ARRAY_SIZE]);
