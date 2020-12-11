#include "orderedListADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

LIST* createList(int(*fpCompare)(double avgLStudent, double avgRStudent),
	void(*fpPrint)(STUDENT_GRADE* pArg))
{
	LIST* list;

	list = (LIST*)malloc(sizeof(LIST));
	if (list)
	{
		list->head = NULL;
		list->pos = NULL;
		list->rear = NULL;
		list->listCount = 0;
		list->fpCompare = fpCompare;
		list->fpPrint = fpPrint;
	}

	return list;
}

void destoryList(LIST* pList)
{
	// TODO fin 

	for (LIST_NODE* pPre = NULL, *pCur = pList->head; pCur; pPre = pCur, pCur = pCur->next) {
		free(pCur->pData);
		free(pCur);
	}
	free(pList);

}

bool insertData(LIST* pList,
	studentId id, double gradeDS, double gradeDB, double gradeOS)
{
	LIST_NODE* pPre = NULL;
	LIST_NODE* pCur = NULL;

	STUDENT_GRADE* pData;
	makeStudentGrade(&pData, id, gradeDS, gradeDB, gradeOS);
	_exeFind(pList, &pPre, &pCur, pData->avg);

	initTraversePos(pList);
	return _exeInsert(pList, pPre, pData);
}

static bool _exeInsert(LIST* pList, LIST_NODE* pPre, STUDENT_GRADE* pDataIn)
{
	// TODO fin 

	LIST_NODE* newNode = (LIST_NODE*)malloc(sizeof(LIST_NODE));
	if (newNode == NULL) return false;

	newNode->pData = pDataIn;
	newNode->next = NULL;

	if (pPre == NULL) {
		newNode->next = pList->head;
		pList->head = newNode;
		if (listCount(pList) == 0) pList->rear = newNode;
	}
	else {
		newNode->next = pPre->next;
		pPre->next = newNode;
		if (newNode->next == NULL)
			pList->rear = newNode;
	}
	(pList->listCount)++;
	initTraversePos(pList);
	return true;
}

bool deleteData(LIST* pList, double avg)
{
	// TODO fin

	LIST_NODE* pPre = NULL;
	LIST_NODE* pCur = NULL;

	bool isFound = _exeFind(pList, &pPre, &pCur, avg);
	if (isFound) {
		_exeDelete(pList, pPre, pCur);
		return true;
	}
	else return false;



}

static void _exeDelete(LIST* pList, LIST_NODE* pPre, LIST_NODE* pCur)
{
	// TODO fin

	if (pPre == NULL)
		pList->head = pCur->next;
	else
		pPre->next = pCur->next;
	if (pCur->next == NULL)
		pList->rear = pPre;

	--(pList->listCount);

	free(pCur->pData);
	free(pCur);
	initTraversePos(pList);
	return;

}

bool findData(LIST* pList, double avg, STUDENT_GRADE** pDataOut)
{
	// TODO fin

	LIST_NODE* pPre = NULL, * pCur = NULL;
	bool isFound = _exeFind(pList, &pPre, &pCur, avg);
	if (isFound) {
		*pDataOut = pCur->pData;
		return true;
	}
	return false;

}

static bool _exeFind(LIST* pList, LIST_NODE** pPre, LIST_NODE** pCur, double avg)
{
	// TODOfin 
	double result;
	*pPre = NULL;
	*pCur = pList->head;
	if (listCount(pList) == 0) return false;

	if ((*pList->fpCompare)(avg, pList->rear->pData->avg) > 0) { //맨 뒤 것보다 작다면 . 
		*pPre = pList->rear;
		*pCur = NULL;
		return false;
	}
	while ((result = (*pList->fpCompare)(avg, (*pCur)->pData->avg)) > 0) {
		*pPre = *pCur;
		*pCur = (*pCur)->next;
	}
	if (result == 0) return true;
	else return false;

}

int listCount(LIST* pList)
{
	return pList->listCount;
}

void initTraversePos(LIST* pList)
{
	pList->pos = NULL;
}

bool traverseList(LIST* pList, STUDENT_GRADE** pDataOut)
{
	// TODO fin
	if (listCount(pList) == 0) {
		pList->pos = NULL;
		*pDataOut = NULL;
		return false;
	}

	if (pList->pos == NULL)
		pList->pos = pList->head;
	else pList->pos = pList->pos->next;

	if (pList->pos != NULL) {
		*pDataOut = pList->pos->pData;
		return true;
	}
	else {
		*pDataOut = NULL;
		return false;
	}

}

int cmpStudentGrade(double avgLStudent, double avgRStudent)
{
	// TODO fin 

	if (avgRStudent - avgLStudent > 0) return 1;
	else if (avgRStudent - avgLStudent < 0) return -1;
	else return 0;

}

bool makeStudentGrade(STUDENT_GRADE** pDataOut,
	studentId id, double gradeDS, double gradeDB, double gradeOS)
{
	STUDENT_GRADE* obj = (STUDENT_GRADE*)malloc(sizeof(STUDENT_GRADE));
	if (obj == NULL)
		return false;

	obj->id = id;
	obj->gradeDS = gradeDS;
	obj->gradeDB = gradeDB;
	obj->gradeOS = gradeOS;
	obj->avg = (gradeDS + gradeDB + gradeOS) / NUM_SUBJECTS;

	*pDataOut = obj;

	return true;
}

void printList(LIST* pList)
{
	STUDENT_GRADE* pData;
	initTraversePos(pList);

	while (traverseList(pList, &pData))
	{
		pList->fpPrint(pData);
	}
	printf("====================\n");
}

void printStudentGrade(STUDENT_GRADE* pStudent)
{
	if (pStudent != NULL)
	{
		printf("STUDENT ID: %d\nData Structure: %.1f\nDatabases: %.1f\nOperating Systems: %.1f\nAvg: %.2f\n",
			pStudent->id,
			pStudent->gradeDS, pStudent->gradeDB, pStudent->gradeOS,
			pStudent->avg);
		printf("--------------------\n");
	}
}

