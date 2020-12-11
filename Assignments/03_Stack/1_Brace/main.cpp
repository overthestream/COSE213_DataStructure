#include "stackADT.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>



void catStackTest()
{
	char* data;

	////////////////////////////////////////
	// Fill stack A
	STACK* A = createStack();
	data = (char*)malloc(sizeof(char));
	*data = 'e';
	pushStack(A, data);
	data = (char*)malloc(sizeof(char));
	*data = 'd';
	pushStack(A, data);
	data = (char*)malloc(sizeof(char));
	*data = 'c';
	pushStack(A, data);

	////////////////////////////////////////
	// Fill stack B
	STACK* B = createStack();
	data = (char*)malloc(sizeof(char));
	*data = 'b';
	pushStack(B, data);
	data = (char*)malloc(sizeof(char));
	*data = 'a';
	pushStack(B, data);

	// concatenate
	catStack(A, B);

	////////////////////////////////////////
	// Print char values in Stack A
	//
	// EXPECTED OUTPUT:
	// a, b, c, d, e
	while (stackTop(A) != NULL)
	{
		printf("%c", *(char*)stackTop(A));
		popStack(A);

		if (stackTop(A) != NULL)
		{
			printf(", ");
		}
	}
	printf("\n");
	destroyStack(A);
}

bool braceCheck(const char* str)
{
	// TODO
	int length = strlen(str);
	STACK* stack = createStack();
	char* data;
	for (int i = 0; i < length; ++i) {

		if (strchr("({[", str[i]) != NULL) {
			data = (char*)malloc(sizeof(char));
			if (str[i] == '(') *data = ')';
			else if (str[i] == '{') *data = '}';
			else *data = ']';
			pushStack(stack, data);
		}

		if (strchr(")}]", str[i]) != NULL) {
			if (stack->top == NULL) {
				destroyStack(stack);
				return false;
			}
			else if (*(char*)stackTop(stack) != str[i]) {
				destroyStack(stack);
				return false;
			}
			else popStack(stack);
		}
	}
	if (stack->top == NULL) {
		destroyStack(stack);
		return true;
	}
	else {
		destroyStack(stack);
		return false;
	}
}

void braceCheckTest()
{
	const int numTestCase = 7;
	int i = 0;
	char str[numTestCase][100] = {
		{"So when I die (the [first] I will see in (heaven) is a score list)."},
		{"[ first in ] ( first out )."},
		{"Half Moon tonight (At least it is better than no Moon at all]."},
		{"A rope may form )( a trail in a maze."},
		{"Help( I[m being held prisoner in a fortune cookie factory)]."},
		{"([ (([( [ ] ) ( ) (( ))] )) ])."},
		{"."}
	};

	for (i = 0; i < numTestCase; ++i)
	{
		if (braceCheck(str[i]))
		{
			printf("yes\n");
		}
		else
		{
			printf("no\n");
		}
	}
}

int main(void)
{
	catStackTest();

	braceCheckTest();

	return 0;
}