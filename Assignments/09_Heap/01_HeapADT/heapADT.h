#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define HEAP_UNIT 100

typedef struct heap {
	int* data;
	int size;
	int capacity;
} HEAP;

HEAP* heapCreate();
void heapDestroy(HEAP* heap);

bool heapInsert(HEAP* heap, int val);
int heapDelete(HEAP* heap);

int heapCount(HEAP* heap);
bool heapFull(HEAP* heap);
bool heapEmpty(HEAP* heap);
void heapTraverse(HEAP* heap);

// additional functions
void reheapUp(HEAP* heap, int pos);
void reheapDown(HEAP* heap, int pos);

//bool extendHeap(HEAP** heap);
void swap(int* arr, int pos1, int pos2);