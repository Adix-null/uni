#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dekas.h"

FILE *output;

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

enum State
{
    WAITING,
    WORKING
};

void print_info(Dequeue *applications, Dequeue *applicants)
{
    fprintf(output, "\t\t1) Stojačiųjų kiekis eilėje: %d", applicants->size);
    if (applicants->size != 0)
    {
        fprintf(output, ", Eilė {");
        print_dequeue(output, applicants, 'S');
        fprintf(output, "}");
    }
    fprintf(output, "\n\t\t2) Prašymų kiekis: %d", applications->size);
    if (applications->size != 0)
    {
        fprintf(output, ", Eilė {");
        print_dequeue(output, applications, 'P');
        fprintf(output, "}");
    }
    fprintf(output, "\n");
}

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
        printf("Nepavyko atidaryti įvesties failo.");
        return -1;
    }
    if (output == NULL)
    {
        perror("fopen");
        return -1;
    }

    int prim_t, d1t, d2t, sim_t, prob;
    fscanf(input, "%d", &prim_t);
    fscanf(input, "%d", &d1t);
    fscanf(input, "%d", &d2t);
    fscanf(input, "%d", &sim_t);
    fscanf(input, "%d", &prob);

    fprintf(output, "3 užduotis, 3 variantas. Adomas Bieliūnas, 1 kursas, 2 grupė, 1 pogrupis.\n\n");
    fprintf(output, "SALYGA. Priėmimo komisija. (ADT: dekas, ilgas sveikas skaičius). Procesas: komisijoje dirba 2 darbuotojos (D1, D2) skirtingu produktyvumu. Jos priima stojančiųjų prašymus ir stato į lentyną, kiekviena iš savo pusės. Kai nėra stojančiųjų ir pasibaigus tos dienos priėmimui, jos ima prašymus ir juos sutvarko. Patyrinėti, kiek laiko reikia tvarkyti prašymus, pasibaigus jų priėmimo trukmei, pvz., N=30 min.\n");
    fprintf(output, "\nPIRMA DALIS: Duomenys\n");
    fprintf(output, "\tPrašymo priėmimo laikas: %d min.\n", prim_t);
    fprintf(output, "\tD1 apdorojimo greitis: %d min.\n", d1t);
    fprintf(output, "\tD2 apdorojimo greitis: %d min.\n", d2t);
    fprintf(output, "\tSimuliavimo trukmė: %d min.\n", sim_t);
    fprintf(output, "\tStojančiojo atėjimo tikimybė: %d%%\n", prob);

    fprintf(output, "\n\nANTRA DALIS: Vykdymas\n");

    Dequeue *applications = create_dequeue();
    Dequeue *applicants = create_dequeue();

    int d1 = WAITING;
    int d2 = WAITING;
    int d1num = 0;
    int p1w = 0;
    int d2num = 0;
    int p2w = 0;

    for (int i = 0; i < sim_t; i++)
    {
        fprintf(output, "T=%d min.\n\tBŪSENA_%d PRADŽIOJE\n", i, i);
        print_info(applications, applicants);

        fprintf(output, "\tVEIKSMAI_%d\n", i + 1);
        if (d1num == 0 && applicants->size != 0)
            d1num = pop_front(applicants);
        if (d2num == 0 && applicants->size != 0)
            d2num = pop_front(applicants);

        switch (d1)
        {
        case WAITING:
        {
            if (d1num == 0)
            {
                fprintf(output, "\t\t1) Darbuotoja D1 laukia\n");
            }
            else
            {
                fprintf(output, "\t\t1) Darbuotoja D1 pradeda priima S%d. Ji baigs priėmimą iki T=%d min.\n", d1num, i + prim_t - 1);
                p1w = prim_t - 1;
                d1 = WORKING;
            }
            break;
        }
        case WORKING:
        {
            if (d1t == 1)
            {
                fprintf(output, "\t\t1) Darbuotoja D1 baigia dirbti prie S%d.\n", d1num);
                d1 = WAITING;
            }
            else
            {
                fprintf(output, "\t\t1) Darbuotoja D1 dirba prie S%d.\n", d1num);
            }
            break;
        }
        }

        switch (d2)
        {
        case WAITING:
        {
            if (d2num == 0)
            {
                fprintf(output, "\t\t2) Darbuotoja D2 laukia\n");
            }
            else
            {
                fprintf(output, "\t\t2) Darbuotoja D2 pradeda priima S%d. Ji baigs priėmimą iki T=%d min.\n", d2num, i + prim_t - 1);
                p2w = prim_t - 1;
                d2 = WORKING;
            }
            break;
        }
        case WORKING:
        {
            if (d2t == 1)
            {
                fprintf(output, "\t\t2) Darbuotoja D2 baigia dirbti prie S%d.\n", d2num);
                d2 = WAITING;
            }
            else
            {
                fprintf(output, "\t\t2) Darbuotoja D2 dirba prie S%d.\n", d2num);
            }
            break;
        }
        }

        p1w = MAX(0, p1w - 1);
        p2w = MAX(0, p2w - 1);

        srand(time(NULL));
        if (rand() % 100 <= prob)
        {
            fprintf(output, "\t\t3) Ateina naujas stojantysis %d\n", applicants->size + 1);
            push_front(applicants, applicants->size + 1);
        }
        else
        {
            fprintf(output, "\t\t3) Naujų stojančiųjų nėra\n");
        }

        fprintf(output, "\tBŪSENA PABAIGOJE\n");
        print_info(applications, applicants);
    }

    fclose(input);
    fclose(output);

    return 0;
}
