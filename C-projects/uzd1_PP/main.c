//LSP: 2413914
//el. paštas: adomas.bieliunas@mifstud.vu.lt
//1 užduotis, 6 variantas

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int input;
    int sq_num_count = 0;
    while (1)
    {
        int result = scanf("%d", &input);

        if(result != 1 || input < 0)
        {
            printf("Neteisinga įvestis\n");
            return 0;
        }
        if(input == 0)
        {
            break;
        }
        int sqrt_num = sqrt(input);

        if (sqrt_num * sqrt_num == input)
        {
            sq_num_count++;
        }
    }

    printf("Sekos narių sveikų skaičių kvadratų kiekis: %d\n", sq_num_count);

    return 0;
}
