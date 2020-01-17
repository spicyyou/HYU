//2017030519_È«À¯Áø_A
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<stack>
#include<vector>
#include<string.h>
using namespace std;

vector<int> adj[1005];
int visit[1005];
int cnt = 0;
int num[1005];
int dfs(int now, int count) {
	visit[now] = 1;
	for (int i = 0; i < adj[now].size(); i++) {
		int togo = adj[now][i];
		if (visit[togo] == 0) {
			num[togo] = count;
			dfs(togo, count);
		}
	}
	return 0;
}


int main() {
	int n;
	scanf("%d", &n);
	int x, y;
	while (scanf("%d", &x) != EOF) {
		scanf("%d", &y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	for (int i = 1; i <= n; i++) {
		if (visit[i] != 1) {
			cnt++;
			num[i] = cnt;
		}
		dfs(i, cnt);
	}
	printf("%d\n", cnt);
	for (int i = 1; i <= n; i++) {
		printf("%d\n", num[i]);
	}
}