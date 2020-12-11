#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "binarySearchTreeADT.h"

BST_TREE* bstCreate()
{
	// fin.

	BST_TREE* tree = (BST_TREE*)malloc(sizeof(BST_TREE));

	if (tree) {
		tree->root = NULL;
		tree->count = 0;
	}
	return tree;

}

void bstDestroy(BST_TREE* tree)
{
	// fin

	if (tree == NULL) return;
	_bstDestroy(tree->root);
	free(tree);
}

void _bstDestroy(TREE_NODE* root)
{
	// fin
	if (root == NULL) return;
	if (root->left) _bstDestroy(root->left);
	if (root->right) _bstDestroy(root->right);

	free(root);

}

bool bstInsert(BST_TREE* tree, int data)
{
	// fin
	TREE_NODE* newPtr = (TREE_NODE*)malloc(sizeof(TREE_NODE));
	if (!newPtr) return false;
	newPtr->data = data;
	newPtr->left = NULL;
	newPtr->right = NULL;
	tree->root = _bstInsert(tree->root, newPtr);
	++(tree->count);
	return true;


}

TREE_NODE* _bstInsert(TREE_NODE* root, TREE_NODE* newPtr)
{
	// fin

	if (root == NULL)
		return newPtr;

	if (root->data <= newPtr->data) root->right = _bstInsert(root->right, newPtr);
	else root->left = _bstInsert(root->left, newPtr);

	return root;

}

void bstDelete(BST_TREE* tree, int key)
{
	// fin

	if (tree == NULL) return;
	tree->root = _bstDelete(tree->root, key);
	--(tree->count);
}

TREE_NODE* _bstDelete(TREE_NODE* root, int key)
{
	// fin
	if (root == NULL) return NULL;

	if (key < root->data)
		root->left = _bstDelete(root->left, key);
	else if (key > root->data)
		root->right = _bstDelete(root->right, key);
	else {
		TREE_NODE* delPtr = root;
		if (root->right == NULL) {
			root = root->left;
			free(delPtr);
			return root;
		}
		else if (root->left == NULL) {
			root = root->right;
			free(delPtr);
			return root;
		}
		else {
			for (delPtr = root->left; delPtr->right != NULL; delPtr = delPtr->right);
			root->data = delPtr->data;
			root->left = _bstDelete(root->left, delPtr->data);
		}
	}
	return root;
}

TREE_NODE* bstSearch(BST_TREE* tree, int key)
{
	// fin
	if (tree == NULL) return NULL;
	TREE_NODE* node = _bstSearch(tree->root, key);
	return node;

}

TREE_NODE* _bstSearch(TREE_NODE* root, int key)
{
	// fin
	/* 
	// iterative search
	while(root!=NULL){
		if(key == root->data)
			break;
		else if (key < root ->data)
			root = root -> left;
		else if (key > root->data)
			root= root ->right;
	}
	return root;
	*/
	if (root == NULL) return NULL;

	if (key == root->data) return root;
	else if (key < root->data) return _bstSearch(root->left, key);
	else return _bstSearch(root->right, key);

}

void bstTraverse(BST_TREE* tree, void(*process)(TREE_NODE* root))
{
	// fin

	if (tree == NULL) return;
	_bstTraverse(tree->root, process);
	printf("\n");

}

void _bstTraverse(TREE_NODE* root, void(*process)(TREE_NODE* root))
{
	// fin
	if (root == NULL) return;

	_bstTraverse(root->left, process);
	process(root);
	_bstTraverse(root->right, process);

}

void bstPrintData(TREE_NODE* root)
{
	if (root)
	{
		printf("%d\t", root->data);
	}
}

bool bstEmpty(BST_TREE* tree)
{
	return tree->count == 0;
}

int bstCount(BST_TREE* tree)
{
	return tree->count;
}