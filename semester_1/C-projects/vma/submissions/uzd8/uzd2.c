#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>

typedef struct
{
    long int size;
    char* name;
} fl;

int compare(const void* a, const void* b)
{
    fl* fl_a = (fl*)a;
    fl* fl_b = (fl*)b;

    if (fl_a->size > fl_b->size)
        return 1;
    else
        return -1;
}

char* find_max_file_size(int argc, char** name)
{
    int cnt = 0;
    fl files[argc - 1];
    for(int i = 1; i < argc; i++)
    {
        FILE* file = fopen(name[i], "rb");
        if (file != NULL)
        {
            fseek(file, 0, SEEK_END);
            fl tmp;
            tmp.name = name[i];
            tmp.size = ftell(file);
            files[cnt] = tmp;
            fclose(file);
            ++cnt;
        }
    }

    qsort(files, argc, sizeof(fl), compare);

    return files[cnt - 1].name;
}

int main(int argc, char** argv)
{
    return 0;
}
