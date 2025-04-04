#include <stdio.h>
#include <stdlib.h>

#define DEKO_MAKS_ELEMENTU_KIEKIS 5
#define DEKU_MAKS_KIEKIS 3

static int deku_kiekis_atmintyje = 0;
static int error = 0;

char klaidu_zinutes[6][256] = {
    "Klaida nr. 1: Viršijama 3 dekų apimtis\n",
    "Klaida nr. 2: Deke nėra elementų\n",
    "Klaida nr. 3: Viršijama 5 dekų kiekio apimtis\n",
    "Klaida nr. 4: Netinkama pozicija deke\n",
    "Klaida nr. 5: Dekas nesukurtas\n",
    "Klaida nr. 6: Blogas deko skaičius\n"};

void throw_error(int kodas)
{
    printf("%s", klaidu_zinutes[kodas - 1]);
    error = 1;
}

typedef struct
{
    int *duomenys;
    int priekis, galas, dydis, talpa;
} Dekas;

Dekas *create_dequeue()
{
    if (deku_kiekis_atmintyje == DEKU_MAKS_KIEKIS)
    {
        throw_error(3);
    }
    if (error == 0)
    {
        deku_kiekis_atmintyje++;
        Dekas *dekas = (Dekas *)malloc(sizeof(Dekas));
        dekas->talpa = DEKO_MAKS_ELEMENTU_KIEKIS;
        dekas->duomenys = (int *)malloc(dekas->talpa * sizeof(int));
        dekas->priekis = dekas->galas = dekas->dydis = 0;
        return dekas;
    }
    error = 0;
}

void push_priekis(Dekas *dekas, int verte)
{
    if (dekas == NULL)
    {
        throw_error(5);
    }
    if (dekas->dydis == dekas->talpa)
    {
        throw_error(1);
    }
    if (error == 0)
    {
        dekas->priekis = (dekas->priekis - 1 + dekas->talpa) % dekas->talpa;
        dekas->duomenys[dekas->priekis] = verte;
        dekas->dydis++;
    }
    error = 0;
}

void push_galas(Dekas *dekas, int verte)
{
    if (dekas == NULL)
    {
        throw_error(5);
    }
    if (dekas->dydis == dekas->talpa)
    {
        throw_error(1);
    }
    if (error == 0)
    {
        dekas->duomenys[dekas->galas] = verte;
        dekas->galas = (dekas->galas + 1) % dekas->talpa;
        dekas->dydis++;
    }
    error = 0;
}

int pop_priekis(Dekas *dekas)
{
    if (dekas == NULL)
    {
        throw_error(5);
    }
    if (dekas->dydis == 0)
    {
        throw_error(2);
    }
    if (error == 0)
    {
        int verte = dekas->duomenys[dekas->priekis];
        dekas->priekis = (dekas->priekis + 1) % dekas->talpa;
        dekas->dydis--;
        return verte;
    }
    error = 0;
}

int pop_galas(Dekas *dekas)
{
    if (dekas == NULL)
    {
        throw_error(5);
    }
    if (dekas->dydis == 0)
    {
        throw_error(2);
    }
    if (error == 0)
    {
        dekas->galas = (dekas->galas - 1 + dekas->talpa) % dekas->talpa;
        int verte = dekas->duomenys[dekas->galas];
        dekas->dydis--;
        return verte;
    }
    error = 0;
}

int top(Dekas *dekas)
{
    if (dekas == NULL)
    {
        throw_error(5);
    }
    if (dekas->dydis == 0)
    {
        throw_error(2);
    }
    if (error == 0)
    {
        return dekas->duomenys[dekas->priekis];
    }
    error = 0;
}

int bottom(Dekas *dekas)
{
    if (dekas == NULL)
    {
        throw_error(5);
    }
    if (dekas->dydis == 0)
    {
        throw_error(2);
    }
    if (error == 0)
    {
        return dekas->duomenys[(dekas->galas - 1 + dekas->talpa) % dekas->talpa];
    }
    error = 0;
}

void ideti(Dekas *dekas, int index, int verte)
{
    if (dekas == NULL)
    {
        throw_error(5);
    }
    if (index < 0 || index > dekas->dydis)
    {
        throw_error(4);
    }
    if (dekas->dydis == dekas->talpa)
    {
        throw_error(1);
    }
    for (int i = dekas->dydis; i > index; i--)
    {
        dekas->duomenys[(dekas->priekis + i) % dekas->talpa] = dekas->duomenys[(dekas->priekis + i - 1) % dekas->talpa];
    }
    if (error == 0)
    {
        dekas->duomenys[(dekas->priekis + index) % dekas->talpa] = verte;
        dekas->dydis++;
    }
    error = 0;
}

void print_dekas(Dekas *dekas)
{
    if (dekas == NULL || dekas->dydis == 0)
    {
        printf("Dekas tuščias\n");
    }
    else
    {
        printf("Priekis ");
        for (int i = 0; i < dekas->dydis; i++)
        {
            printf("%d, ", dekas->duomenys[(dekas->priekis + i) % dekas->talpa]);
        }
        printf("Galas\n");
    }
}

void atlaisvinti(Dekas *dekas)
{
    if (deku_kiekis_atmintyje == 0)
    {
        throw_error(5);
    }
    if (error == 0)
    {
        deku_kiekis_atmintyje--;
        free(dekas->duomenys);
        // free(dekas);
        dekas = NULL;
    }
    error = 0;
}

int main()
{
    int kilpa = 0;
    int deko_sk = 1;
    static Dekas *dekai[DEKU_MAKS_KIEKIS] = {NULL};

    while (kilpa == 0)
    {
        int choice = 0;
        printf("Meniu:\n");
        printf(" 1: Sukurti deką\n");
        printf(" 2: Įdėti elementą\n");
        printf(" 3: Push iš priekio\n");
        printf(" 4: Push iš galo\n");
        printf(" 5: Pop iš priekio\n");
        printf(" 6: Pop iš galo\n");
        printf(" 7: Top\n");
        printf(" 8: Bottom\n");
        printf(" 9: Atspausdinti deką\n");
        printf("10: Sunaikinti deką\n");
        printf("11: Pasirinkti deką\n");
        printf("12: Išeiti iš programos\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            dekai[deko_sk - 1] = create_dequeue();
            break;
        }
        case 2:
        {
            int v = 0;
            int i = 0;
            printf("Įveskite poziciją: ");
            scanf("%d", &i);
            printf("Įveskite reikšmę: ");
            scanf("%d", &v);
            ideti(dekai[deko_sk - 1], i, v);
            break;
        }
        case 3:
        {
            int v = 0;
            printf("Įveskite reikšmę: ");
            scanf("%d", &v);
            push_priekis(dekai[deko_sk - 1], v);
            break;
        }
        case 4:
        {
            int v = 0;
            printf("Įveskite reikšmę: ");
            scanf("%d", &v);
            push_galas(dekai[deko_sk - 1], v);
            break;
        }
        case 5:
        {
            printf("Pop priekis: %d\n", pop_priekis(dekai[deko_sk - 1]));
            break;
        }
        case 6:
        {
            printf("Pop galas: %d\n", pop_galas(dekai[deko_sk - 1]));
            break;
        }
        case 7:
        {
            printf("Top: %d\n", top(dekai[deko_sk - 1]));
            break;
        }
        case 8:
        {
            printf("Bottom: %d\n", bottom(dekai[deko_sk - 1]));
            break;
        }
        case 9:
        {
            print_dekas(dekai[deko_sk - 1]);
            break;
        }
        case 10:
        {
            atlaisvinti(dekai[deko_sk - 1]);
            break;
        }
        case 11:
        {
            printf("Įveskite deko numerį: ");
            scanf("%d", &deko_sk);
            if (deko_sk < 1 || deko_sk > DEKU_MAKS_KIEKIS)
            {
                throw_error(6);
            }
            break;
        }
        case 12:
        {
            kilpa = 1;
            break;
        }
        }
    }
    return 0;
}