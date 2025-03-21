#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX 1000

FILE *output;
int dbgcnt = 1;

int max(int a, int b)
{
    return (a > b) ? a : b;
}

typedef struct
{
    int items[MAX];
    int count;
} Combination;

// Array to store combinations
Combination combinations[MAX];
int combCount = 0;

void findCombinations(int dp[][MAX], int weights[], int values[], int n, int w, int currentComb[], int idx)
{
    if (w == 0 || n == 0)
    {
        Combination newComb;
        newComb.count = idx;
        for (int i = 0; i < idx; i++)
            newComb.items[i] = currentComb[i];
        combinations[combCount++] = newComb;
        return;
    }

    if (dp[n][w] == dp[n - 1][w])
    {
        fprintf(output, "%d) ", dbgcnt++);
        fprintf(output, "Praleidžiamas daiktas %d su svoriu %d\n", n, w);
        findCombinations(dp, weights, values, n - 1, w, currentComb, idx);
    }

    if (weights[n - 1] <= w && dp[n][w] == dp[n - 1][w - weights[n - 1]] + values[n - 1])
    {
        fprintf(output, "%d) ", dbgcnt++);
        fprintf(output, "Įtraukiamas daiktas %d su svoriu %d\n", n, w);
        currentComb[idx] = n;
        findCombinations(dp, weights, values, n - 1, w - weights[n - 1], currentComb, idx + 1);
    }
}

void knapsack(int weights[], int prices[], int n, int maxWeight)
{
    fprintf(output, "\nANTRA DALIS: Vykdymas\n");
    int dp[n + 1][MAX];
    memset(dp, 0, (n + 1) * MAX * sizeof(int));

    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= maxWeight; w++)
        {
            if (weights[i - 1] <= w)
                dp[i][w] = (prices[i - 1] + dp[i - 1][w - weights[i - 1]] > dp[i - 1][w])
                               ? prices[i - 1] + dp[i - 1][w - weights[i - 1]]
                               : dp[i - 1][w];
            else
                dp[i][w] = dp[i - 1][w];
            fprintf(output, "%d) ", dbgcnt++);
            fprintf(output, "dp[%d][%d] = %d\n", i, w, dp[i][w]);
        }
    }

    int currentComb[MAX];
    findCombinations(dp, weights, prices, n, maxWeight, currentComb, 0);

    fprintf(output, "\nTREČIA DALIS: Rezultatai\n");
    fprintf(output, "Bandymų skaičius: %d\n", dbgcnt - 1);
    // fprintf(output, "Galutinis rezultatas:  svoris %d, kaina %d\n", maxWeight, dp[n][maxWeight]);
    fprintf(output, "Galimos kombinacijos:\n");
    for (int i = 0; i < combCount; i++)
    {
        fprintf(output, "%d) {", i + 1);
        for (int j = 0; j < combinations[i].count - 1; j++)
        {
            int idx = combinations[i].items[j] - 1;
            fprintf(output, "s%d, ", idx + 1);
        }
        fprintf(output, "s%d} Svoris=", combinations[i].items[combinations[i].count - 1]);
        int ss = 0;
        for (int j = 0; j < combinations[i].count - 1; j++)
        {
            int idx = combinations[i].items[j] - 1;
            fprintf(output, "%d+", weights[idx]);
            ss += weights[idx];
        }
        ss += weights[combinations[i].items[combinations[i].count - 1] - 1];
        fprintf(output, "%d=%d Kaina=", weights[combinations[i].items[combinations[i].count - 1] - 1], ss);

        int sk = 0;
        for (int j = 0; j < combinations[i].count - 1; j++)
        {
            int idx = combinations[i].items[j] - 1;
            fprintf(output, "%d+", prices[idx]);
            sk += prices[idx];
        }
        sk += prices[combinations[i].items[combinations[i].count - 1] - 1];
        fprintf(output, "%d=%d\n", prices[combinations[i].items[combinations[i].count - 1] - 1], sk);
    }
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