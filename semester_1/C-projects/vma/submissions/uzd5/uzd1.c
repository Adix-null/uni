#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define ARR_SIZE 10

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
    printf("Ši programa atlieka įvairius veiksmus su masyvais ir naudotojo įvesstimi.\nVisuose atvejuose įvedami sveiki skaičiai, x - pozicija masyve pradedant nuo 0, y - reikšmė.\n");

    int data[ARR_SIZE] = {0};

    print_array(data, ARR_SIZE);

    data[0] = 1;
    data[3] = 2;
    data[9] = 3;

    delete_element(2, data, ARR_SIZE);
    insert_element(6, 4, data, ARR_SIZE);
    print_array(data, ARR_SIZE);

    int x, y, result;

    printf("Masyvo skaičius pozicijoje x įgaus reikšmę y.\n");
    result = validate_input("x", &x, 0, ARR_SIZE - 1);
    if(result == 1)
    {
        return 1;
    }
    result = validate_input("y", &y, INT_MIN, INT_MAX);
    if(result == 1)
    {
        return 1;
    }

    data[x] = y;
    print_array(data, ARR_SIZE);

    printf("Masyvo skaičius pozicijoje x bus ištrintas.\n");
    result = validate_input("x", &x, 0, ARR_SIZE - 1);
    if(result == 1)
    {
        return 1;
    }

    delete_element(x, data, ARR_SIZE);
    print_array(data, ARR_SIZE);

    printf("Masyvo pozicijoje x bus įterpta reikšmė y.\n");
    result = validate_input("x", &x, 0, ARR_SIZE - 1);
    if(result == 1)
    {
        return 1;
    }
    result = validate_input("y", &y, INT_MIN, INT_MAX);
    if(result == 1)
    {
        return 1;
    }
    insert_element(x, y, data, ARR_SIZE);

    print_array(data, ARR_SIZE);


    return 0;
}

void delete_element(int pos, int arr[], int sz)
{
    for(int i = pos; i < sz - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    arr[sz - 1] = 0;
}


void insert_element(int pos, int val, int arr[], int sz)
{
    for(int i = sz - 2; i > pos - 1; i--)
    {
        arr[i + 1] = arr[i];
    }
    arr[pos] = val;
}

void print_array(int arr[], int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

