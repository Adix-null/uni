#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
    double x;
    double y;
} Point;

void printPoint(Point p)
{
    printf("(%.3f, %.3f)\n", p.x, p.y);
}

Point createPoint(double x, double y)
{
    Point temp = {x, y};
    return temp;
}

double getDistance(Point a, Point b)
{
    double dx = abs(a.x - b.x);
    double dy = abs(a.y - b.y);
    return sqrt(dx * dx + dy * dy);
}


typedef struct
{
    Point *arr;
    int size;
} Stack;

void initStack(Stack *stack)
{
    stack->arr = (Point*)calloc(stack->size, sizeof(stack->arr[0]));
    memset(stack->arr, 0, stack->size);
}

void printStack(Stack *stack)
{
    for(int i = 0; i < stack->size; i++)
    {
        printPoint(stack->arr[i]);
    }
    printf("\n");
}

void printStackDist(Stack *stack)
{
    Point origin = createPoint(0, 0);
    for(int i = 0; i < stack->size; i++)
    {
        printf("%f\n", getDistance(stack->arr[i], origin));
    }
}

int getStackSize(Stack *stack)
{
    return stack->size;
}

void push(Stack *stack, Point value)
{
    stack->arr = realloc(stack->arr, (getStackSize(stack) + 1) * sizeof(stack->arr[0]));
    stack->arr[getStackSize(stack)] = value;
    ++(stack->size);
}

Point top(Stack *stack)
{
    return stack->size == 0 ? createPoint(0, 0) : stack->arr[getStackSize(stack) - 1];
}

Point pop(Stack *stack)
{
    Point tmp = top(stack);
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
    Stack s = {0, 0};
    initStack(&s);

    push(&s, createPoint(1.6, 4.12));
    push(&s, createPoint(0, 0));
    push(&s, createPoint(6.201, 9));
    push(&s, createPoint(-8, 5.24));
    push(&s, createPoint(-7, -3.1));
    printStack(&s);
    printStackDist(&s);

    destroyStack(&s);

    return 0;
}
