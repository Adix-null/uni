#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>
#include <regex.h>

int validate_input(char** mail)
{
    char email[256];
    printf("Įveskite el. pašto adresą: ");
    scanf("%255s", &email);
    *mail = email;

    const char *pattern = "^[^@]+@[^@]+\\.[^@]+$";
    regex_t regex;
    int result;

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result)
    {
        fprintf(stderr, "Nepavyko kompiliuoti regex.\n");
        return 0;
    }
    result = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    if(result == 1)
    {
        printf("Netinkama įvestis\n");
        return 1;
    }

    printf("Sėkminga įvestis\n");

    return 0;
}

int main()
{
    printf("Programa 6.5\n");
    printf("Ši programa patikrina, ar įvestis yra teisingas el. pašto adresas. Jei taip, tuomet yra atspausdinamas domenas. Visi pateikti adresai saugomi emails.txt faile.\n");

    int result;
    char* email;
    char* domain;

    do
    {
        result = validate_input(&email);

    }while(result != 0);

    char *at_sign = strchr(email, '@');
    domain = at_sign + 1;
    printf("%s\n", domain);

    strcat(email, "\0");
    char otp[1000];
    strcpy(otp, email);

    FILE* file;
    file = fopen("emails.txt", "a");
    if (file == NULL)
    {
        printf("Nepavyko atidaryti failo\n");
        return 1;
    }
    fprintf(file, "%s\n", otp);
    fclose(file);


    return 0;
}
