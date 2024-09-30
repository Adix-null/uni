#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <string.h>

//no templates :`(
int input_check_int(char* name, int* var)
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
int input_check_float(char* name, float* var)
{
    printf("Kintamasis %s: ", name);
    int scan_result = scanf("%f", var);
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
    char* msg = "Ši programa atspausdina įvesto skaičių sąrašo sumą, vidurkį ir didžiausią bei mažiausią skaičius.\n"
    "Į programą yra įvedamas sąrašo ilgio natūralus skaičius n ir po to n realiųjų skaičių.\n";
    printf("%s", msg);

    int n;
    if(input_check_int("n", &n) == 1)
    {
        return 1;
    }
    if(n < 1)
    {
        printf("n turi būti natūralus skaičius\n");
        return 1;
    }

    float min = FLT_MAX;
    float max = -FLT_MAX;
    float sum = 0.0f;
    float average = 0.0f;
    for(int i = 0; i < n; i++)
    {
        float number;
        char buf[(n / 10) + 2];
        char name[(n / 10) + 4];
        name[0] = 'n';
        sprintf(buf, "%d", i + 1);
        strcat(name, buf);
        if(input_check_float(name, &number) == 1)
        {
            return 1;
        }
        memset(name, '\0', sizeof(name));
        if(number < min)
        {
            min = number;
        }
        if(number > max)
        {
            max = number;
        }
        sum = sum + number;
    }
    average = sum / n;

    printf("Suma: %f\n", sum);
    printf("Vidurkis: %f\n", average);
    printf("Minimumas: %f\n", min);
    printf("Maksimumas: %f\n", max);

    return 0;
}
