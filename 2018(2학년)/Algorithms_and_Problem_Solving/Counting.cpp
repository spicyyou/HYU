//2017030519_È«À¯Áø_Algorithm

#include<stdio.h>
int n, m, k;
int a[100005], b[100005], c[100005];
int temp[100005];
int a0[100005], b0[100005];
void counting_sort(int key) {//key=m
	int i, j;
	for (j = 1; j <= n; j++) {
		c[a[j]]++;
	}
	for (i = 0; i <= key; i++) {
		c[i] = c[i] + c[i - 1];
		//temp[i] = c[i];
	}
	for (j = n; j >= 1; j--) {
		b[c[a[j]] - 1] = a[j];
		//c[a[j]] = c[a[j]] - 1;
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= k; i++) {
		scanf("%d%d", a0 + i, b0 + i);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
	}
	counting_sort(m);
	for (int i = 1; i <= k; i++) {
		int cnt = 0; cnt = c[b0[i]] - c[a0[i] - 1];
		printf("%d\n", cnt);
	}
}