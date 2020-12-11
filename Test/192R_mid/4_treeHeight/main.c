#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binaryTreeADT.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int getTreeHeight(TREE_NODE* node)
{
	// Write your code here.
}

int getTreeWeight(TREE_NODE* node)
{
	// Write your code here.
}

int main()
{
	TREE_NODE* rootNode = buildDummyTree();

	printf("Height: %d\n", getTreeHeight(rootNode));
	printf("Number of nodes: %d\n", getTreeWeight(rootNode));

	return 0;
}
