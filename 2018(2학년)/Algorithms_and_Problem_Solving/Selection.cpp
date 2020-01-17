//2017030519_홍유진_Algorithm
//전코드들의 학번을 잘못적었습니다.
#include<stdio.h>

int arr[30005];
int main() {
	int n, m;
	int temp;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", arr + i);
	}
	int k = 0;
	for (int i = 0; i < m; i++) {
		int min = i;
		for (int j = i+1; j < n; j++) {
			if (arr[min] > arr[j]) {
				min = j;
			}
		}
		temp = arr[min];
		arr[min] = arr[i];
		arr[i] = temp;
	}
	for (int i = 0; i < n; i++) {
		printf("%d\n", arr[i]);
	}
}