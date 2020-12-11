#include <stdio.h>
#include "heapADT.h"
//heap  sort 오름내림반대 
void heapSort(int* arr, int num) {
	HEAP* heap = heapCreate();
	for (int i = 0; i < num; ++i)
		heapInsert(heap, arr[i]);
	for (int i = 0; i < num; ++i)
		arr[i] = heapDelete(heap);
	heapDestroy(heap);
	/*HEAP* heap = (HEAP*)malloc(sizeof(HEAP));
	heap->size = num;
	heap->capacity = num;
	heap->data = arr;
	for (int i = 1; i < num; ++i)
		reheapUp(heap, i);

	while (!heapEmpty(heap)) {
		int index = heap->size - 1;
		heap->data[index] = heapDelete(heap);
	}
	free(heap);*/
}

int main()
{

	int val[] = { 100, 55, 234, 452, 10 ,23, 5, 3242 ,23 ,435 ,345 ,232 ,234, 12 , 2 ,3 };
	heapSort(val, 15);
	for (int i = 0; i < 15; ++i)
		printf("%d ", val[i]);
	return 0;

}