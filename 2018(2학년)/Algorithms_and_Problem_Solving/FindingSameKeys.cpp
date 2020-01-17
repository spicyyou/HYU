//2017030519_È«À¯Áø_A
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<stack>
#include<vector>
#include<string.h>
using namespace std;

int a[100005];
int b[100005];
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", a + i);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d", b + i);
	}
	//1 2 3 4 5 6 9
	// 3 4 5 7 8
	sort(a, a + n);
	sort(b, b + m);
	int i = 0, j = 0;
	int cnt = 0;
	while (1) {
		if (i >= n || j >= m) { break; }
		if (a[i] == b[j]) {
			cnt++;
			i++;
			j++;
		}
		else if (a[i]>b[j]) {
			j++;
		}
		else {
			i++;
		}
	}
	printf("%d\n", cnt);

}