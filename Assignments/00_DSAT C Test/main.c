#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

void sort(int* arr, int len) {
	int sorted = 1;
	int cmp;
	while (sorted) {
		sorted = 0;
		for (int i = 1; i < len; i++)
			if (arr[i] > arr[i - 1]) {
				cmp = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = cmp;
				sorted = 1;
			}
	}
}

int main()
{
	int N;
	scanf("%d", &N);
	int* arr = (int*)malloc(sizeof(int) * N);
	for (int i = 0; i < N; i++) {
		scanf(" %d", arr + i);
	}
	sort(arr, N);
	printf("Min: %d, Max: %d, Median: %.1f", arr[N-1], arr[0], N % 2 == 0 ? (double)(arr[N / 2] + arr[N / 2 - 1]) / 2.0 : arr[N / 2]);
	return 0;
}