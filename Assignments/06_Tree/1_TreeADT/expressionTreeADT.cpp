#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "expressionTreeADT.h"

NODE* createTree(NODE* left, const char* dataPtr, NODE* right)
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	if (!newNode) return NULL;
	strcpy(newNode->data, dataPtr);
	newNode->left = left;
	newNode->right = right;
	return newNode;
}

void destroyTree(NODE* node)
{
	if (!node) return;
	if (node->left) destroyTree(node->left);
	if (node->right) destroyTree(node->right);
	free(node);
	return;
}

char* treeData(NODE* node)
{
	return node->data;
}

bool hasChild(NODE* node)
{
	if (node->left == NULL && node->right == NULL) return false;
	else return true;
}

double evaluate(NODE* node)
{
	if (!hasChild(node)) return atof(node->data);
	else if (node->left == NULL || node->right == NULL) return 0;
	else {
		double oper1 = evaluate(node->left), oper2 = evaluate(node->right);
		if (*treeData(node) == '+') return oper1 + oper2;
		else if (*treeData(node) == '*') return oper1 * oper2;
		else if (*treeData(node) == '/') return oper1 / oper2;
		else if (*treeData(node) == '-') return oper1 - oper2;
		else return 0;
	}

}

