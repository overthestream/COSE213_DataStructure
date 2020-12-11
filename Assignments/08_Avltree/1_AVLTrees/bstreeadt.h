#pragma once
#include <stdio.h>
#include <stdbool.h>

typedef struct treeNode
{
	int data;
	struct treeNode* left;
	struct treeNode* right;
} TREE_NODE;

typedef struct
{
	int count;
	TREE_NODE* root;
} BS_TREE;

BS_TREE* bstCreate();
void bstDestroy(BS_TREE* tree);
static void _bstDestroy(TREE_NODE* root);

bool bstInsert(BS_TREE* tree, int data);
TREE_NODE* _bstInsert(BS_TREE* tree, TREE_NODE* root, TREE_NODE* newPtr);
void bstDelete(BS_TREE* tree, int key);
TREE_NODE* _bstDelete(TREE_NODE* root, int key);
TREE_NODE* findLargetNode(TREE_NODE* root);
TREE_NODE* bstSearch(BS_TREE* tree, int key);
TREE_NODE* _bstSearch(TREE_NODE* root, int key);

void bstTraverse(BS_TREE* tree, void(*process)(TREE_NODE* root));
void _bstTraverse(TREE_NODE* root, void (*process)(TREE_NODE* root));
void bstPrintData(TREE_NODE* root);

bool bstEmpty(BS_TREE* tree);
int bstCount(BS_TREE* tree);
int bstHeight(BS_TREE* tree);
int _bstHeight(TREE_NODE* root);
