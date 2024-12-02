#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "func.h"

#if TESTING != 1
//actual logic implementtion: 1.5 + 1 + 2
//menu: 0.5h
//failų pertvarkymas į skirtingus: 0.25h
//apibrėžimų tvarkymas: 0.25ħ
//testų implementavimas: 1
int main()
{
    printf("Aprašas:\n");
    printf("Programa atlieka veiksmus su sąrašu, kurio 1 elemetas yra simbolių eilutė. \
    Eilutės maksimalus ilgis - 255 simboliai. Toliau pateikiama vartotojo pasirinkimo meniu, jam reikia įvesti vieną skaičių. \
    Įvedus kelis skaičius, atskirtus tarpu, jie .\n");

    Node* head = NULL;
    int loop = 0;
    char error_msgs_input[3][WORD_MAX] = {
                "Netinkama parinktis\n",
                "Netinkama parinktis\n",
                "Neteisinga įvestis\n"
                };
    while(loop == 0)
    {
        int choice = 0;
        printf("Meniu:\n");
        printf("1 - sukuriamas tuščias sąrašas\n");
        printf("2 - prie sąrašo galo prirašoma pradine reikšmė visose pozicijose\n");
        printf("3 - nuskaitomi duomenys iš duomenų failo į visą sąrašą\n");
        printf("4 - ištrinamas elementas pagal reikšmę\n");
        printf("5 - spausdinamas visas sąrašas\n");
        printf("6 - ištrinamas visas sąrašas\n");
        printf("7 - išeinama iš programos\n");
        validate_input_int("Parinktis:\n", error_msgs_input, &choice, 1, 7);

        switch (choice)
        {
            case 1:
            {
                int size = 0;
                int cont;

                char error_msgs[3][WORD_MAX] = {
                "Skaičius per mažas\n",
                "Skaičius per didelis\n",
                "Neteisinga įvestis\n"
                };

                cont = warn("Praeitos sąrašo reikšmės bus ištrintos. Jei norite tęsti, įveskite \"1\":\n");
                if(cont == 1)
                {
                    validate_input_int("Sąrašo ilgis:\n", error_msgs, &size, 1, LENGTH_MAX);

                    delete_list(&head);
                    generate_nodes(&head, size, "\0");
                }
                break;
            }

            case 2:
            {
                int size = 0;
                char init_val[WORD_MAX];

                char error_msgs_int[3][WORD_MAX] = {
                "Skaičius per mažas\n",
                "Skaičius per didelis\n",
                "Neteisinga įvestis\n"
                };
                char error_msgs_string[1][WORD_MAX] = {
                "Eilutės ilgis per didelis\n"
                };

                validate_input_int("Elementų kiekis:\n", error_msgs_int, &size, 1, LENGTH_MAX);
                validate_input_string("Pradinė reikšmė:\n", error_msgs_string, &init_val, WORD_MAX);
                generate_nodes(&head, size, init_val);
                break;
            }

            case 3:
            {
                char name[WORD_MAX];
                FILE *file;

                char error_msgs_string[1][WORD_MAX] = {
                "Eilutės ilgis per didelis\n"
                };

                 char error_msgs_file[1][WORD_MAX] = {
                "Failas neegzistuoja\n"
                };

                validate_input_string("Failo pavadinimas:\n", error_msgs_string, name, WORD_MAX);
                validate_file(error_msgs_file, "r+", file, name);
                read_from_file(&head, file, name);
                break;
            }

            case 4:
            {
                char key[WORD_MAX];

                char error_msgs_string[1][WORD_MAX] = {
                "Eilutės ilgis per didelis\n"
                };
                validate_input_string("Elemento reikšmė:\n", error_msgs_string, &key, WORD_MAX);

                delete_node(&head, key);
                break;
            }

            case 5:
            {
                print_list(head);
                break;
            }

            case 6:
            {
                delete_list(&head);
                break;
            }

            case 7:
            {
                loop = 1;
                break;
            }
        }
    }

    return 0;
}
#endif
