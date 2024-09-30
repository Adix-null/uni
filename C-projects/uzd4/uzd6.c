#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <string.h>

int count_digits(int n)
{
    int count = 0;

    while (n != 0)
    {
        n /= 10;
        count++;
    }

    return count;
}

int main()
{
    char* msg = "Ši programa tarp skaičių sekos randa skaičių su dugiausiai skaitemnų.\n"
    "Į programą yra įvedama teigiamų skaičių seka, kurios pabaigą žymi pirma įvesta neteigiama reikšmė.\n";
    printf("%s", msg);

    int max_digit_sum = 0;
    int max_digit_num_whole = 0;
    int max_digit_num_fraction = 0;
    for(int i = 0; 1 > 0; i++)
    {
        char buf[1000];
        char name[1000];
        memset(name, '\0', sizeof(name));
        name[0] = 'n';
        sprintf(buf, "%d", i + 1);
        strcat(name, buf);

        char* input;
        int iWhole;
        int iFraction;
        char* cWhole;
        char* cFraction;

        printf("%s: ", name);
        scanf("%s", input);
        char input_num[100];
        strcpy(input_num, input);

        if(strchr(input_num, '.') == NULL)
        {
            iWhole = atoi(input_num);
            iFraction = 0;
            if(input[0] == '0')
            {
                break;
            }
            if(iWhole == 0)
            {
                printf("Neteisinga įvestis\n");
                return 1;
            }
        }
        else
        {
            cWhole = strtok(input_num, ".");
            cFraction = strtok(NULL, ".");

            if(cWhole == NULL || cFraction == NULL)
            {
                printf("Neteisinga įvestis\n");
                return 1;
            }
            iWhole = atoi(cWhole);
            iFraction = atoi(cFraction);
        }

        if (iWhole < 0 || (iWhole == 0 && iFraction == 0))
        {
            break;
        }

        int digit_sum = count_digits(iWhole) + count_digits(iFraction);
        if(max_digit_sum < digit_sum)
        {
            max_digit_sum = digit_sum;
            max_digit_num_whole = iWhole;
            max_digit_num_fraction = iFraction;
        }
        printf("Sėkminga įvestis\n");
        memset(name, '\0', sizeof(name));
    }
    printf("Skaičius su daugiausiai skaitmenų: %d.%d", max_digit_num_whole, max_digit_num_fraction);

    return 0;
}
