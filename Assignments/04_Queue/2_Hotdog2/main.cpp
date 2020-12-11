#define _CRT_SECURE_NO_WARNINGS
#include "queueADT.h"
#include <stdio.h>
#include <stdlib.h>

int hotdogsSold(int numCustomers, int* patience)
{
	// TODO : return the number of hotdogs sold

	QUEUE* queue = createQueue();
	int result = 0;
	for (int i = 0; i < numCustomers; ++i)
		enqueue(queue, patience + i);
	for (int t = 0; queueCount(queue); ++t) {
		while (queueCount(queue) && *(int*)queueFront(queue) - t < 0) dequeue(queue);
		if (!queueCount(queue)) {
			destroyQueue(queue);
			return result;
		}
		++result;
		dequeue(queue);

		while (queueCount(queue) && *(int*)queueFront(queue) - t < 0) dequeue(queue);
		if (!queueCount(queue)) {
			destroyQueue(queue);
			return result;
		}
		++result;
		dequeue(queue);

	}
	destroyQueue(queue);
	return result;

}

int main()
{
	int numCustomers;
	int* patience;

	printf("Number of customers : ");
	scanf("%d", &numCustomers);
	patience = (int*)malloc(sizeof(int) * numCustomers);
	//patience 배열 free 해줘야하는가?
	for (int i = 0; i < numCustomers; ++i)
	{
		printf("Patience of customer %d (1~9): ", i + 1);
		scanf("%d", &patience[i]);
	}

	printf("I sold %d hotdogs\n", hotdogsSold(numCustomers, patience));
	free(patience);
	return 0;
}
