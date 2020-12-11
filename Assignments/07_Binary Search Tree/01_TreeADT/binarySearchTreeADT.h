#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
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
} BST_TREE;

BST_TREE* bstCreate();
void bstDestroy(BST_TREE* tree);
static void _bstDestroy(TREE_NODE* root);

bool bstInsert(BST_TREE* tree, int data);
TREE_NODE* _bstInsert(TREE_NODE* root, TREE_NODE* newPtr);
void bstDelete(BST_TREE* tree, int key);
TREE_NODE* _bstDelete(TREE_NODE* root, int key);
TREE_NODE* bstSearch(BST_TREE* tree, int key);
TREE_NODE* _bstSearch(TREE_NODE* root, int key);

void bstTraverse(BST_TREE* tree, void(*process)(TREE_NODE* root));
void _bstTraverse(TREE_NODE* root, void (*process)(TREE_NODE* root));
void bstPrintData(TREE_NODE* root);

bool bstEmpty(BST_TREE* tree);
int bstCount(BST_TREE* tree);
