//2017030519_È«À¯Áø_Algorithm
#include<stdio.h>
int a[100005];
int temp[1000005];
void merge(int *a, int st, int mid, int end) {
	int i = st;
	int j = mid + 1;
	int k = st;
	while (i <= mid&&j <= end) {
		if (a[i] < a[j]) {
			temp[k++] = a[j++];
		}
		else {
			temp[k++] = a[i++];
		}
	}
	int m = (i > mid) ? j : i;
	int n = (i > mid) ? end : mid;

	for (; m <= n; m++) {
		temp[k++] = a[m];
	}
	for (m = st; m <= end; m++) {
		a[m] = temp[m];
	}
}
void merge_sort(int *a, int st, int end) {
	int mid = (st + end) / 2;
	if (st < end) {
		merge_sort(a, st, mid);
		merge_sort(a, mid + 1, end);
		merge(a, st, mid, end);
	}
}
int main() {
	int n, j;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", a + i);
	}
	merge_sort(a, 0, n - 1);
	for (int i = 0; i < n; i++) {
		printf("%d\n", a[i]);
	}
	return 0;
}