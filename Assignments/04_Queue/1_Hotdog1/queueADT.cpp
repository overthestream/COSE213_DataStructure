#include "queueADT.h"

QUEUE* createQueue(void)
{
	// TODO : create a queue

	QUEUE* pNewQueue = (QUEUE*)malloc(sizeof(QUEUE));
	if (pNewQueue == NULL) return NULL;

	pNewQueue->count = 0;
	pNewQueue->front = NULL;
	pNewQueue->rear = NULL;

	return pNewQueue;

}

int queueCount(QUEUE* queue)
{
	// TODO : retrieve the number of element in the queue 
	return queue->count;

}

void enqueue(QUEUE* queue, void* dataPtr)
{
	// TODO : insert data at the end of the queue

	QUEUE_NODE* pNewNode = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE));
	if (pNewNode == NULL) return;

	pNewNode->dataPtr = dataPtr;
	pNewNode->next = NULL;
	if (queueCount(queue) <= 0) queue->front = queue->rear = pNewNode;
	else {
		queue->rear->next = pNewNode;
		queue->rear = pNewNode;
	}
	(queue->count)++;

}

void dequeue(QUEUE* queue)
{
	// TODO : delete data at the front of the queue
	 
	QUEUE_NODE* pFront = NULL;

	if (queueCount(queue) <= 0) return;

	pFront = queue->front;
	if (queueCount(queue) == 1)
		queue->front = queue->rear = NULL;
	else
		queue->front = pFront->next;

//	free((int*)pFront->dataPtr);
	free(pFront);
	(queue->count)--;
	return;
	

}

void* queueFront(QUEUE* queue)
{
	// TODO : retrieve data at the front of the queue
	if (queueCount(queue) <= 0) return NULL;

	return queue->front->dataPtr;

}

void destroyQueue(QUEUE* queue)
{
	// TODO : delete the queue
	while (queueCount(queue)) dequeue(queue);
	free(queue);
}

