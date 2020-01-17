//2017030519_È«À¯Áø_A
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<stack>
#include<vector>
#include<string.h>
#include<queue>
using namespace std;

#define INF 987654300
int dis[200005];
vector<int> adj[500];
vector<pair<int, int> > graph[200005];

int main() {
	int v;
	scanf("%d", &v);
	for (int i = 0; i < v; i++) {
		int v_idx, e_num;
		scanf("%d%d", &v_idx, &e_num);
		for (int i = 0; i < e_num ; i++) {
			int b, a_to_b_weight;//b=destination
			scanf("%d%d", &b, &a_to_b_weight);
			graph[v_idx].push_back({ b,a_to_b_weight });
		}
	}
	for (int i = 1; i <= v; i++) {
		dis[i] = INF;
	}

	priority_queue<pair<int, int> > pq;
	dis[1] = 0;
	pq.push(make_pair(-0, 1));
	while (!pq.empty()) {
		int myDis = -pq.top().first;
		int now = pq.top().second;
		pq.pop();
		for (int i = 0; i < graph[now].size(); i++) {
			int toGo = graph[now][i].first;
			int toDis = myDis + graph[now][i].second;
			if (dis[toGo] > toDis) {
				dis[toGo] = toDis;
				pq.push({ -toDis,toGo });
			}
		}
	}

	int max = 0;
	for (int i = 1; i <= v; i++) {
		if (max < dis[i]&&dis[i]!=INF) {
			max = dis[i];
		}
	}

	printf("%d\n", max);
}

/*5
1 2
2 10 3 5
2 2
4 1 3 2
3 3
2 3 4 9 5 2
4 1
5 4
5 2
1 7 3 6*/