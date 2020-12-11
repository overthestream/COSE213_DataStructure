#define _CRT_SECURE_NO_WARNINGS
#include "orderedListADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static bool _doInsert(LIST* pList, NODE* pPre, STUDENT* pDataIn)
{
	NODE* pNew = NULL;

	if (!(pNew = (NODE*)malloc(sizeof(NODE))))
		return false; 
	pNew->pData = pDataIn;
	pNew->next = NULL;

	if (pPre == NULL) { 
		pNew->next = pList->head;
		pList->head = pNew;
		if (isEmpty(pList))
			pList->rear = pNew;
	}
	else{
		pNew->next = pPre->next;
		pPre->next = pNew;
		if (pNew->next == NULL)
			pList->rear = pNew;
	}
	(pList->listSize)++;
	initIterator(pList);
	return true;
}

static void _doRemove(LIST* pList, NODE* pPre, NODE* pCur)
{
	
	if (pPre == NULL)
		pList->head = pCur->next;
	else
		pPre->next = pCur->next;
	if (pCur->next == NULL) 
		pList->rear = pPre;

	(pList->listSize)--;

	free(pCur->pData);
	free(pCur); 
	initIterator(pList);
	return;

}

static bool _doSearch(LIST* pList, NODE** pPre, NODE** pLoc, studentId pKey)
{

	int result;
	*pPre = NULL;
	*pLoc = pList->head;
	if (isEmpty(pList)) return false;
	if ((*pList->compare)((STUDENT*)&pKey, pList->rear->pData)>0){
		*pPre = pList->rear;
		*pLoc = NULL;
		return false; 
	}
	while ( (result = (*pList->compare)((STUDENT*)&pKey, (*pLoc)->pData)) > 0){
		*pPre = *pLoc;
		*pLoc = (*pLoc)->next;
	}
	if (result == 0)
		return true;
	else return false; 

}

LIST* createList(int(*compare)(STUDENT* pArg1, STUDENT* pArg2))
{
	LIST* list = NULL;
	list = (LIST*)malloc(sizeof(LIST));
	if (list) {
		list->head = NULL;
		list->pos = NULL;
		list->rear = NULL;
		list->listSize = 0;
		list->compare = compare;
	}
	return list;
}

void destoryList(LIST* pList)
{
	
	for (NODE* pPre = NULL, *pCur = pList->head; pCur; pPre = pCur, pCur = pCur->next) {
		free(pCur->pData);
		free(pCur);
	}
	free(pList);
}

bool insertData(LIST* pList, studentId id, char* name, char* email)
{

	STUDENT* newStudent = NULL;
	if (makeStudent(&newStudent, id, name, email)) {
		NODE* pPre = NULL, * pLoc = NULL;
		if (_doSearch(pList, &pPre, &pLoc, id)) {
			free(newStudent);
			return false;
		}
		_doInsert(pList, pPre, newStudent);
		return true;
	}
	else return false;

}

bool removeData(LIST* pList, studentId pKey)
{
	NODE* pPre = NULL, * pLoc = NULL;
	bool isFound = _doSearch(pList, &pPre, &pLoc, pKey);
	if (isFound) {
		_doRemove(pList, pPre, pLoc);
		return true;
	}
	else return false;
} 

bool searchData(LIST* pList, studentId pKey, STUDENT** pDataOut)
{
	NODE* pPre = NULL, * pLoc = NULL;
	bool isFound = _doSearch(pList, &pPre, &pLoc, pKey);
	if (isFound) {
		*pDataOut = pLoc->pData;
		return true;
	}
	return false;
}

int listSize(LIST* pList)
{
	return pList->listSize;
}

bool isEmpty(LIST* pList)
{
	if (pList->listSize) return false;
	else return true;
}

void initIterator(LIST* pList)
{
	pList->pos = NULL;
}

bool iterateList(LIST* pList, STUDENT** pDataOut)
{
	if (isEmpty(pList)) {
		pList->pos = NULL;
		*pDataOut = NULL;
		return false;
	}
	if (!pList->pos)
		pList->pos = pList->head;
	else pList->pos = pList->pos->next;

	if (pList->pos) {
		*pDataOut = pList->pos->pData;
		return true;
	}
	else {
		*pDataOut = NULL;
		return false;
	}
}

void printList(LIST* pList, void(*print)(STUDENT* pArg))
{
	initIterator(pList);
	STUDENT* pCur = NULL;
	while (iterateList(pList,&pCur)) {
		(*print)(pCur);
	}
}

bool makeStudent(STUDENT** pDataOut, studentId id, char* name, char* email)
{
	STUDENT* newStudent = (STUDENT*)malloc(sizeof(STUDENT));
	if (!newStudent) return false;
	strcpy(newStudent->email,email);
	strcpy(newStudent->name, name);
	newStudent->id = id;
	*pDataOut = newStudent;
	return true;
}

void printStudent(STUDENT* pStudent)
{
	printf("STUDENT ID: %d\n", pStudent->id);
	printf("NAME: %s\n", pStudent->name);
	printf("EMAIL: %s\n", pStudent->email);
	printf("----------------\n");
}

int cmpStudentId(STUDENT* pStudent1, STUDENT* pStudent2)
{
	return pStudent1->id - pStudent2->id;
}
