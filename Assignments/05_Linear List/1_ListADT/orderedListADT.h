#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STR_MAX 32

typedef int studentId;

typedef struct
{
	studentId id;
	char name[STR_MAX];
	char email[STR_MAX];
} STUDENT;

typedef struct node
{
	STUDENT* pData;
	struct node* next;
} NODE;

typedef struct
{
	int listSize;
	NODE* pos; //pos : walking pointer ; iterator 
	NODE* head;
	NODE* rear;
	int(*compare) (STUDENT* pArg1, STUDENT* pArg2);
} LIST;

LIST* createList(int(*compare)(STUDENT* pArg1, STUDENT* pArg2));
void destoryList(LIST* pList);
bool insertData(LIST* pList, studentId id, char* name, char* email);
bool removeData(LIST* pList, studentId pKey);
bool searchData(LIST* pList, studentId pKey, STUDENT** pDataOut);
int listSize(LIST* pList);
bool isEmpty(LIST* pList);
void initIterator(LIST* pList);
bool iterateList(LIST* pList, STUDENT** pDataOut); //== traverse 
void printList(LIST* pList, void(*print)(STUDENT* pArg));

static bool _doInsert(LIST* pList, NODE* pPre, STUDENT* pDataIn);
static void _doRemove(LIST* pList, NODE* pPre, NODE* pCur);
static bool _doSearch(LIST* pList, NODE** pPre, NODE** pCur, studentId pKey);

bool makeStudent(STUDENT** pDataOut, studentId id, char* name, char* email);
void printStudent(STUDENT* pArg);
int cmpStudentId(STUDENT* student1, STUDENT* student2);
