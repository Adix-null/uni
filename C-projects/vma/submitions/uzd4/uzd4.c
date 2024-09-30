#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int input_check(char* name, int* var)
{
    printf("Kintamasis %s: ", name);
    int scan_result = scanf("%d", var);
    if(scan_result != 1 || *var < 1)
    {
        printf("Neteisinga įvestis\n");
        return 1;
    }
    printf("Sėkminga įvestis\n");
    return 0;
}

int dbd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mbk(int a, int b)
{
    return (a * b) / dbd(a, b);
}

int main()
{
    char* msg = "Ši programa atspausdina 3 natūralių skaičių didžiausią bendrą daliklį ir mažiausią bendrą kartotinį.\n"
    "Į programą yra įvedami 3 natūralūs skaičiai a,b,c.\n";
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

    printf("Didžiausias bendras daliklis: %d\n", dbd(dbd(a, b), c));
    printf("Mažiausias bendras kartotinis: %d\n", mbk(mbk(a, b), c));

    return 0;
}
