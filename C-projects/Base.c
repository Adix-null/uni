#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>

int validate_input(char* name, int* input, int lower_bound, int upper_bound)
{
    char extra_input;
    printf("Iveskite %s: \n", name);
    int result = scanf("%d%c", input, &extra_input);

    if(result != 2 || (extra_input != '\n' && extra_input != ' '))
    {
        printf("Neteisinga ivestis\n");
        return 1;
    }
    else if(*input < lower_bound || *input > upper_bound)
    {
        printf("Netinkamas skaicius\n");
        return 2;
    }
    return 0;
}

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int compare_cst(const void* a, const void* b)
{
    fl* fl_a = (fl*)a;
    fl* fl_b = (fl*)b;

    if (fl_a->size > fl_b->size)
        return 1;
    else
        return -1;
}

void print_array(int* data, int size, const char* format)
{
    for(int i = 0; i < size; i++)
    {
        printf(format, *(data + i));
    }
    printf("\n");
}

int* create_random_array(int size, int lower, int upper)
{
    int* arr = (int*)malloc(size * sizeof(int));

    srand(time(NULL));

    for (int i = 0; i < size; i++)
    {
        arr[i] = (rand() % (upper - lower + 1)) + lower;
    }

    return arr;
}

int main()
{
    return 0;
}

