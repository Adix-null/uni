#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int input_check(char* name, int* var)
{
    printf("Kintamasis %s: ", name);
    int scan_result = scanf("%d", var);
    if(scan_result != 1)
    {
        printf("Neteisinga įvestis\n");
        return 1;
    }
    printf("Sėkminga įvestis\n");
    return 0;
}

int main()
{
    char* msg = "Ši programa atspausdina visus teigiamus skaičius iš intervalo (a; b], kurie dalijasi iš skaičiaus c su liekana 1.\n"
    "Į programą yra įvedami 3 sveiki skaičiai a,b,c.\n";
    printf("%s", msg);

    int a;
    int b;
    int c;
    if(input_check("a", &a) == 1)
    {
        return 1;
    }
    if(input_check("b", &b) == 1)
    {
        return 1;
    }
    if(input_check("c", &c) == 1)
    {
        return 1;
    }

    printf("Skaičiai atitinkantys reikalavimus: ");
    for(int i = a + 1; i <= b; i++)
    {
        if(i % c == 1)
        {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}
