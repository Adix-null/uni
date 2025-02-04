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

int main()
{
    int data[ARRAY_SIZE];
    int temp[ARRAY_SIZE];

    //int comp_count[TEST_SIZE][5];
    //int assgn_count[TEST_SIZE][5];
    //double time_taken[TEST_SIZE][5];

    double comp_count_avg[5];
    double assgn_count_avg[5];
    double time_taken_avg[5];

    char* names[5] = {"bubbleSort", "quickSort", "insertionSort", "selectionSort", "mergeSort"};
    void (*funcArr[5])(int[]) = {bubbleSort, quickSort, insertionSort, selectionSort, mergeSort};

    for(int i = 0; i < TEST_SIZE; i++)
    {
        fillArray(data, -1000, 1000);
        for(int j = 0; j < 5; j++)
        {
            memcpy(temp, data, ARRAY_SIZE * sizeof(int));

            comparison_count = 0;
            assignment_count = 0;
            clock_t start, end;
            double time_taken = 0.0f;
            start = clock();

            funcArr[j](data);

            end = clock();
            time_taken = ((double)(end - start)) * 1000000 / CLOCKS_PER_SEC;

            //comp_count[i][j] = comparison_count;
            //assgn_count[i][j] = assgn_count;
            //time_taken[i][j] = time_taken;

            comp_count_avg[j] += comparison_count / (TEST_SIZE * 1.0f);
            assgn_count_avg[j] += assignment_count / (TEST_SIZE * 1.0f);
            time_taken_avg[j] += time_taken / (TEST_SIZE * 1.0f);
            checkArray(data, true);

            memcpy(data, temp, ARRAY_SIZE * sizeof(int));
        }
    }

   printf("Algoritmų vidurkiai\n\n%15s | %-15s  | %-15s  | %-15s \n\n", "Pavadinimas", "Palyginimų sk.", "Priskyrimų sk.", "Laikas µs");

    for(int i = 0; i < 5; i++)
    {
        printf("%15s | %-15f | %-15f | %-5.2f\n", names[i], comp_count_avg[i], assgn_count_avg[i], time_taken_avg[i]);
    }


    return 0;
}
