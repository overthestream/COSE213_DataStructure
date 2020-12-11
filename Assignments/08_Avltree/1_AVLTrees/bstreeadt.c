#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "bstreeadt.h"

BS_TREE* bstCreate()
{
	BS_TREE* tree = (BS_TREE*)malloc(sizeof(BS_TREE));
	if (tree)
	{
		tree->root = NULL;
		tree->count = 0;
	}

	return tree;
}

void bstDestroy(BS_TREE* tree)
{
	if (tree)
	{
		_bstDestroy(tree->root);
		tree->count = 0;

		free(tree);
	}
}

void _bstDestroy(TREE_NODE* root)
{
	if (root)
	{
		_bstDestroy(root->left);
		_bstDestroy(root->right);
		free(root);
	}
}

bool bstInsert(BS_TREE* tree, int data)
{
	TREE_NODE* newPtr = (TREE_NODE*)malloc(sizeof(TREE_NODE));
	newPtr->left = NULL;
	newPtr->right = NULL;
	newPtr->data = data;

	if (tree->root == NULL || tree->count == 0)
	{
		tree->root = newPtr;
		tree->count = 1;
		return true;
	}

	tree->root = _bstInsert(tree, tree->root, newPtr);
	(tree->count)++;
	return true;
}

TREE_NODE* _bstInsert(BS_TREE* tree, TREE_NODE* root, TREE_NODE* newPtr)
{
	if (!root)
		return newPtr;

	if (newPtr->data < root->data)
	{
		root->left = _bstInsert(tree, root->left, newPtr);
		return root;
	}
	else
	{
		root->right = _bstInsert(tree, root->right, newPtr);
		return root;
	}
}

void bstDelete(BS_TREE* tree, int key)
{
	tree->root = _bstDelete(tree->root, key);
}

TREE_NODE* _bstDelete(TREE_NODE* root, int key)
{
	if (root == NULL)
	{
		return NULL;
	}

	if (key < root->data)
	{
		root->left = _bstDelete(root->left, key);
	}
	else if (key > root->data)
	{
		root->right = _bstDelete(root->right, key);
	}
	else if (key == root->data)
	{
		if (root->left == NULL && root->right == NULL)
		{
			free(root);
			return NULL;
		}
		else if (root->left != NULL && root->right == NULL)
		{
			TREE_NODE* newRoot = root->left;
			free(root);
			return newRoot;
		}
		else if (root->left == NULL && root->right != NULL)
		{
			TREE_NODE* newRoot = root->right;
			free(root);
			return newRoot;
		}
		else
		{
			TREE_NODE* exchPtr = findLargetNode(root->left);

			root->data = exchPtr->data;
			root->left = _bstDelete(root->left, exchPtr->data);
		}
	}

	return root;
}

TREE_NODE* findLargetNode(TREE_NODE* root)
{
	if (root == NULL)
		return NULL;

	if (root->right)
	{
		return findLargetNode(root->right);
	}

	return root;
}

TREE_NODE* bstSearch(BS_TREE* tree, int key)
{
	if (tree == NULL)
		return NULL;
	return _bstSearch(tree->root, key);
}

TREE_NODE* _bstSearch(TREE_NODE* root, int key)
{
	if (root == NULL)
		return NULL;
	if (key < root->data)
	{
		return _bstSearch(root->left, key);
	}
	else if (key > root->data)
	{
		return _bstSearch(root->right, key);
	}
	else
	{
		return root;
	}
}

void bstTraverse(BS_TREE* tree, void(*process)(TREE_NODE* root))
{
	_bstTraverse(tree->root, process);
	printf("\n");
}

void _bstTraverse(TREE_NODE* root, void(*process)(TREE_NODE* root))
{
	if (root)
	{
		_bstTraverse(root->left, process);
		process(root);
		_bstTraverse(root->right, process);
	}
}

void bstPrintData(TREE_NODE* root)
{
	if (root)
	{
		printf("%d\t", root->data);
	}
}

bool bstEmpty(BS_TREE* tree)
{
	return tree->count == 0;
}

int bstCount(BS_TREE* tree)
{
	return tree->count;
}

int bstHeight(BS_TREE* tree)
{
	// TODO
	return _bstHeight(tree->root);
}

int _bstHeight(TREE_NODE* root)
{
	// TODO
	if (root == NULL) return 0;
	return _bstHeight(root->left) > _bstHeight(root->right) ? _bstHeight(root->left) + 1 : _bstHeight(root->right) + 1;
}
