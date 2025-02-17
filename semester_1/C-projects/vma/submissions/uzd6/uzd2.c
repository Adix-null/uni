#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

#define prec 1000000

int validate_input(char* name, double* var, double lower_bound, double upper_bound, FILE* file)
{
    printf("%s: ", name);
    int result = fscanf(file, "%lf", var);

    if(result != 1)
    {
        printf("Neteisinga įvestis.\n");
        return 1;
    }
    else if(*var < lower_bound || *var > upper_bound)
    {
        printf("Blogas skaičius.\n");
        return 2;
    }

    int int_part = (int) *var;
    double fractional_part = *var - int_part;

    fractional_part = (round(fractional_part * prec) / prec) * 1000;

    if ((int)fractional_part != fractional_part)
    {
        printf("Skaičius turi daugiau nei 3 skaičius po kablelio.\n");
        return 3;
    }

    printf("Įvestis sėkminga.\n");

    return 0;
}

int main()
{
    printf("Programa 6.2\n");
    printf("Ši programa apskaičiuoja įvesto skaičiaus ilgį ir jį išveda ekrane. Skaičius turi būti ne mažesnis už 10 ir nedidesnis už 1000, su ne daugiau kaip 3 skaičiais po kablelio.\n");

    double n = 0;
    int result;
    char line[256];
    int length = 0;

    FILE *file;
    file = fopen("in.txt", "r");
    if (file == NULL)
    {
        printf("Nepavyko atidaryti failo.\n");
        return 1;
    }

    do
    {
        result = validate_input("n", &n, 10, 1000, file);

        if(result != 0)
        {
            do
            {
                char file_name[100];
                printf("Įveskite kito failo pavadinimą: ");
                scanf("%s", &file_name);

                //Remove the newline character from the input if present
                file_name[strcspn(file_name, "\n")] = 0;

                file = fopen(file_name, "r");
                if (file == NULL)
                {
                    printf("Nepavyko atidaryti failo.\n");
                    fseek(stdin,0,SEEK_END);
                }
            }while(file == NULL);
        }
        else
        {
            rewind(file);
            length = strlen(fgets(line, sizeof(line), file));
        }

    } while(result != 0);

    printf("Skaičiaus ilgis: %d\n", length);

    return 0;
}
