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

enum Mode
{
    STUDENTS,
    APPLICATIONS
};

// cd semester_2/ads/priemimo_komisija

int d1 = WAITING;
int d2 = WAITING;
int d1num = 0;
int p1w = 0;
int d2num = 0;
int p2w = 0;
int i = 0;

int m1w = STUDENTS;
int m2w = STUDENTS;

int w1wt = 0;
int w2wt = 0;

int prim_t, d1t, d2t, sim_t, prob;

int scount = 0;

Dequeue *applications;
Dequeue *applicants;

void print_info(Dequeue *applications, Dequeue *applicants)
{
    fprintf(output, "\t\t1) Stojačiųjų kiekis eilėje: %d", applicants->size);
    print_applicants(applicants);
    fprintf(output, "\t\t2) Prašymų kiekis: %d", applications->size);
    print_applications(applications);
}

void print_applicants(Dequeue *applicants)
{
    if (applicants->size != 0)
    {
        fprintf(output, ", Eilė {");
        print_dequeue(output, applicants, 'S');
        fprintf(output, "}");
    }
    fprintf(output, "\n");
}

void print_applications(Dequeue *applications)
{
    if (applications->size != 0)
    {
        fprintf(output, ", Prašymai lentynoje {");
        print_dequeue(output, applications, 'P');
        fprintf(output, "}");
    }
    fprintf(output, "\n");
}

int main()
{
    int variant = 3;

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

    fprintf(output, "\tĮvesties failas: %s\n", input_name);
    fprintf(output, "\tIšvesties failas: %s\n", output_name);

    fprintf(output, "\nANTRA DALIS: Vykdymas\n");

    applications = create_dequeue();
    applicants = create_dequeue();

    srand(time(NULL));

    while (!(applicants->size == 0 && applications->size == 0 && i >= sim_t && d1 == WAITING && d2 == WAITING))
    {
        fprintf(output, "T=%d min.\n\tBŪSENA_%d PRADŽIOJE\n", i, i);
        print_info(applications, applicants);

        fprintf(output, "\tVEIKSMAI_%d\n", i + 1);

        if (d1num == 0 && applicants->size != 0 && d1 != WORKING)
        {
            d1num = pop_back(applicants);
            m1w = STUDENTS;
        }
        if (d2num == 0 && applicants->size != 0 && d2 != WORKING)
        {
            d2num = pop_back(applicants);
            m2w = STUDENTS;
        }
        if (d1num == 0 && applications->size != 0 && d1 != WORKING)
        {
            d1num = pop_front(applications);
            m1w = APPLICATIONS;
        }
        if (d2num == 0 && applications->size != 0 && d2 != WORKING)
        {
            d2num = pop_back(applications);
            m2w = APPLICATIONS;
        }

        if (m1w == STUDENTS)
        {
            switch (d1)
            {
            case WAITING:
            {
                if (d1num == 0)
                {
                    fprintf(output, "\t\t1) Darbuotoja D1 laukia\n");
                    w1wt++;
                }
                else
                {
                    fprintf(output, "\t\t1) Darbuotoja D1 pradeda priimti S%d. Ji priiminės iki T=%d min.\n", d1num, i + prim_t - 1);
                    p1w = prim_t;
                    d1 = WORKING;
                }
                break;
            }
            case WORKING:
            {
                if (p1w < 2)
                {
                    fprintf(output, "\t\t1) Darbuotoja D1 baigia dirbti prie S%d.\n", d1num);
                    push_front(applications, d1num);
                    d1num = 0;
                    d1 = WAITING;
                }
                else
                {
                    fprintf(output, "\t\t1) Darbuotoja D1 dirba prie S%d.\n", d1num);
                }
                break;
            }
            }
        }
        if (m1w == APPLICATIONS)
        {
            switch (d1)
            {
            case WAITING:
            {
                if (d1num == 0)
                {
                    fprintf(output, "\t\t1) Darbuotoja D1 laukia\n");
                    w1wt++;
                }
                else
                {
                    fprintf(output, "\t\t1) Darbuotoja D1 pradeda dirbti prie P%d prašymo. Ji dirbs iki T=%d min.\n", d1num, i + d1t - 1);
                    p1w = d1t;
                    d1 = WORKING;
                }
                break;
            }
            case WORKING:
            {
                if (p1w < 2)
                {
                    fprintf(output, "\t\t1) Darbuotoja D1 baigia dirbti prie P%d prašymo.\n", d1num);
                    d1num = 0;
                    d1 = WAITING;
                }
                else
                {
                    fprintf(output, "\t\t1) Darbuotoja D1 dirba prie P%d prašymo.\n", d1num);
                }
                break;
            }
            }
        }
        if (m2w == STUDENTS)
        {
            switch (d2)
            {
            case WAITING:
            {
                if (d2num == 0)
                {
                    fprintf(output, "\t\t2) Darbuotoja D2 laukia\n");
                    w2wt++;
                }
                else
                {
                    fprintf(output, "\t\t2) Darbuotoja D2 pradeda priimti S%d. Ji priiminės iki T=%d min.\n", d2num, i + prim_t - 1);
                    p2w = prim_t;
                    d2 = WORKING;
                }
                break;
            }
            case WORKING:
            {
                if (p2w < 2)
                {
                    fprintf(output, "\t\t2) Darbuotoja D2 baigia dirbti prie S%d.\n", d2num);
                    push_back(applications, d2num);
                    d2num = 0;
                    d2 = WAITING;
                }
                else
                {
                    fprintf(output, "\t\t2) Darbuotoja D2 dirba prie S%d.\n", d2num);
                }
                break;
            }
            }
        }
        if (m2w == APPLICATIONS)
        {
            switch (d2)
            {
            case WAITING:
            {
                if (d2num == 0)
                {
                    fprintf(output, "\t\t2) Darbuotoja D2 laukia\n");
                    w2wt++;
                }
                else
                {
                    fprintf(output, "\t\t2) Darbuotoja D2 pradeda dirbti prie P%d prašymo. Ji dirbs iki T=%d min.\n", d2num, i + d2t - 1);
                    p2w = d2t;
                    d2 = WORKING;
                }
                break;
            }
            case WORKING:
            {
                if (p2w < 2)
                {
                    fprintf(output, "\t\t2) Darbuotoja D2 baigia dirbti prie P%d prašymo.\n", d2num);
                    d2num = 0;
                    d2 = WAITING;
                }
                else
                {
                    fprintf(output, "\t\t2) Darbuotoja D2 dirba prie P%d prašymo.\n", d2num);
                }
                break;
            }
            }
        }

        if (i <= sim_t)
        {
            if (rand() % 100 <= prob)
            {
                fprintf(output, "\t\t3) Ateina naujas stojantysis %d\n", scount + 1);
                push_front(applicants, scount + 1);
                scount++;
            }
            else
            {
                fprintf(output, "\t\t3) Naujų stojančiųjų nėra\n");
            }
        }

        p1w = MAX(0, p1w - 1);
        p2w = MAX(0, p2w - 1);

        fprintf(output, "\tBŪSENA PABAIGOJE\n");
        print_info(applications, applicants);

        if (i == sim_t)
            fprintf(output, "\nPAPILDOMAS DARBO LAIKAS\n\n");

        i++;
    }

    fprintf(output, "\n3 DALIS. REZULTATAI\n");
    fprintf(output, "\tPapildomas darbo laikas %d min.\n", i - sim_t);
    fprintf(output, "\tD1 užimtumas %.0f%%\n", 100.0f * (i - w1wt) / i);
    fprintf(output, "\tD2 užimtumas %.0f%%\n", 100.0f * (i - w2wt) / i);

    fclose(input);
    fclose(output);

    return 0;
}
