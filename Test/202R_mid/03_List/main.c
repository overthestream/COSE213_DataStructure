#include "orderedListADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void printHeader(const char* title);
void testInsertion(LIST* pList);
void testTraverse(LIST* pList);
void testFind(LIST* pList);
void testDeletion(LIST* pList);

STUDENT_GRADE csDummy[] =
{
	{320001, 2.0, 3.0, 2.5},
	{320002, 2.5, 3.5, 3.0},
	{320003, 4.5, 4.5, 4.5},
	{320004, 3.5, 3.5, 3.5},
	{320005, 3.5, 2.5, 3.0},
	{320006, 2.5, 3.5, 3.0},
	{320007, 4.5, 4.5, 3.0},
	{320008, 4.5, 4.5, 4.5},
};

int main()
{
	LIST* csStudents = createList(cmpStudentGrade, printStudentGrade);

	printHeader("Insertion Test");
	testInsertion(csStudents);

	printHeader("Traverse Test");
	testTraverse(csStudents);

	printHeader("Find Test");
	testFind(csStudents);

	printHeader("Deletion Test");
	testDeletion(csStudents);

	// Destory list
	destoryList(csStudents);

	return 0;
}

void testInsertion(LIST* pList)
{
	studentId expect[] = { 320008, 320003, 320007, 320004, 320006, 320005, 320002, 320001 };
	LIST_NODE* pNode = NULL;
	int dummySize = sizeof(csDummy) / sizeof(STUDENT_GRADE);
	int i = 0;

	for (i = 0; i < dummySize; i++)
	{
		if (!insertData(pList,
			csDummy[i].id,
			csDummy[i].gradeDS, csDummy[i].gradeDB, csDummy[i].gradeOS))
		{
			printf("INSERT FAIL: (ID: %d)\n", csDummy[i].id);
		}
	}

	assert(dummySize == listCount(pList) && "Dummy size == List count");

	pNode = pList->head;
	i = 0;
	while(pNode != NULL)
	{
		if(pNode->pData != NULL && pNode->pData->id == expect[i])
		{
			printf("PASS\n");
		}else
		{
			printf("INSERTION ERROR: (ID: %d)\n", csDummy[i].id);
		}

		++i;
		pNode = pNode->next;
	}
}

void testTraverse(LIST* pList)
{
	studentId expect[] = { 320008, 320003, 320007, 320004, 320006, 320005, 320002, 320001};
	STUDENT_GRADE* pStudent = NULL;
	int dummySize = sizeof(csDummy) / sizeof(STUDENT_GRADE);
	int i = 0;

	initTraversePos(pList);

	while (traverseList(pList, &pStudent))
	{
		if(pStudent != NULL && pStudent->id == expect[i])
		{
			printf("PASS\n");
		}else
		{
			printf("ERROR: (ID: %d)\n", expect[i]);
		}
		++i;
	}
}

void testFind(LIST* pList)
{
	double targets[] = { 4.5, 4.2, 4.0, 3.0, 2.5 };
	bool expect[] = {true, false, true, true, true};
	for (int i = 0; i < sizeof(targets) / sizeof(double); ++i)
	{
		double key = targets[i];
		STUDENT_GRADE* pStudent;

		if(findData(pList, key, &pStudent) == expect[i])
		{
			printf("PASS\n");
		}else
		{
			printf("ERROR: (KEY: %f)\n", targets[i]);
		}
	}
}

void testDeletion(LIST* pList)
{
	double targets[] = { 4.5, 4.5, 2.5, 3.0, 3.25 };
	bool expect[] = {true, true, true, true, false};
	for (int i = 0; i < sizeof(targets) / sizeof(double); ++i)
	{
		if(deleteData(pList, targets[i]) == expect[i])
		{
			printf("PASS\n");
		}else
		{
			printf("ERROR: (KEY: %f)\n", targets[i]);
		}
		double key = targets[i];
		
	}
}

void printHeader(const char* title)
{
	printf("\n####################\n# %s\n", title);
}
