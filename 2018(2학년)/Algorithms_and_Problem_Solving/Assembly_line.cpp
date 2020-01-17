//2017030519_È«À¯Áø_Algorithm
#include<stdio.h>
#include<algorithm>
#include<stack>
#include<iostream>
using namespace std;

int a[200][200];
int t[200][200];
int t1[200];
int t2[200];
int l[200][200];
int n;
int e1, e2;
int x1, x2;
int trk, cnt;
stack<int> st;
void assembly() {
	t1[0] = e1 + a[0][0];
	t2[0] = e2 + a[1][0];
	l[0][0] = l[0][1] = -1;
	for (int i = 1; i < n; i++) {
		t1[i] = min(t1[i - 1] + a[0][i], t2[i - 1] + t[1][i] + a[0][i]);
		t2[i] = min(t2[i - 1] + a[1][i], t1[i - 1] + t[0][i] + a[1][i]);
		l[i][0] = (t1[i] == t1[i - 1] + a[0][i]) ? (1) : (2);
		l[i][1] = (t2[i] == t2[i - 1] + a[1][i]) ? (2) : (1);
	}
	int res = min(t1[n - 1] + x1, t2[n - 1] + x2);
	printf("%d\n", min(t1[n - 1] + x1, t2[n - 1] + x2));
	trk = (t1[n - 1] + x1 < t2[n - 1] + x2) ? (1) : (2);
	cnt = n - 1;
	while (trk != -1)
	{
		st.push(trk);

		trk = l[cnt][trk - 1];
		cnt--;
	}
	for (int i = 1; i <= n; i++) {
		printf("%d %d\n", st.top(), i);
		st.pop();
	}
}
int main() {
	scanf("%d%d%d%d%d", &n, &e1, &e2, &x1, &x2);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[0][i]);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[1][i]);
	}
	for (int i = 1; i < n; i++) {
		scanf("%d", &t[0][i]);
	}
	for (int i = 1; i < n; i++) {
		scanf("%d", &t[1][i]);
	}
	assembly();
}