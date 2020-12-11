#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "orderedListADT.h"

void printHeader(const char* title);

STUDENT csDummy[] =
{
	{320001, "yangbong", "beebee@korea.ac.kr" },
	{320002, "hyoyong", "utility@korea.ac.kr" },
	{320003, "daegi", "waiting@korea.ac.kr" },
	{320004, "hyubjin", "hyubjinlee@korea.ac.kr" },
	{320005, "minsoo", "msdb@korea.ac.kr" }
};

int main()
{
	int dummySize = sizeof(csDummy) / sizeof(STUDENT);
	LIST* csStudents = createList(cmpStudentId);

	//////////////////////////////
	// Insert dummy data
	printHeader("Insert dummy data");
	for (int i = 0; i < dummySize; i++)
	{
		if (!insertData(csStudents, csDummy[i].id, csDummy[i].name, csDummy[i].email))
		{
			printf("Insertion failed\n");
		}
		else
		{
			printf("Inserted\n");
		}
	}

	//////////////////////////////
	// Iterate elements
	printHeader("Iterate elements");
	STUDENT* curStudent;
	while (iterateList(csStudents, &curStudent))
	{
		printStudent(curStudent);
	}
	initIterator(csStudents);

	//////////////////////////////
	// Search elements
	printHeader("Search elements");
	int searchKeyOrder[] = { 320001, 320003, 120001 };
	for (int i = 0; i < sizeof(searchKeyOrder) / sizeof(int); ++i)
	{
		int key = searchKeyOrder[i];
		STUDENT* pStudent;

		if (searchData(csStudents, key, &pStudent))
		{
			printf("Found a student (key: %d)\n", key);
			printStudent(pStudent);
		}
		else
		{
			printf("Search failed (key: %d)\n", key);
		}
	}

	//////////////////////////////
	// Remove elements
	printHeader("Remove elements");
	int eraseKeyOrder[] = { 320001, 320005, 320003, 320004, 320002 };
	for (int i = 0; i < sizeof(eraseKeyOrder) / sizeof(int); ++i)
	{
		int key = eraseKeyOrder[i];

		if (removeData(csStudents, key))
		{
			printf("Erase successed (key: %d)\n", key);
		}
		else
		{
			printf("Erase failed (key: %d)\n", key);
		}

		printList(csStudents, printStudent);
	}

	//////////////////////////////
	// List empty check
	printHeader("List empty check");
	if (isEmpty(csStudents))
		printf("Empty\n");
	else
		printf("Not empty\n");

	// Destory list
	destoryList(csStudents);

	return 0;
}

void printHeader(const char* title)
{
	printf("\n####################\n# %s\n", title);
}
