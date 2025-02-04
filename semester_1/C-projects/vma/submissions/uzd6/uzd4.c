#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>
#define prec 1000000

int validate_input(int* year, int* month, int* day)
{
    printf("Įveskite datą: ");
    int result = scanf("%4d-%2d-%2d", year, month, day);

    if (result != 3)
    {
        printf("Neteisinga įvestis\n");
        while((getchar()) != '\n');
        return 1;
    }
    printf("Sėkminga įvestis\n");

    return 0;
}

bool is_leap_year(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool validate_date(int year, int month, int day)
{

    if (month < 1 || month > 12)
    {
        return false;
    }

    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (is_leap_year(year) && month == 2)
    {
        days_in_month[1] = 29;
    }

    if (day < 1 || day > days_in_month[month - 1])
    {
        return false;
    }

    return true;
}

int day_of_week(int year, int month, int day)
{
    if (month < 3)
    {
        month += 12;
        year -= 1;
    }

    int k = year % 100;
    int j = year / 100;

    int day_of_week = (day + (13 * (month + 1)) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;

    return (day_of_week + 5) % 7;
}

int main()
{
    printf("Programa 6.4\n");
    printf("Ši programa nuskaito įvestą datą ir atspausdina, kokia tai savaitės diena. Datos formatas YYYY-MM-DD, savaičių dienų pavadinimai faile week.txt.\n");

    int result, year, month, day;
    bool valid_date;

    do
    {
        result = validate_input(&year, &month, &day);
        valid_date = validate_date(year, month, day);

        if(result == 0 && !valid_date)
        {
            valid_date = false;
            printf("Netinkama data\n");
        }
        else
        {
            valid_date = true;
        }

    }while(result != 0 || !valid_date);

    int weekday = day_of_week(year, month, day);

    FILE* file;
    char lines[7][256];

    file = fopen("week.txt", "r");
    if (file == NULL)
    {
        perror("Nepavyko atidaryti failo\n");
        return 1;
    }

    for (int i = 0; i < 7; i++)
    {
        if (fgets(lines[i], 256, file) == NULL)
        {
            if (feof(file))
            {
                printf("Failas turi mažiau nei 7 eilutes\n");
                break;
            }
            else
            {
                perror("Klaida skaitant failą\n");
                return 1;
            }
        }
    }

    fclose(file);

    printf("%d-%d-%d yra %s\n", year, month, day, lines[weekday]);


    return 0;
}
