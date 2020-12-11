#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

long long fibMemoization(long long* arr, int n) {
	if (arr[n] != -1) return arr[n];
	else return arr[n] = fibMemoization(arr, n - 1) + fibMemoization(arr, n - 2);
}
int main(void)
{

	int n;
	scanf("%d", &n);

	long long* arr;
	arr = (long long*)malloc(sizeof(long long) * (n + 1));
	for (int i = 0; i <= n; i++)
		arr[i] = -1;
	arr[0] = 0, arr[1] = 1;
	for (int i = 0; i < 50; i++)
		fibMemoization(arr, i);
	printf("Memoization::\n");
	for (int i = 50; i <= n; i++)
		printf("%d : %lld\n", i, fibMemoization(arr, i));
	free(arr);
	return 0;
}
