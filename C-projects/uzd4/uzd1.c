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
    char* msg = "Ši programa apskaičiuoja kvadratinės lygties ax^2+bx+c=0 sprendinius.\n"
    "Į programą yra įvedami lygties koeficientai, 3 sveiki skaičiai a,b,c.\n";
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

    int det = b * b - 4 * a * c;
    if(det > 0)
    {
        printf("Sprendinių skaičius: 2\n");
        printf("x1=%f; x2=%f\n", (-b + sqrt(det)) / (2.0f * a), (-b - sqrt(det)) / (2.0f * a));
    }
    else if(det == 0)
    {
        printf("Sprendinių skaičius: 1\n");
        printf("x=%f\n", -b / (2.0f * a));
    }
    else
    {
        printf("Sprendinių nėra\n");
    }

    return 0;
}
