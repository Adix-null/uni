//LSP: 2413914
//el. pastas: adomas.bieliunas@mifstud.vu.lt
//2 uzduotis, 2 variantas

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>

#define ARRAY_SIZE 1000

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

int compare(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

int most_common_occurence(int (*data)[], int size)
{
    qsort(data, size, sizeof((*data)[0]), compare);

    int com_num = 0;
    int current_count = 1;
    int max_occ = 0;

    if(size == 1)
    {
        return (*data)[0];
    }

    for(int i = 0; i < size - 1; i++)
    {
        if((*data)[i] == (*data)[i + 1])
        {
            current_count++;
        }
        else
        {
            current_count = 1;
        }
        if(current_count > max_occ)
        {
            com_num = (*data)[i];
            max_occ = current_count;
        }
    }
    return com_num;
}


int main()
{
    int size;
    int data[ARRAY_SIZE];

    int result = validate_input("N", &size, 1, ARRAY_SIZE);
    if(result == 1 || result == 2)
    {
        return 0;
    }

    for(int i = 0; i < size; i++)
    {
        char name[20];
        sprintf(name, "n%d", i + 1);

        int num;
        result = validate_input(name, &num, INT_MIN, INT_MAX);
        if(result == 1 || result == 2)
        {
            return 0;
        }

        data[i] = num;
    }

    int com_num = most_common_occurence(&data, size);
    printf("Dazniausiai pasikartojantis skaicius: %d\n", com_num);

    return 0;
}
