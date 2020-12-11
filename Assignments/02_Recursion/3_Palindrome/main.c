#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

int getStrLength(const char* str, int length) {

	if (str[length] == 0) return length;

	else return getStrLength(str, length + 1);

}

bool palindrome(const char* str, int start, int end) {

	if (start >= end) return true;
	else {
		if (str[start] == str[end]) return palindrome(str, start + 1, end - 1);
		else return false;
	}

}

int main(void)
{
	int T = 4;

	while (T--) {
		char word[100];
		scanf("%s", word);

		int length = getStrLength(word, 0);
		printf("%s: ", word);
		if (palindrome(word, 0, length - 1))
			printf("The string is palindrome\n");
		else
			printf("The string is not palindrome\n");
	}

	return 0;
}
