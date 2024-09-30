//LSP: 2413914
//el. paštas: adomas.bieliunas@mifstud.vu.lt
//2 užduotis, 6 variantas

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>

void output_segment(float lower_bound, float upper_bound, int data[], int size, int occurence, bool include)
{
    printf("\n%d) ", occurence);
    for (int i = 0; i < size; i++)
    {
        if(include)
        {
            if(data[i] >= lower_bound && data[i] <= upper_bound)
            {
                printf("%d ", data[i]);
            }
        }
        else
        {
            if(data[i] > lower_bound && data[i] < upper_bound)
            {
                printf("%d ", data[i]);
            }
        }
    }
    printf("\n");
}

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

    output_segment(min_num, min_num + (max_num - min_num) * (1 / 3.0f), data, inp_num, 1, true);
    output_segment(min_num + (max_num - min_num) * (1 / 3.0f), min_num + (max_num - min_num) * (2 / 3.0f), data, inp_num, 2, false);
    output_segment(min_num + (max_num - min_num) * (2 / 3.0f), max_num, data, inp_num, 3, true);

    return 0;

}
