//2017030519_홍유진_Algorithm
#include<stdio.h>
#include<iostream>
#include<climits>
using namespace std;

int n;
int p[200], m[200][200], s[200][200];
int min__ = INT_MAX;
void matrix_chain_order() {
	/*for (int i = 1; i <= N; i++) {
	m[i][i] = 0;
	}*/
	for (int l = 2; l <= n; l++) {//체인의 길이
		for (int i = 1; i <= n - l + 1; i++) {
			int j = i + l - 1;
			m[i][j] = INT_MAX;
			for (int k = i; k <= j - 1; k++) {
				int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (q < m[i][j]) {
					m[i][j] = q;
					if (m[i][j] < min__) {
						min__ = m[i][j];
					}
					s[i][j] = k;
				}
			}

		}
	}

}
int temp = 1;
void print(int i, int j) {
	if (i == j) {
		printf("%d ", temp++);
	}
	else {
		printf("( ");
		print(i, s[i][j]);
		print(s[i][j] + 1, j);
		printf(") ");
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i <= n; i++) {
		scanf("%d", p + i);
	}
	matrix_chain_order();
	printf("%d\n", m[1][n]);
	print(1, n);
	printf("\n");
}
