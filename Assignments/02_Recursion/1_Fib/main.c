#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int fibLoop(int n) {
	
	if (n == 0) return 0;
	else if (n == 1) return 1;

	int morePrev = 0, prev = 1, result=1;
	
	for (int i= 2; i <= n; i++) {

		result = morePrev + prev;

		morePrev = prev;
		prev = result;

	}

	return result;

}
int fibRecursion(int n) {

	if (n == 0) return 0;
	else if (n == 1) return 1;
	return fibRecursion(n - 2) + fibRecursion(n - 1);

}
int main(void)
{
	
	int n;
	scanf("%d", &n);

	printf("Loop::\n");
	for (int i = 0; i <= n; i++)
		printf("%d : %d\n", i, fibLoop(i));

	printf("-------------------\n");

	printf("Recursion::\n");
	for (int i = 0; i <= n; i++)
		printf("%d : %d\n", i, fibRecursion(i));

	return 0;
}
