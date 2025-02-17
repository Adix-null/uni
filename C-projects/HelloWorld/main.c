#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <assert.h>
#include <ctype.h>
#include <float.h>
#include <string.h>

void insert(char* source, char* dat)
{
    while(*source != '\0')
    {
        char temp = *source;
        *source = *dat;
        source++;
        dat++;
    }
}

int replaceString(char *source, char *toReplace, char *replacement)
{
    char buffer[1000];
    char *pos = strstr(source, toReplace);

    if (pos == NULL)
    {
        return 0;
    }

    int lenBefore = pos - source;
    strncpy(buffer, source, lenBefore);
    buffer[lenBefore] = '\0';

    strcat(buffer, replacement);
    strcat(buffer, pos + strlen(toReplace));
    strcpy(source, buffer);

    return strlen(replacement);
}

void removeAdjacentDuplicates(char *str)
 {
    if (str == NULL) return;

    int i = 0;
    int j = 0;

    while (str[i] != '\0')
    {
        if (i == 0 || str[i] != str[i - 1])
        {
            str[j] = str[i];
            j++;
        }
        i++;
    }

    str[j] = '\0';
}

void transform (char t[])
{
    char *german[10] = {"Null\0", "Eins\0", "Zwei\0", "Drei\0", "Vier\0", "Funf\0", "Sechs\0", "Sieben\0", "Acht\0", "Neun\0"};

    char* orPos = t;
    char *r = t;
    while(*r != '\0')
    {
        if(*r >= 'A' && *r <= 'Z')
        {
            *r += 'a' - 'A';
        }
        else if(*r >= 'a' && *r <= 'z')
        {
            *r -= 'a' - 'A';
        }
        else if(*r == '.' || *r == ',' || *r == ';' || *r == '-' || *r == ':' || *r == '_')
        {
            *r = ' ';
        }
        removeAdjacentDuplicates(r);
        r++;
    }
    r = orPos;
    while(*r != '\0')
    {
        if(*r >= '0' && *r <= '9')
        {
            replaceString(r, "0", german[0]);
            replaceString(r, "1", german[1]);
            replaceString(r, "2", german[2]);
            replaceString(r, "3", german[3]);
            replaceString(r, "4", german[4]);
            replaceString(r, "5", german[5]);
            replaceString(r, "6", german[6]);
            replaceString(r, "7", german[7]);
            replaceString(r, "8", german[8]);
            replaceString(r, "9", german[9]);
        }

        printf("%c", *r);
        r++;
    }
}

int main()
{
char d[] = "TesTAS wefweee ttt yyy ..,,.,. ;,.- T 1234567890 e                                                       \n";
transform(d);
    return 0;
}
