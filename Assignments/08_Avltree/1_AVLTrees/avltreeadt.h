#pragma once
#include <stdio.h>
#include <stdbool.h>

typedef struct node 
{
	struct node* left;
	void* dataPtr;
	int bal;
	struct node* right;
} AVL_NODE;

typedef struct 
{
	int count;
	AVL_NODE* root;
	int (*compare)(void* arg1, void* arg2);
} AVL_TREE;

enum { LH , EH, RH };

AVL_TREE* avlCreate(int (*compare)(void* arg1, void* arg2));
AVL_TREE* avlDestroy(AVL_TREE* tree);

bool avlInsert(AVL_TREE* tree, void* dataInPtr);
bool avlDelete(AVL_TREE* tree, void* dltKey);
void* avlRetrieve(AVL_TREE* tree, void* keyPtr);
void avlTraverse(AVL_TREE* tree, void (*process)(void* dataPtr));

int avlCount(AVL_TREE* tree);
int avlHeight(AVL_TREE* tree);
int _avlHeight(AVL_NODE* root);
bool avlEmpty(AVL_TREE* tree);
bool avlFull(AVL_TREE* tree);

static AVL_NODE* _avlInsert(AVL_TREE* tree, AVL_NODE* root, AVL_NODE* newPtr, bool* taller);
static AVL_NODE* _avlDelete(AVL_TREE* tree, AVL_NODE* root, void* dltKey, bool* shorter, bool* success);
static void* _avlRetrieve(AVL_TREE* tree, void* keyPtr, AVL_NODE* root);
static void _avlTraversal(AVL_NODE* root, void (*process)(void* dataPtr));
static void _avlDestroy(AVL_NODE* root);

static AVL_NODE* rotateLeft(AVL_NODE* root);
static AVL_NODE* rotateRight(AVL_NODE* root);
static AVL_NODE* insLeftBal(AVL_NODE* root, bool* taller);
static AVL_NODE* insRightBal(AVL_NODE* root, bool* taller);
static AVL_NODE* dltLeftBal(AVL_NODE* root, bool* shorter);
static AVL_NODE* dltRightBal(AVL_NODE* root, bool* shorter);
