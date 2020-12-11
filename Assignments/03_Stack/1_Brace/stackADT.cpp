#include "stackADT.h"

STACK* createStack()
{
    // TODO
    STACK* newStack = (STACK*)malloc(sizeof(STACK));
    if (newStack == NULL) return NULL;

    newStack->count = 0;
    newStack->top = NULL;

    return newStack;

}

void pushStack(STACK* stack, void* dataInPtr)
{
    // TODO
    STACK_NODE* newNode = (STACK_NODE*)malloc(sizeof(STACK_NODE));
    if (newNode == NULL) return;

    newNode->dataPtr = dataInPtr;
    newNode->link = stack->top;

    stack->top = newNode;
    (stack->count)++;

}

void popStack(STACK* stack)
{
    // TODO
    if (stack->top == NULL) return;

    STACK_NODE* prevTop = stack->top;
    stack->top = prevTop->link;
    free(prevTop->dataPtr);
    free(prevTop);
    (stack->count)--;

}

void* stackTop(STACK* stack)
{
    // TODO
    if (stack->top == NULL) return NULL;
    return stack->top->dataPtr;

}

void destroyStack(STACK* stack)
{
    // TODO
    while (stack->top != NULL)
        popStack(stack);
    free(stack);

}

void catStack(STACK* a, STACK* b)
{
    // TODO1
    if (b->top != NULL) {
        STACK_NODE* curNode = b->top;
        STACK_NODE* nextNode = curNode->link;
        while (nextNode != NULL) {
            curNode = nextNode;
            nextNode = curNode->link;
        }
        curNode->link = a->top;
        a->top = b->top;
        a->count += b->count;
    }
    free(b);
    
}