#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
    int *arr;
    int size;
} Stack;

void initStack(Stack *stack)
{
    stack->arr = (int*)calloc(stack->size, sizeof(stack->arr[0]));
    memset(stack->arr, 0, stack->size);
}

void printStack(Stack *stack)
{
    for(int i = 0; i < stack->size; i++)
    {
        printf("%d ", stack->arr[i]);
    }
    printf("\n");
}

int getStackSize(Stack *stack)
{
    return stack->size;
}

void push(Stack *stack, int value)
{
    stack->arr = realloc(stack->arr, (getStackSize(stack) + 1) * sizeof(stack->arr[0]));
    stack->arr[getStackSize(stack)] = value;
    ++(stack->size);
}

int top(Stack *stack)
{
    return stack->size == 0 ? 0 : stack->arr[getStackSize(stack) - 1];
}

int pop(Stack *stack)
{
    int tmp = top(stack);
    stack->arr = realloc(stack->arr, (getStackSize(stack) - 1) * sizeof(stack->arr[0]));
    --(stack->size);
    return tmp;
}

void destroyStack(Stack *stack)
{
    memset(stack->arr, 0, stack->size);
    free(stack->arr);
    stack->size = 0;
    stack = NULL;
}

int main()
{
//    Stack s = {0, 0};
//    initStack(&s);
//
//    push(&s, 2);
//    printStack(&s);
//    push(&s, 6);
//    printStack(&s);
//    printf("%d\n", pop(&s));
//    printStack(&s);
//    destroyStack(&s);
//    printStack(&s);

    return 0;
}
