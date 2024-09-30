#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fptr;

    fptr = fopen("loremipsum.txt", "r");

    if(fptr == NULL) {
      printf("Failo nuskaitymas nepavyko.\n");
    }

    // Close the file
    fclose(fptr);
        return 0;
}
