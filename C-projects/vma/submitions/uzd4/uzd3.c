#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int input_check(char* name, int* var)
{
    printf("Kintamasis %s: ", name);
    int scan_result = scanf("%d", var);
    if(scan_result != 1 || *var < 0)
    {
        printf("Neteisinga įvestis\n");
        return 1;
    }
    printf("Sėkminga įvestis\n");
    return 0;
}

int sequence_num(int a, int b, int c)
{
    if(c == 0)
    {
        return a;
    }
    else if(c == 1)
    {
        return b;
    }
    else
    {
        return sequence_num(a, b, c - 1) + sequence_num(a, b, c - 2);
    }
}

int main()
{
    char* msg = "Ši programa atspausdina c-ąjį skaičių fc, kur fc=fc-1+fc-2, o f0 = a ir f1 = b.\n"
    "Į programą yra įvedami 3 sveiki neneigiami skaičiai a,b,c.\n";
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

    printf("c-asis sekos narys: %d\n", sequence_num(a, b, c));

    return 0;
}
