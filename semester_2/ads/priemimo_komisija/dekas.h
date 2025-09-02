#pragma once
#include <stdio.h>
#include <stdlib.h>

#ifndef DEKAS_H
#define DEKAS_H

#define DEKO_MAKS_ELEMENTU_KIEKIS 1000
#define DEKU_MAKS_KIEKIS 100

void throw_error(int kodas);

typedef struct
{
    int *data;
    int front, back, size, capacity;
} Dequeue;

Dequeue *create_dequeue();
void push_front(Dequeue *dekas, int value);
void push_back(Dequeue *dekas, int value);
int pop_front(Dequeue *dekas);
int pop_back(Dequeue *dekas);
int top(Dequeue *dekas);
int bottom(Dequeue *dekas);
void print_dequeue(FILE *output, Dequeue *dekas, char c);
void free_dequeue(Dequeue *dekas);

#endif