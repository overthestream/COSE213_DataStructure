#include "stackADT.h"

STACK* createStack()
{
    STACK* stack = (STACK*)malloc(sizeof(STACK));
    if (stack == NULL)
        return NULL;

    stack->count = 0;
    stack->top = NULL;

    return stack;
}

void destroyStack(STACK* stack)
{
    // TODO
    while (stackCount(stack))popStack(stack);
    free(stack);
}

void pushStack(STACK* stack, double data)
{
    // TODO
    STACK_NODE* newNode = (STACK_NODE*)malloc(sizeof(STACK_NODE));
    if (newNode == NULL) return;

    newNode->data = data;
    newNode->next = stack->top;
    ++(stack->count);
    stack->top = newNode;
    return;
}

void popStack(STACK* stack)
{
    // TODO

    if (stackCount(stack) == 0) return;
    STACK_NODE* del = stack->top;

    stack->top = del->next;
    --(stack->count);

    free(del);
    return;

}

double* stackTop(STACK* stack)
{
    if (stack->count == 0)
        return NULL;

    return &(stack->top->data);
}

int stackCount(STACK* stack)
{
    return stack->count;
}
