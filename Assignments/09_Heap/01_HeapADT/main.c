#include <stdio.h>
#include "heapADT.h"

int main()
{
	// 질문 : maxsize 안정해져있는데 본인이 capacity 설정해서 realloc 하면서 하면 되나? X 리얼록 하지마
	// delete 는 값을 return하나 ? Yes  / false = -1
	// heap traverse ? -> 그냥 array 나열  
	HEAP* heap = heapCreate();
	int val[] = { 100, 55, 234, 452, 10 };

	for (int i = 0; i < sizeof(val) / sizeof(int); i++)
	{
		if (!heapInsert(heap, val[i]))
		{
			printf("Error: inserting %d\n", val[i]);
		}

		heapTraverse(heap);
	}

	for (int i = 0; i < sizeof(val) / sizeof(int); i++)
	{
		heapDelete(heap);
		heapTraverse(heap);
	}

	heapDestroy(heap);

	return 0;

}