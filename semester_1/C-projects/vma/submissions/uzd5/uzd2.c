#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define ARR_SIZE 1000

int validate_input(char* name, int* var, int lower_bound, int upper_bound)
{
    printf("Įveskite %s: ", name);
    int result = scanf("%d", var);
    if(result != 1)
    {
        printf("Neteisinga įvestis.\n");
        return 1;
    }
    if(*var < lower_bound || *var > upper_bound)
    {
        printf("Įvesties reikšmė neatitinka nustatytų rėžių.\n");
        return 1;
    }
    printf("Įvestis sėkminga.\n");
    return 0;
}

int main()
{
    time(NULL);
    printf("Ši programa atspausdina pasirinktą kiekį atsitiktinių skaičių norimame intervale. Įvedami sveiki skaičiai: a - žemutinis intervalo limitas, b - aukštesnysis, c - reikšmių kiekis, neviršijantis 1000.\n");

    int data[ARR_SIZE] = {0};

    int a, b, c, result;
    result = validate_input("a", &a, INT_MIN, INT_MAX);
    if(result == 1)
    {
        return 1;
    }
    result = validate_input("b", &b, a, INT_MAX);
    if(result == 1)
    {
        return 1;
    }
    result = validate_input("c", &c, 0, ARR_SIZE);
    if(result == 1)
    {
        return 1;
    }

    for(int i = 0; i < c; i++)
    {
        //[A, B] --> [a, b]
        data[i] = (b - a) * (rand() / (1.0f * RAND_MAX)) + a;
    }

    print_array(data, c);
}

void print_array(int arr[], int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
