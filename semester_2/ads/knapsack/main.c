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
    fprintf(output, "ANTRA DALIS: Vykdymas\n");
    int dp[n + 1][maxWeight + 1];
    int dbgcnt = 0;

    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= maxWeight; w++)
        {
            if (i == 0 || w == 0)
            {
                dp[i][w] = 0;
            }
            else if (weights[i - 1] <= w)
            {
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
            fprintf(output, "%d) p[%d][%d] = %d\n", ++dbgcnt, i, w, dp[i][w]);
        }
    }
    fprintf(output, "TREČIA DALIS: Rezultatai\n");
    fprintf(output, "1) Pasirinkti elementai:\n");
    int w = maxWeight;
    for (int i = n; i > 0 && dp[i][w] != 0; i--)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            fprintf(output, "%d:  svoris %d, kaina %d\n", i, weights[i - 1], values[i - 1]);
            w -= weights[i - 1];
        }
    }
    fprintf(output, "2) Galutinis rezultatas:  svoris %d, kaina %d\n", maxWeight - w, dp[n][maxWeight]);
}

int main()
{
    // output = fopen("otp.txt", "w");
    output = stdout;

    fprintf(output, "2 užduotis. Adomas Bieliūnas, 1 kursas, 2 grupė, 1 pogrupis.\n");
    fprintf(output, "SĄLYGA. Duota N daiktų, kurių svoriai s1, s2, ..., sN, o kainos k1, k2, ..., kN. Programa turi sudaryti daiktų rinkinį, kurio kaina maksimali, o svoris neviršytų nurodyto svorio C. Spausdinti visus sprendinius. Vartotojas nurodo failą įvesti svorius, kainas ir C.\n");

    int n[] = {1, 4, 5, 7, 10, 8, 3, 12, 9, 6};
    int k[] = {5, 4, 2, 9, 6, 11, 4, 17, 6, 8};
    int c = 18;
    int sz = sizeof(k) / sizeof(k[0]);

    fprintf(output, "PIRMA DALIS: Duomenys\n");
    fprintf(output, "1) Svoriai: ");
    for (int i = 0; i < sz; i++)
    {
        fprintf(output, "%d ", n[i]);
    }
    fprintf(output, "\n2) Kainos: ");
    for (int i = 0; i < sz; i++)
    {
        fprintf(output, "%d ", k[i]);
    }
    fprintf(output, "\n3) Maksimali svorio apimtis: %d\n", c);

    knapsack(n, k, sz, c);

    return 0;
}