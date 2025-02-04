#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#include "func.h"

int comparison_count = 0;
int assignment_count = 0;

void fillArray(int array[ARRAY_SIZE], int min, int max)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = rand() % (max - min + 1) + min;
    }
}

void checkArray(int array[ARRAY_SIZE], bool asc)
{
    for(int i = 0; i < ARRAY_SIZE - 1; i++)
    {
        if(asc && (array[i] > array[i + 1]))
        {
            printf("Rūšiavimas nepavyko\n");
            return false;
        }
        if(!asc && (array[i] < array[i + 1]))
        {
            printf("Rūšiavimas nepavyko\n");
            return false;
        }
    }
    return true;
}


void printArray(int array[ARRAY_SIZE])
{
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void swap(int *a, int *b)
{
    assignment_count += 2;
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int array[ARRAY_SIZE])
{
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        for(int j = 0; j < ARRAY_SIZE - 1; j++)
        {
            comparison_count++;
            if(array[j] > array[j + 1])
            {
                swap(&(array[j]), &(array[j + 1]));
            }
        }
    }
}

void quickSort_1(int array[ARRAY_SIZE], int low, int high)
{
    if (low < high)
    {
        int pivot = array[high];
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            comparison_count++;
            if (array[j] < pivot)
            {
                i++;
                swap(&array[i], &array[j]);
            }
        }
        swap(&array[i + 1], &array[high]);

        quickSort_1(array, low, i);
        quickSort_1(array, i + 2, high);
    }
}

void quickSort(int array[ARRAY_SIZE])
{
    quickSort_1(array, 0, ARRAY_SIZE - 1);
}

void insertionSort(int array[ARRAY_SIZE])
{
    for (int i = 1; i < ARRAY_SIZE; i++)
    {
        int key = array[i];
        int j = i - 1;

        comparison_count++;
        while (j >= 0 && array[j] > key)
        {
            assignment_count++;
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

void selectionSort(int array[ARRAY_SIZE])
{
    for (int i = 0; i < ARRAY_SIZE - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < ARRAY_SIZE; j++)
        {
            comparison_count++;
            if (array[j] < array[minIndex])
            {
                minIndex = j;
            }
        }

        swap(&array[i], &array[minIndex]);
    }
}

void merge(int array[ARRAY_SIZE], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        comparison_count++;
        if (L[i] <= R[j])
        {
            assignment_count++;
            array[k] = L[i];
            i++;
        }
        else
        {
            assignment_count++;
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        assignment_count++;
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        assignment_count++;
        array[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort_1(int array[ARRAY_SIZE], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort_1(array, left, mid);
        mergeSort_1(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}
void mergeSort(int array[ARRAY_SIZE])
{
    mergeSort_1(array, 0, ARRAY_SIZE - 1);
}
