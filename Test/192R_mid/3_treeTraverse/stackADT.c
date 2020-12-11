#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stackADT.h"

STACK* createStack()
{
	STACK* stack;

	stack = (STACK*)malloc(sizeof(STACK));
	if (stack)
	{
		stack->count = 0;
		stack->top = NULL;
	}
	return stack;
}

STACK* destroyStack(STACK* stack)
{
	STACK_NODE* temp;

	if (stack)
	{
		while (stack->top != NULL)
		{
			free(stack->top->dataPtr);
			temp = stack->top;
			stack->top = stack->top->link;
			free(temp);
		}
		free(stack);
	}
	return NULL;
}

bool pushStack(STACK* stack, void* dataInPtr)
{
	STACK_NODE* newPtr;

	newPtr = (STACK_NODE*)malloc(sizeof(STACK_NODE));
	if (!newPtr)
		return false;

	newPtr->dataPtr = dataInPtr;

	newPtr->link = stack->top;
	stack->top = newPtr;

	(stack->count)++;
	return true;
}

void* popStack(STACK* stack)
{
	void* dataOutPtr;
	STACK_NODE* temp;

	if (stack->count == 0)
		dataOutPtr = NULL;
	else
	{
		temp = stack->top;
		dataOutPtr = stack->top->dataPtr;
		stack->top = stack->top->link;
		free(temp);
		(stack->count)--;
	}
	return dataOutPtr;
}

void* stackTop(STACK* stack)
{
	if (stack->count == 0)
		return NULL;
	else
		return stack->top->dataPtr;
}

bool isEmpty(STACK* stack)
{
	return (stack->count == 0);
}
