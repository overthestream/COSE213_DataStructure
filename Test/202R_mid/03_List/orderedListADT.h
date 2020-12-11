#pragma once
#ifndef _ORDEREDLIST_ADT_H_
#define _ORDEREDLIST_ADT_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define NUM_SUBJECTS	3

typedef int studentId;

typedef struct
{
	studentId id;				// student ID
	double gradeDS;				// data structure grade
	double gradeDB;				// databases grade
	double gradeOS;				// operating systems grade
	double avg;					// student's average grade
} STUDENT_GRADE;

typedef struct node
{
	STUDENT_GRADE* pData;
	struct node* next;
} LIST_NODE;

typedef struct
{
	int listCount;
	LIST_NODE* pos;
	LIST_NODE* head;
	LIST_NODE* rear;
	int(*fpCompare) (double avgLStudent, double avgRStudent);	// function pointer for ordering nodes
	void(*fpPrint)(STUDENT_GRADE* pArg);						// function pointer for printing a node data
} LIST;

LIST* createList(int(*fpCompare)(double avgLStudent, double avgRStudent),
				 void(*fpPrint)(STUDENT_GRADE* pArg));
void destoryList(LIST* pList);
bool insertData(LIST* pList, 
				studentId id, double gradeDS, double gradeDB, double gradeOS);
bool deleteData(LIST* pList, double avg);
bool findData(LIST* pList, double avg, STUDENT_GRADE** pDataOut);
int listCount(LIST* pList);
void initTraversePos(LIST* pList);
bool traverseList(LIST* pList, STUDENT_GRADE** pDataOut);

static bool _exeInsert(LIST* pList, LIST_NODE* pPre, STUDENT_GRADE* pDataIn);
static void _exeDelete(LIST* pList, 
					   LIST_NODE* pPre, LIST_NODE* pCur);
static bool _exeFind(LIST* pList, 
					 LIST_NODE** pPre, LIST_NODE** pCur,
					 double avg);

int cmpStudentGrade(double avgLStudent, double avgRStudent);

bool makeStudentGrade(STUDENT_GRADE** pDataOut,
					  studentId id, double gradeDS, double gradeDB, double gradeOS);
void printList(LIST* pList);					  
void printStudentGrade(STUDENT_GRADE* pArg);


#endif	// _ORDEREDLIST_ADT_H_
