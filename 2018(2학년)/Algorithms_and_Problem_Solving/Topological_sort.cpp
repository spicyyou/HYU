//2017030519_È«À¯Áø_A
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<stack>
#include<vector>
#include<string.h>
using namespace std;

vector<int> adj[32005];
int visit[32005];
vector<int> vec;
int visited[32005];
bool findCycleAlgorithm(int here) {
	if (visited[here]) {
		if (visited[here] == -1) {
			return true;
		}
		return false;
	}

	visited[here] = -1;
	int there;
	for (int i = 0; i < adj[here].size(); i++) {
		there = adj[here][i];
		if (findCycleAlgorithm(there)) {
			return true;
		}
	}
	visited[here] = 1;

	return false;
}

int dfs(int now) {
	visit[now] = 1;
	for (int i = 0; i < adj[now].size(); i++) {
		int togo = adj[now][i];
		if (visit[togo] == 0) {
			dfs(togo);
		}
		else if (visit[togo] == 1) {
			return 2;
		}
	}
	vec.push_back(now);
	visit[now] = 2;
	return 0;
}
int main() {
	int n;
	scanf("%d", &n);
	int a, b;

	while (scanf("%d", &a) != EOF) {
		scanf("%d", &b);
		adj[a].push_back(b);
	}
	for (int i = 0; i <= n; i++) {
		sort(adj[i].begin(), adj[i].end());
	}

	if (!findCycleAlgorithm(1)) {
		for (int i = 1; i <= n; i++) {
			if (visit[i] == 0) {
				int a = dfs(i);
			}
		}
		printf("1\n");
		for (int i = vec.size() - 1; i >= 0; i--) {
			printf("%d ", vec[i]);
		}
	}
	else { printf("0\n"); }
}

/*9
1 5
1 4
2 5
4 6
4 5
6 9
7 6
7 8
8 9
*/