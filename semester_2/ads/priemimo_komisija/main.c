#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

FILE *output;

int main()
{
    int variant = 1;

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char date[11]; // yyyy-mm-dd + null terminator
    strftime(date, sizeof(date), "%Y-%m-%d", tm_info);

    char input_name[64];
    snprintf(input_name, sizeof(input_name), "inp%d.txt", variant);
    char output_name[64];
    snprintf(output_name, sizeof(output_name), "3uzd-03var-protokolas%d-Bieliūnas-%s.txt", variant, date);

    FILE *input = fopen(input_name, "r");

    output = fopen(output_name, "w");
    if (input == NULL)
    {
        fprintf(output, "Nepavyko atidaryti failo.");
        return -1;
    }

    int prim_t, d1, d2, sim_t, prob;
    fscanf(input, "%d", &prim_t);
    fscanf(input, "%d", &d1);
    fscanf(input, "%d", &d2);
    fscanf(input, "%d", &sim_t);
    fscanf(input, "%d", &prob);

    fprintf(output, "3 užduotis, 3 variantas. Adomas Bieliūnas, 1 kursas, 2 grupė, 1 pogrupis.\n\n");
    fprintf(output, "SALYGA. Priėmimo komisija. (ADT: dekas, ilgas sveikas skaičius). Procesas: komisijoje dirba 2 darbuotojos (D1, D2) skirtingu produktyvumu. Jos priima stojančiųjų prašymus ir stato į lentyną, kiekviena iš savo pusės. Kai nėra stojančiųjų ir pasibaigus tos dienos priėmimui, jos ima prašymus ir juos sutvarko. Patyrinėti, kiek laiko reikia tvarkyti prašymus, pasibaigus jų priėmimo trukmei, pvz., N=30 min.\n");
    fprintf(output, "\nPIRMA DALIS: Duomenys\n");
    fprintf(output, "\tPrašymo priėmimo laikas: %d min.\n", prim_t);
    fprintf(output, "\tD1 produktyvumas: %d min.\n", d1);
    fprintf(output, "\tD2 produktyvumas: %d min.\n", d2);
    fprintf(output, "\tSimuliavimo trukmė: %d min.\n", sim_t);
    fprintf(output, "\tKliento atėjimo tikimybė: %d%%\n", prob);

    return 0;
}