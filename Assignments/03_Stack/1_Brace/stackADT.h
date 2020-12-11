#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    void* dataPtr;
    struct node* link;
} STACK_NODE;

typedef struct
{
    int count;
    STACK_NODE* top;
} STACK;

STACK* createStack();
void destroyStack(STACK* stack);
void pushStack(STACK* stack, void* dataInPtr);
void popStack(STACK* stack);
void* stackTop(STACK* stack);
void catStack(STACK* a, STACK* b);