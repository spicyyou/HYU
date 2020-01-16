#include<stdio.h>
#define INF 987654321
#define LIM 200001
int dist[LIM];
int visit[LIM];
int v, e;
int node[1005][1005];

int dijkstra(int start, int end) {
	dist[start] = 0;
	int t;
	int min_v = 0;
	for (t = 1; t <= v; t++) {
		int min = INF;
		int i;
		for (i = 1; i <= v; i++) {
			if (visit[i] == 0 && min > dist[i]) {
				min = dist[i];
				min_v = i;
			}
		}
		visit[min_v] = 1;
		int j;
		for (j = 1; j <= v; j++) {
			if (dist[j] > dist[min_v] + node[min_v][j]) {
				dist[j] = dist[min_v] + node[min_v][j];
			}
		}
	}
	return dist[end];
}

int main() {
	scanf("%d%d", &v, &e); 
	int i,j;
	for (i = 1; i <= v; i++) {
		for (j = 1; j <= v; j++) {
			node[i][j] = INF;
		}
	}
	for (i = 1; i <= v; i++) {
		dist[i] = INF;
	}
	for ( i = 1; i <= e; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		if (node[u][v] > w) { node[u][v] = w; }
	}
	int a, b;
	scanf("%d%d", &a, &b);
	printf("%d\n",dijkstra(a, b));
}