#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "bstreeadt.h"
#include "avltreeadt.h"

int compareInt(void* argu1, void* argu2);

int main()
{
	int data[] = { 14, 23, 7, 10, 3, 6, 2, 33, 56, 80, 66, 70, 72, 74, 76, 77, 80, 81, 83 };


	//////////////////////////////
	// Binary search tree
	//////////////////////////////
	printf("//////////////////////////////\n// BS tree\n//////////////////////////////\n");
	BS_TREE* bsTree = bstCreate();

	for (int i = 0; i < sizeof(data) / sizeof(int); i++)
	{
		bstInsert(bsTree, data[i]);
		bstTraverse(bsTree, bstPrintData);
	}

	//printf("AVL Tree Height: %d\n", bstHeight(bsTree));

	bstDestroy(bsTree);

	//////////////////////////////
	// AVL tree
	//////////////////////////////
	printf("//////////////////////////////\n// AVL tree\n//////////////////////////////\n");
	AVL_TREE* avlTree = avlCreate(&compareInt);

	for (int i = 0; i < sizeof(data) / sizeof(int); i++)
	{
		int* iData = (int*)malloc(sizeof(int));
		if (!iData)
			return 0;

		*iData = data[i];
		avlInsert(avlTree, iData);
		avlTraverse(avlTree, bstPrintData);
	}

	//printf("AVL Tree Height: %d\n", avlHeight(avlTree));

	avlDestroy(avlTree);

	return 0;
}

int compareInt(void* argu1, void* argu2)
{
	int i1, i2;

	i1 = *(int*)argu1;
	i2 = *(int*)argu2;

	if (i1 < i2)
		return -1;
	if (i1 > i2)
		return 1;

	return 0;
}
