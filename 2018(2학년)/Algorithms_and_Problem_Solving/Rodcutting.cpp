//2017030519_È«À¯Áø_Algorithm
#include<stdio.h>
#include<algorithm>

using namespace std;

int p[200];
int r[200];
int s[200];
int n;

void cut_rod() {
	for (int j = 1; j <= n;j++) {
		int q = -3000000;
		for (int i = 1; i <= j; i++) {
			if (q < p[i] + r[j - i]) {
				q = p[i] + r[j - i];
				s[j] = i;
			}
			r[j] = q;
		}
	}
}

void print() {
	printf("%d\n", r[n]);
	while (n > 0) {
		printf("%d ", s[n]);
		n = n - s[n];
	}
	printf("\n");
}
int main() {

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", p + i);
	}
	cut_rod();
	print();
}