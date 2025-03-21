#include <stdio.h>
#include <stdlib.h>

#define MAX_ITEMS 100
#define MAX_WEIGHT 1000

FILE *output;

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void knapsack(int weights[], int values[], int n, int maxWeight)
{
    fprintf(output, "\nANTRA DALIS: Vykdymas\n");
    int dp[n + 1][maxWeight + 1];
    int dbgcnt = 0;

    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= maxWeight; w++)
        {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i - 1] <= w)
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
            fprintf(output, "%d) p[%d][%d] = %d\n", ++dbgcnt, i, w, dp[i][w]);
        }
    }
    fprintf(output, "\nTREČIA DALIS: Rezultatai\n");
    fprintf(output, "Bandymų skaičius: %d\n", dbgcnt);
    fprintf(output, "Pasirinkti elementai:\n");
    int w = maxWeight;
    for (int i = n; i > 0 && dp[i][w] != 0; i--)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            fprintf(output, "%d:  svoris %d, kaina %d\n", i, weights[i - 1], values[i - 1]);
            w -= weights[i - 1];
        }
    }
    fprintf(output, "Galutinis rezultatas:  svoris %d, kaina %d\n", maxWeight - w, dp[n][maxWeight]);
}

int main()
{
    char *input_name = "inp.txt";
    char *output_name = "otp.txt";
    FILE *input = fopen(input_name, "r");

    output = fopen(output_name, "w");
    if (input == NULL)
    {
        fprintf(output, "Nepavyko atidaryti failo.");
        return -1;
    }

    int size;
    fscanf(input, "%d", &size);
    int *s = malloc(size * sizeof(int));
    int *k = malloc(size * sizeof(int));
    int c;

    for (int i = 0; i < size; i++)
    {
        fscanf(input, "%d", &s[i]);
    }
    for (int i = 0; i < size; i++)
    {
        fscanf(input, "%d", &k[i]);
    }
    fscanf(input, "%d", &c);

    fprintf(output, "2 užduotis. Adomas Bieliūnas, 1 kursas, 2 grupė, 1 pogrupis.\n");
    fprintf(output, "SĄLYGA. Duota N daiktų, kurių svoriai s1, s2, ..., sN, o kainos k1, k2, ..., kN. Programa turi sudaryti daiktų rinkinį, kurio kaina maksimali, o svoris neviršytų nurodyto svorio C. Spausdinti visus sprendinius. Vartotojas nurodo failą įvesti svorius, kainas ir C.\n");

    fprintf(output, "\nPIRMA DALIS: Duomenys\n");
    fprintf(output, "Daiktų kiekis n=%d\n", size);
    fprintf(output, "Svoriai s={");
    for (int i = 0; i < size - 1; i++)
    {
        fprintf(output, "%d, ", s[i]);
    }
    fprintf(output, "%d}\n", s[size - 1]);
    fprintf(output, "Kainos k={");
    for (int i = 0; i < size - 1; i++)
    {
        fprintf(output, "%d, ", k[i]);
    }
    fprintf(output, "%d}\n", k[size - 1]);
    fprintf(output, "Maksimali svorio apimtis c=%d\n", c);
    fprintf(output, "Įvesties failas: %s\n", input_name);
    fprintf(output, "Išvesties failas: %s\n", output_name);

    knapsack(s, k, size, c);

    return 0;
}