#include <stdio.h>
#include <stdlib.h>

#define DEKO_MAKS_ELEMENTU_KIEKIS 5
#define DEKU_MAKS_KIEKIS 3

static int dekuKiekisAtmintyje = 0;

char klaidu_zinutes[4][256] = {
    "Viršijamas deko limitas\n",
    "Deke nėra elementų\n",
    "Viršijamas dekų kiekio limitas\n",
    "Netinkama pozicija deke\n"};

void mesti_klaida(int kodas)
{
    printf("%s", klaidu_zinutes[kodas - 1]);
    exit(kodas);
}

typedef struct
{
    int *duomenys;
    int priekis, galas, dydis, talpa;
} Dekas;

Dekas *sukurti_deka()
{
    if (dekuKiekisAtmintyje == DEKU_MAKS_KIEKIS)
    {
        mesti_klaida(3);
    }
    dekuKiekisAtmintyje++;
    Dekas *dekas = (Dekas *)malloc(sizeof(Dekas));
    dekas->talpa = DEKO_MAKS_ELEMENTU_KIEKIS;
    dekas->duomenys = (int *)malloc(dekas->talpa * sizeof(int));
    dekas->priekis = dekas->galas = dekas->dydis = 0;
    return dekas;
}

void push_priekis(Dekas *dekas, int verte)
{
    if (dekas->dydis == dekas->talpa)
    {
        mesti_klaida(1);
    }
    dekas->priekis = (dekas->priekis - 1 + dekas->talpa) % dekas->talpa;
    dekas->duomenys[dekas->priekis] = verte;
    dekas->dydis++;
}

void push_galas(Dekas *dekas, int verte)
{
    if (dekas->dydis == dekas->talpa)
    {
        mesti_klaida(1);
    }
    dekas->duomenys[dekas->galas] = verte;
    dekas->galas = (dekas->galas + 1) % dekas->talpa;
    dekas->dydis++;
}

int pop_priekis(Dekas *dekas)
{
    if (dekas->dydis == 0)
    {
        mesti_klaida(2);
    }
    int verte = dekas->duomenys[dekas->priekis];
    dekas->priekis = (dekas->priekis + 1) % dekas->talpa;
    dekas->dydis--;
    return verte;
}

int pop_galas(Dekas *dekas)
{
    if (dekas->dydis == 0)
    {
        mesti_klaida(2);
    }
    dekas->galas = (dekas->galas - 1 + dekas->talpa) % dekas->talpa;
    int verte = dekas->duomenys[dekas->galas];
    dekas->dydis--;
    return verte;
}

int top(Dekas *dekas)
{
    return dekas->priekis;
}

int bottom(Dekas *dekas)
{
    return dekas->galas;
}

void ideti(Dekas *dekas, int index, int verte)
{
    if (index < 0 || index > dekas->dydis)
    {
        mesti_klaida(4);
    }
    if (dekas->dydis == dekas->talpa)
    {
        mesti_klaida(1);
    }
    for (int i = dekas->dydis; i > index; i--)
    {
        dekas->duomenys[(dekas->priekis + i) % dekas->talpa] = dekas->duomenys[(dekas->priekis + i - 1) % dekas->talpa];
    }
    dekas->duomenys[(dekas->priekis + index) % dekas->talpa] = verte;
    dekas->dydis++;
}

void print_dekas(Dekas *dekas)
{
    if (dekas->dydis == 0)
    {
        mesti_klaida(2);
    }
    printf("Priekis ");
    for (int i = 0; i < dekas->dydis; i++)
    {
        printf("%d -> ", dekas->duomenys[(dekas->priekis + i) % dekas->talpa]);
    }
    printf("Galas\n");
}

void atlaisvinti(Dekas *dekas)
{
    dekuKiekisAtmintyje--;
    free(dekas->duomenys);
    free(dekas);
}

int main()
{
    Dekas *dekas = sukurti_deka();
    Dekas *dekas1 = sukurti_deka();
    Dekas *dekas2 = sukurti_deka();
    push_galas(dekas, 10);
    push_priekis(dekas, 20);
    push_galas(dekas, 30);
    print_dekas(dekas);
    ideti(dekas, 1, 25);
    print_dekas(dekas);
    printf("Pop priekis: %d\n", pop_priekis(dekas));
    printf("Pop galas: %d\n", pop_galas(dekas));
    print_dekas(dekas);
    atlaisvinti(dekas);
    return 0;
}
