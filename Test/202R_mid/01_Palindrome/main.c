#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LENGTH	32

void testPalindromeLoop();
void testPalindromeRecur();
void printHeader(const char* title);

bool isPalindromeLoop(const char* str, int length)
{
	// TODO
	for (int i = 0; i <= (length - 1) / 2; ++i) {
		if (str[i] != str[length - 1 - i])
			return false;
	}
	return true;
}

bool isPalindromeRecur(const char* str, int length, int pos)
{
	// TODO
	if (pos > (length - 1) / 2) return true;

	if (str[pos] != str[length - 1 - pos]) return false;
	else return isPalindromeRecur(str, length, pos + 1);

}

int main()
{
	printHeader("Palindrome Loop Test");
	testPalindromeLoop();

	printHeader("Palindrome Recursion Test");
	testPalindromeRecur();

	return 0;
}

void testPalindromeLoop()
{
	bool expect[] = { true, true, true, true, false, false, false };
	char str[][MAX_STR_LENGTH] = { "abccba", "abcba", "aba", "a", "ab", "abc", "abca" };

	for (int i = 0; i < sizeof(str) / MAX_STR_LENGTH; ++i)
	{
		printf("Testcase %02d: %s\n", i + 1, str[i]);
		bool result = isPalindromeLoop(str[i], strlen(str[i]));
		if (expect[i] == result)
		{
			printf("PASS\n");
		}
		else
		{
			printf("ERROR (Expect: %s, Real: %s)\n", expect[i] ? "true" : "false", result ? "true" : "false");
		}
	}
}

void testPalindromeRecur()
{
	bool expect[] = { true, true, true, true, false, false, false };
	char str[][MAX_STR_LENGTH] = { "abccba", "abcba", "aba", "a", "ab", "abc", "abca" };

	for (int i = 0; i < sizeof(str) / MAX_STR_LENGTH; ++i)
	{
		printf("Testcase %02d: %s\n", i + 1, str[i]);
		bool result = isPalindromeRecur(str[i], strlen(str[i]), 0);
		if (expect[i] == result)
		{
			printf("PASS\n");
		}
		else
		{
			printf("ERROR (Expect: %s, Real: %s)\n", expect[i] ? "true" : "false", result ? "true" : "false");
		}
	}
}

void printHeader(const char* title)
{
	printf("\n####################\n# %s\n", title);
}