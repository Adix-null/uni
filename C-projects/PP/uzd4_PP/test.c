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

#if TESTING == 1
int main()
{
    printf("Testuojama\n");
    static errors = 0;

    Node* head = NULL;

    append(&head, "test1");

    append(&head, "test2");
    assert(list_size(head) == 2);

    append(&head, "0V");
    assert(!strcmp(get_at_pos(&head, 1)->data, "test2"));

    delete_node(&head, "test1");
    assert(!strcmp(get_at_pos(&head, 0)->data, "test2"));
    assert(!strcmp(get_at_pos(&head, 1)->data, "0V"));

    generate_nodes(&head, 3, "gen:3");
    assert(!strcmp(get_at_pos(&head, 4)->data, "gen:3"));

    FILE *file;
    read_from_file(&head, file, "inp.txt");
    assert(!strcmp(get_at_pos(&head, 5)->data, "daviens"));

    delete_list(&head);
    assert(list_size(head) == 0);

    assert(errors == 0);

    return 0;
}
#endif
