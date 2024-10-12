#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>

#define prec 1000000

int validate_input(char* name, double *var)
{
    printf("Įveskite %s: ", name);
    for(int i = 0; i < 3; i++)
    {
        char separator;
        int result = scanf("%lf%c", (double*)&var[i], &separator);

        if(result != 2 || (separator != ';' && i != 3))
        {
            printf("Neteisinga įvestis.\n");
            return 1;
        }
        printf("Įvestis sėkminga.\n");
    }

    return 0;
}

int compare(const double* a, const double* b)
{
   return (*a - *b);
}

int main()
{
    printf("Programa 6.3\n");
    printf("Ši programa tarp 3 įvestų skaičių randa vidurinį pagal reikšmę. Skaičiai skiriami kabliataškiais. Rastas skaičius išvedamas rezultatų faile pagal įvestą pavadinimą su pabaiga .txt.\n");

    double data[3];
    int result;

    do
    {
        result = validate_input("seką", data);

        if(result != 0)
        {
            memset(data, 0, sizeof (data));
            while ((getchar()) != '\n');
        }

    } while(result != 0);

    qsort(data, sizeof(data) / sizeof(data[0]), sizeof(double), compare);

    bool name_ok = false;
    while(!name_ok)
    {
        char name[255];
        scanf("%s", &name);
        // Remove trailing newline if present
        name[strcspn(name, "\n")] = 0;

        int length = strlen(name);

        if (length >= 4 && strcmp(name + length - 4, ".txt") == 0)
        {
            FILE *file;
            file = fopen(name, "w");

            fprintf(file, "%lf", data[1]);

            fclose(file);
            name_ok = true;
        }
        else
        {
            while ((getchar()) != '\n');
            printf("Netinkamas failo pavadinimas\n");
        }
    }

    return 0;
}
