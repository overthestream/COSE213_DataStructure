#include "avltreeadt.h"

AVL_TREE* avlCreate(int (*compare)(void* arg1, void* arg2)) 
{
	AVL_TREE* tree;

	tree = (AVL_TREE*)malloc(sizeof(AVL_TREE));
	if (tree) 
	{
		tree->root = NULL;
		tree->count = 0;
		tree->compare = compare;
	}

	return tree;
}

bool avlInsert(AVL_TREE* tree, void* dataInPtr) 
{
	AVL_NODE* newPtr;
	bool forTaller;

	newPtr = (AVL_NODE*)malloc(sizeof(AVL_NODE));
	if (!newPtr) return false;

	newPtr->bal = EH;
	newPtr->right = NULL;
	newPtr->left = NULL;
	newPtr->dataPtr = dataInPtr;

	tree->root = _avlInsert(tree, tree->root, newPtr, &forTaller);
	(tree->count)++;
	return true;
}

bool avlDelete(AVL_TREE* tree, void* dltKey) 
{
	bool shorter;
	bool success;
	AVL_NODE* newRoot;

	newRoot = _avlDelete(tree, tree->root, dltKey, &shorter, &success);

	if (success) {
		tree->root = newRoot;
		(tree->count)--;
		return true;
	}
	else return false;
}

void* avlRetrieve(AVL_TREE* tree, void* keyPtr) 
{
	if (tree->root) return _avlRetrieve(tree, keyPtr, tree->root);
	else return NULL;
}

void avlTraverse(AVL_TREE* tree, void (*process)(void* dataPtr)) 
{
	_avlTraversal(tree->root, process);
	printf("\n");
	return;
}

int avlCount(AVL_TREE* tree) 
{
	return (tree->count);
}

int avlHeight(AVL_TREE* tree)
{
	// TODO
	return _avlHeight(tree->root);

}

int _avlHeight(AVL_NODE* root)
{
	// TODO
	if (root == NULL) return 0;

	return _avlHeight(root->left) > _avlHeight(root->right) ? _avlHeight(root->left) + 1 : _avlHeight(root->right) + 1;

}

bool avlEmpty(AVL_TREE* tree) 
{
	return (tree->count == 0);
}

AVL_TREE* avlDestroy(AVL_TREE* tree) 
{
	if (tree)
		_avlDestroy(tree->root);
	free(tree);
	return NULL;
}

bool avlFull(AVL_TREE* tree) 
{
	AVL_NODE* newPtr;

	newPtr = (AVL_NODE*)malloc(sizeof(*(tree->root)));
	if (newPtr) 
	{
		free(newPtr);
		return false;
	}
	else return true;
}

AVL_NODE* _avlInsert(AVL_TREE* tree, AVL_NODE* root, AVL_NODE* newPtr, bool* taller)
{
	if (!root) 
	{
		//insert at root
		root = newPtr;
		*taller = true; // insert한 node의 바로 위 parent에게만 rotate를 해주기 위한 변수
		return root;
	} 

	if (tree->compare(newPtr->dataPtr, root->dataPtr) < 0) 
	{
		// new data < root --> go left 왼쪽에 insert를 함. 
		root->left = _avlInsert(tree, root->left, newPtr, taller);
		if (*taller) // 삽입 한 바로 위 parent라면?
		{
			//Left subtree is taller
			switch (root->bal) 
			{
			case LH: // 왼쪽 노드에 삽입을 했는데 이미 그 노드가 LH다? 미친련 바로 balance 조정 (LR, LL)
				root = insLeftBal(root, taller);
				break;
			case EH: // EH + 왼쪽 삽입 = LH
				root->bal = LH;
				break;
			case RH: // RH + 왼쪽 삽입 = EH
				root->bal = EH;
				*taller = false; // (EH - > taller가 아니게 됨)
				break;
			}
		}
		return root;
	} else 
	{
		// new data >= root --> go right / 오른쪽에 insert 함
		root->right = _avlInsert(tree, root->right, newPtr, taller);
		if (*taller) { // 삽입 한 바로 위 parent 일 때 
			switch (root->bal) {
			case LH: //LH + 오른족 삽입 = EH, EH-> taller X 
				root->bal = EH;
				*taller = false;
				break;
			case EH: //EH + 오른쪽 = RH
				root->bal = RH;
				break;
			case RH: //RH+ 오른쪽? ( RL, RR)바로 컽
				root = insRightBal(root, taller);
				break;
			}
		}
		return root;
	}
	return root;
}

AVL_NODE* insRightBal(AVL_NODE* root, bool* taller)
{
	AVL_NODE* rightTree;
	AVL_NODE* leftTree;
	rightTree = root->right;

	switch (rightTree->bal)
	{
	case LH: 
		// Left High - Requires double rotation:
		leftTree = rightTree->left;
		switch (leftTree->bal)//subtree 의 H 값 조정 
		{
		case RH: 
			root->bal = LH;
			rightTree->bal = EH;
			break;
		case EH:
			root->bal = EH;
			rightTree->bal = EH;
			break;
		case LH:
			root->bal = EH;
			rightTree->bal = RH;
			break;
		} // switch

		leftTree->bal = EH;
		root->right = rotateRight(rightTree);
		root = rotateLeft(root);
		*taller = false;
		break;
	case EH:
		printf("\n\a\aError in rightBalance\n");
		break;
		root->bal = EH;
		taller = false;
		break;
	case RH: 
		root->bal = EH;
		rightTree->bal = EH;
		root = rotateLeft(root);
		*taller = false;
		break;
	} // switch
	return root;
} // insRightBal

AVL_NODE* insLeftBal(AVL_NODE* root, bool* taller) 
{
	AVL_NODE* rightTree;
	AVL_NODE* leftTree;

	leftTree = root->left;
	switch (leftTree->bal) {
	case LH:
		root->bal = EH;
		leftTree->bal = EH;
		root = rotateRight(root);
		*taller = false;
		break;
	case EH:
		printf("\nError in insLeftBal\n");
		exit(100);
	case RH:
		rightTree = leftTree->right;
		switch (rightTree->bal) {
		case LH:
			root->bal = RH;
			leftTree->bal = EH;
			break;
		case EH:
			root->bal = EH;
			leftTree->bal = LH;
			break;
		case RH:
			root->bal = EH;
			leftTree->bal = LH;
			break;
		}
		rightTree->bal = EH;
		root->left = rotateLeft(leftTree);
		root = rotateRight(root);
		*taller = false;
	}
	return root;
}

AVL_NODE* _avlDelete(AVL_TREE* tree, AVL_NODE* root, void* dltKey, bool* shorter, bool* success) {
	AVL_NODE* dltPtr;
	AVL_NODE* exchPtr;
	AVL_NODE* newRoot;

	if (!root) 
	{
		*shorter = false;
		*success = false;
		return NULL;
	}

	if (tree->compare(dltKey, root->dataPtr) < 0) 
	{
		root->left = _avlDelete(tree, root->left, dltKey, shorter, success);
		if (*shorter) root = dltRightBal(root, shorter);
	}
	else if (tree->compare(dltKey, root->dataPtr) > 0) 
	{
		root->right = _avlDelete(tree, root->right, dltKey, shorter, success);
		if (*shorter)
			root = dltLeftBal(root, shorter);
	} else 
	{
		dltPtr = root;
		if (!root->right) 
		{
			newRoot = root->left;
			*success = true;
			*shorter = true;
			free(dltPtr);
			return newRoot;
		} else 
		{
			if (!root->left) 
			{
				newRoot = root->right;
				*success = true;
				*shorter = true;
				free(dltPtr);
				return newRoot;
			} else 
			{
				exchPtr = root->left;
				while (exchPtr->right)
					exchPtr = exchPtr->right;
				root->dataPtr = exchPtr->dataPtr;
				root->left = _avlDelete(tree, root->left, exchPtr->dataPtr, shorter, success);
				if (*shorter) root = dltRightBal(root, shorter);
			}
		}
	}
	return root;
}

AVL_NODE* dltRightBal(AVL_NODE* root, bool* shorter) 
{
	AVL_NODE* rightTree;
	AVL_NODE* leftTree;

	switch (root->bal) 
	{
	case LH:
		root->bal = EH;
		break;
	case EH:
		root->bal = RH;
		*shorter = false;
		break;
	case RH:
		rightTree = root->right;
		if (rightTree->bal == LH) 
		{
			leftTree = rightTree->left;
			switch (leftTree->bal) 
			{
			case LH:
				rightTree->bal = RH;
				root->bal = EH;
				break;
			case EH:
				root->bal = EH;
				rightTree->bal = EH;
				break;
			case RH:
				root->bal = LH;
				rightTree->bal = EH;
				break;
			}
			leftTree->bal = EH;

			root->right = rotateRight(rightTree);
			root = rotateLeft(root);
		} else 
		{
			switch (rightTree->bal) 
			{
			case LH:
			case RH:
				root->bal = EH;
				rightTree->bal = EH;
				break;
			case EH:
				root->bal = RH;
				rightTree->bal = LH;
				*shorter = false;
				break;
			}
			root = rotateLeft(root);
		}
	}
	return root;
}

AVL_NODE* dltLeftBal(AVL_NODE* root, bool* smaller)
{
	AVL_NODE* rightTree;
	AVL_NODE* leftTree;
	switch (root->bal)
	{
	case RH: root->bal = EH;
		break;
	case EH: root->bal = LH;
		*smaller = false;
		break;
	case LH: leftTree = root->left;
		switch (leftTree->bal)
		{
		case LH:
		case EH:
			if (leftTree->bal == EH)
			{
				root->bal = LH;
				leftTree->bal = RH;
				*smaller = false;
			}
			else
			{
				root->bal = EH;
				leftTree->bal = EH;
			}
			root = rotateRight(root);
			break;
		case RH:
			rightTree = leftTree->right;
			switch (rightTree->bal)
			{
			case LH:
				root->bal = RH;
				leftTree->bal = EH;
				break;
			case EH:
				root->bal = EH;
				leftTree->bal = EH;
				break;
			case RH:
				root->bal = EH;
				leftTree->bal = LH;
				break;
			}
			rightTree->bal = EH;
			root->left = rotateLeft(leftTree);
			root = rotateRight(root);
			break;
		}
	}
	return root;
}

AVL_NODE* rotateRight(AVL_NODE* root)
{
	AVL_NODE* tempPtr = NULL;
	tempPtr = root->left;
	root->left = tempPtr->right;
	tempPtr->right = root;
	return tempPtr;
} // rotateRight

AVL_NODE* rotateLeft(AVL_NODE* root)
{
	AVL_NODE* tempPtr = NULL;
	tempPtr = root->right;
	root->right = tempPtr->left;
	tempPtr->left = root;
	return tempPtr;
} // rotateLeft 

void* _avlRetrieve(AVL_TREE* tree, void* keyPtr, AVL_NODE* root) {
	if (root) 
	{
		if (tree->compare(keyPtr, root->dataPtr) < 0)
			return _avlRetrieve(tree, keyPtr, root->left);
		else if (tree->compare(keyPtr, root->dataPtr) > 0)
			return _avlRetrieve(tree, keyPtr, root->right);
		else
			return root->dataPtr;
	} else 
	{
		return NULL;
	}
}

void _avlTraversal(AVL_NODE* root, void (*process)(void* dataPtr)) {
	if (root) {
		_avlTraversal(root->left, process);
		process(root->dataPtr);
		_avlTraversal(root->right, process);
	}
	return;
}

void _avlDestroy(AVL_NODE* root) {
	if (root) {
		_avlDestroy(root->left);
		free(root->dataPtr);
		_avlDestroy(root->right);
		free(root);
	}
	return;
}
