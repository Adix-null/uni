#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

typedef struct
{
    char* str1;
    char* str2;
    int n;
    char* exp_val;
} test_case;

char* app_string(char* str1, char* str2, unsigned int n)
{
    char* tmp = malloc(strlen(str1) + n + 1);

    if (tmp == NULL)
    {
        return NULL;
    }

    strcpy(tmp, str1);
    strncat(tmp, str2, n);
    return tmp;
}

int main()
{
    test_case tests[] = {
    {"vie", "nas", 2, "viena"},
    {"", "\0", INT_MAX, ""},
    {"r \n", "  ", 0, "r \n"},
    {"\0\0", "\t\t", 1, "\t"}
    };

    for(int i = 0; i < sizeof(tests) / sizeof (test_case); i++)
    {
        assert(strcmp(app_string(tests[i].str1, tests[i].str2, tests[i].n), tests[i].exp_val) == 0);
    }

    return 0;
}

