#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>

int getFactorial(int number)
{
    if(number < 0)
    {
        return 0;
    }
    if(number == 0 || number == 1)
    {
        return 1;
    }
    return number * getFactorial(number - 1);
}

int getFactorialNoRec(int number)
{
    if(number < 0)
    {
        return 0;
    }
    int result = 1;
    for(int i = 1; i <= number; i++)
    {
        result *= i;
    }
    return result;
}

int main()
{
    return 0;
}

