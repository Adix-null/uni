#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define SIGN(x) ((x) > 0 ? 1 : ((x) < 0 ? -1 : 0))

typedef struct
{
    char* str1;
    char* str2;
    int exp_val;
} test_case;

int compare_strings(char* str1, char* str2)
{
    return strcmp(str1, str2);
}

int main()
{
    test_case tests[] = {
    {"Testavimas", "Testavimas", 0},
    {"00\0", "000", -1},
    {"", "", 0},
    {" ", "", 1},
    {"\t", "\\ ", -1},
    };

    for(int i = 0; i < sizeof(tests) / sizeof (test_case); i++)
    {
        assert(SIGN(compare_strings(tests[i].str1, tests[i].str2)) == tests[i].exp_val);
    }

    return 0;
}
