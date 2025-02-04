//LSP: 2413914
//el. paštas: adomas.bieliunas@mifstud.vu.lt
//1 užduotis, 6 variantas

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int input;
    char extra_input;
    int sq_num_count = 0;

    do
    {
        int result = scanf("%d%c", &input, &extra_input);

        if(result != 2 || input < 0 || (extra_input != '\n' && extra_input != ' '))
        {
            printf("Neteisinga įvestis\n");
            return 0;
        }
        if(input == 0)
        {
            continue;
        }
        int sqrt_num = sqrt(input);

        if (sqrt_num * sqrt_num == input)
        {
            sq_num_count++;
        }
    } while (input != 0);

    printf("Sekos narių sveikų skaičių kvadratų kiekis: %d\n", sq_num_count);

    return 0;
}
