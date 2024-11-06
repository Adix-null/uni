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
    char* str;
    int exp_val;
} test_case;

int get_length(char* str)
{
    return str != NULL ? strlen(str) : -1;
}

int main()
{
    test_case tests[] = {
    {"Testavimas", 10},
    {"", 0},
    {"\n\\\0", 2},
    {0, -1}
    };

    for(int i = 0; i < sizeof(tests) / sizeof (test_case); i++)
    {
        assert(get_length(tests[i].str) == tests[i].exp_val);
    }

    return 0;
}
