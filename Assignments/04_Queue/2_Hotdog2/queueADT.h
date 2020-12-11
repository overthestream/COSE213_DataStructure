#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
	void* dataPtr;
	struct node* next;
} QUEUE_NODE;

typedef struct QUEUE
{
	QUEUE_NODE* front;
	QUEUE_NODE* rear;
	int count;
} QUEUE;

QUEUE* createQueue();
void destroyQueue(QUEUE* queue);

void enqueue(QUEUE* queue, void* dataPtr);
void dequeue(QUEUE* queue);
void* queueFront(QUEUE* queue);
int queueCount(QUEUE* queue);

