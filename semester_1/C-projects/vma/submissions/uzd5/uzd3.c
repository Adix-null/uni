#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

struct pair{
    int s1;
    int s2;
};

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
        return 2;
    }
    printf("Įvestis sėkminga.\n");
    return 0;
}

int main()
{
    printf("Ši programa atspausdina paprašo naudotojo įvesti norimą sandaugą, skaičių seką, ir atspausdina visas įvestų skaičių poras su 2 elementais kurių sandauga lygi norimai sandaugai. s - norima sandauga, n - sekos ilgis, x_n - n-tasis elementas.\n");

    int s, n, result;
    result = validate_input("s", &s, INT_MIN, INT_MAX);
    if(result == 1)
    {
        return 1;
    }
    rep:
    result = validate_input("n", &n, 1, INT_MAX);
    if(result == 1)
    {
        return 1;
    }
    if(result == 2)
    {
        printf("Pakartokite įvestį.\n");
        goto rep;
    }

    int data[n];

    for (int i = 0; i < n; i++)
    {
        char buf[1000];
        char name[1000];
        memset(name, '\0', sizeof(name));
        name[0] = 'x';
        sprintf(buf, "%d", i + 1);
        strcat(name, buf);

        validate_input(name, &data[i], INT_MIN, INT_MAX);
        if(result == 1)
        {
            return 1;
        }
    }


    struct pair pairs[n*n];
    int counter = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(data[i] * data[j] == s)
            {
                struct pair tmp_str;
                tmp_str.s1 = data[i];
                tmp_str.s2 = data[j];
                pairs[counter] = tmp_str;

                counter++;
            }
        }
    }

    for(int i = 0; i < counter; i++)
    {
        printf("(%d, %d) ", pairs[i].s1, pairs[i].s2);
    }
    if(counter == 0)
    {
        printf("Porų nėra.\n");
    }
}

