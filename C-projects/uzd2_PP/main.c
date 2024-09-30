//LSP: 2413914
//el. paštas: adomas.bieliunas@mifstud.vu.lt
//2 užduotis, 6 variantas

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int main()
{
    int inp_num = 0;
    int list_num = 0;

    int scan_result = scanf("%d", &inp_num);
    if(inp_num < 0 || scan_result != 1)
    {
        printf("Neteisinga įvestis\n");
        return 1;
    }

    int min_num = INT_MAX;
    int max_num = INT_MIN;
    int data[inp_num];
    for (int i = 0; i < inp_num; i++)
    {
        scan_result = scanf("%d", &list_num);
        if(scan_result != 1)
        {
            printf("Neteisinga įvestis\n");
            return 1;
        }
        data[i] = list_num;

        if(list_num < min_num)
        {
            min_num = list_num;
        }
        if(list_num > max_num)
        {
            max_num = list_num;
        }
    }

    printf("\n1)\n");
    for (int i = 0; i < inp_num; i++)
    {
        if(data[i] >= min_num && data[i] <= min_num + (max_num - min_num) * (1/3.0f))
        {
            printf("%d ", data[i]);
        }
    }
    printf("\n\n2)\n");
    for (int i = 0; i < inp_num; i++)
    {
        if(data[i] > (min_num + (max_num - min_num) * (1/3.0f)) && data[i] < min_num + (max_num - min_num) * (2/3.0f))
        {
            printf("%d ", data[i]);
        }
    }
    printf("\n\n3)\n");
    for (int i = 0; i < inp_num; i++)
    {
        if(data[i] >= (min_num + (max_num - min_num) * (2/3.0f)) && data[i] <= max_num)
        {
            printf("%d ", data[i]);
        }
    }

    return 0;

}
