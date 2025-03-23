#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "func.hpp"

using namespace std;

int main()
{
    int loop = 0;
    int deko_sk = 1;
    static ip2::Dequeue *dequeues[DEQUEUE_MAX_COUNT] = {NULL};

    while (loop == 0)
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
            //(*dequeues)[deko_sk - 1].create_dequeue();
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
            //(*dequeues)[deko_sk - 1].insert(i, v);
            break;
        }
        case 3:
        {
            int v = 0;
            printf("Įveskite reikšmę: ");
            scanf("%d", &v);
            // push_front(dequeues[deko_sk - 1], v);
            break;
        }
        case 4:
        {
            int v = 0;
            printf("Įveskite reikšmę: ");
            scanf("%d", &v);
            // push_back(dequeues[deko_sk - 1], v);
            break;
        }
        case 5:
        {
            // printf("Pop priekis: %d\n", (*dequeues)[deko_sk - 1].pop_front());
            break;
        }
        case 6:
        {
            // printf("Pop galas: %d\n", pop_back(dequeues[deko_sk - 1]));
            break;
        }
        case 7:
        {
            // printf("Top: %d\n", top(dequeues[deko_sk - 1]));
            break;
        }
        case 8:
        {
            // printf("Bottom: %d\n", bottom(dequeues[deko_sk - 1]));
            break;
        }
        case 9:
        {
            // print_dequeue(dequeues[deko_sk - 1]);
            break;
        }
        case 10:
        {
            free(dequeues[deko_sk - 1]);
            break;
        }
        case 11:
        {
            printf("Įveskite deko numerį: ");
            scanf("%d", &deko_sk);
            if (deko_sk < 1 || deko_sk > DEQUEUE_MAX_COUNT)
            {
                ip2::Exception e;
                e.throw_error(6);
            }
            break;
        }
        case 12:
        {
            loop = 1;
            break;
        }
        }
    }
    return 0;
}