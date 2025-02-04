#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

int validate_input(char* name, int* var, int lower_bound, int upper_bound)
{
    char extra_input;
    printf("Įveskite %s: ", name);
    int result = scanf("%d%c", var, &extra_input);

    if(result != 2 || extra_input != '\n')
    {
        printf("Neteisinga įvestis.\n");
        //Clear scanf input buffer
        while ((extra_input = getchar()) != '\n' && extra_input != EOF);
        return 1;
    }
    else if(*var < lower_bound || *var > upper_bound)
    {
        printf("Blogas skaičius.\n");
        return 2;
    }

    printf("Įvestis sėkminga.\n");

    return 0;
}

unsigned long long int calc_factorial(int n)
{
    unsigned long long int res = 1;
    for(int i = 1; i <= n; i++)
    {
        res *= i;
    }
    return res;
}


int main()
{
    printf("Programa 6.1\n");
    printf("Ši programa apskaičiuoja įvesto teigiamo skaičiaus faktorialą ir jį išveda ekrane bei tekstiniame faile.\n");

    int n = 0;
    int result;

    do
    {
        result = validate_input("n", &n, 1, INT_MAX);

    } while(result != 0);

    unsigned long long int fact = calc_factorial(n);

    printf("N faktorialas: %llu", fact);

    FILE *fptr;

    fptr = fopen("out.txt", "w");

    fprintf(fptr, "%llu", fact);

    fclose(fptr);


    return 0;
}
