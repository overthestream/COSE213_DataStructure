#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "heapADT.h"

HEAP* heapCreate()
{
	//fin

	// TODO :Create an empty heap

	HEAP* heap = (HEAP*)malloc(sizeof(HEAP));
	if (!heap) return NULL;
	heap->capacity = HEAP_UNIT;
	heap->size = 0;
	heap->data = (int*)malloc(sizeof(int) * (heap->capacity));

	return heap;

}

void heapDestroy(HEAP* heap)
{
	//fin

	// TODO : delete all elements of the heap and free heap

	if (heap) {
		free(heap->data);
		free(heap);
	}
	return;

}

bool heapInsert(HEAP* heap, int val)
{
	// fin

	// TODO : insert the value into the given heap
	if (heapFull(heap)) return false;
	heap->data[(heap->size)++] = val;
//	if (!extendHeap(&heap)) return false;

	reheapUp(heap, heap->size - 1);
	return true;

}

int heapDelete(HEAP* heap)
{
	//fin..?

	// TODO : delete the root of the given heap
	if (heapEmpty(heap)) return -1;
	int val = heap->data[0];
	heap->data[0] = heap->data[--(heap->size)];
	reheapDown(heap, 0);
	return val;
}

int heapCount(HEAP* heap)
{
	return heap->size;
}

bool heapFull(HEAP* heap)
{
	return heap->size >= heap->capacity;
}

bool heapEmpty(HEAP* heap)
{
	return heap->size == 0;
}

void heapTraverse(HEAP* heap)
{
	//fin	

	// TODO : traverse values in the given heap
	for (int i = 0; i < heap->size; i++) {
		printf("%d ", heap->data[i]);
		
	}
	printf("\n");
}

// additional functions
void reheapUp(HEAP* heap, int pos)
{

	// fin

	// TODO : re heap up
	if (pos <= 0 || pos >= heap->size) return;
	int parent = (pos - 1) / 2;
	if (heap->data[pos] > heap->data[parent]) {
		swap(heap->data, pos, parent);
		reheapUp(heap, parent);
	}


}

void reheapDown(HEAP* heap, int pos)
{
	//fin

	// TODO : re heap down 
	if (pos < 0 || pos >= heap->size) return;
	if (pos * 2 + 1 < heap->size) {
		int maxChild = pos * 2 + 1;
		if (maxChild + 1 < heap->size && heap->data[maxChild + 1] > heap->data[maxChild]) ++maxChild;
		if (heap->data[maxChild] > heap->data[pos]) {
			swap(heap->data, pos, maxChild);
			reheapDown(heap, maxChild);
		}
	}


}
/*
bool extendHeap(HEAP** heap) {

	// fin

	// TODO : check the capacity and size of heap, if it exceeds, realloc the heap.

	if (heapFull(*heap)) {
		(*heap)->capacity = (((*heap)->capacity + 1) * 2) - 1;
		int* extended = NULL;
		extended = (int*)realloc((*heap)->data, sizeof(int) * ((*heap)->capacity));
		if (!extended) return false;
		(*heap)->data = extended;
	}
	return true;

}
*/
void swap(int* arr, int pos1, int pos2) {
	//fin

	//TODO : swap 
	int temp = arr[pos1];
	arr[pos1] = arr[pos2];
	arr[pos2] = temp;
}