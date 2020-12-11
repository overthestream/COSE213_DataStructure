#pragma once
#ifndef _STACK_ADT_H_
#define _STACK_ADT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    double data;
    struct node* next;
} STACK_NODE;

typedef struct
{
    int count;
    STACK_NODE* top;
} STACK;

STACK* createStack();
void destroyStack(STACK* stack);
void pushStack(STACK* stack, double data);
void popStack(STACK* stack);
double* stackTop(STACK* stack);
int stackCount(STACK* stack);

#endif  // _STACK_ADT_H_