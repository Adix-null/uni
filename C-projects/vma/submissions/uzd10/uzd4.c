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
    char ch;
    int exp_val;
} test_case;

int search_string(char* str, char ch)
{
    char* res = strchr(str, ch);
    if(res == NULL)
        return -1;
    return res - str + 1;
}

int main()
{
    test_case tests[] = {
    {"cementas\"", 'e', 2},
    {"Tarpdisciplinininkas numeris 1", '1', 30},
    {"ed2dece3", '\0', 9},
    {" ", ' ', 1},
    {"\n e ", 'f', -1},
    {"", '\0', 1}
    };

    for(int i = 0; i < sizeof(tests) / sizeof (test_case); i++)
    {
        assert(search_string(tests[i].str, tests[i].ch) == tests[i].exp_val);
    }

    return 0;
}
