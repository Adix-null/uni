#include <stdio.h>
#include <stdlib.h>

#define MAX_ITEMS 100
#define MAX_WEIGHT 1000

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void knapsack(int weights[], int values[], int n, int maxWeight)
{
    int dp[n + 1][maxWeight + 1];

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
        }
    }

    printf("Pasirinkti elementai:\n");
    int w = maxWeight;
    for (int i = n; i > 0 && dp[i][w] != 0; i--)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            printf("%d:  kaina %d, svoris %d\n", i, values[i - 1], weights[i - 1]);
            w -= weights[i - 1];
        }
    }
    printf("Maksimali svorio apimtis: %d\n", maxWeight);
    printf("Galutinis rezultatas:  svoris %d, kaina %d\n", maxWeight - w, dp[n][maxWeight]);
}

int main()
{
    printf("test1\n");

    int n[] = {1, 4, 5, 7, 10, 8, 3, 12, 9};
    int k[] = {5, 4, 2, 9, 6, 11, 4, 17, 6};
    int c = 18;
    int sz = sizeof(k) / sizeof(k[0]);

    knapsack(n, k, sz, c);

    return 0;
}