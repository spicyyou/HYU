//2017030519_È«À¯Áø_A
#include<stdio.h>
int a[100005];
void merge_sort(int *a, int st, int end) {
	int mid = (st + end) / 2;
	if (st < end) {
		merge
	}
}
int main() {
	int n,j;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", a + i);
	}
	for (int i = 1; i < n; i++) {
		int temp = a[i];
		j = i - 1;
		while (j >= 0 && a[j] < temp) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = temp;
	}
	for (int i = 0; i < n; i++) {
		printf("%d\n", a[i]);
	}
	return 0;
}