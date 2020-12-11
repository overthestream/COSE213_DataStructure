#define _CRT_SECURE_NO_WARNINGS

#include "stackADT.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define STR_MAX 256

bool braceCheck(const char* str)
{
	// Write your code here.
}

int main(void)
{
	char str[STR_MAX];
	printf("Enter a string: \n");

	while (true)
	{
		scanf("%s", str);
		if (strcmp(str, "exit") == 0)
		{
			break;
		}

		if (braceCheck(str))
		{
			printf("Yes\n");
		}
		else
		{
			printf("No\n");
		}

	}

	return 0;
}