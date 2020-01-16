#include<stdio.h>
#define MAX_QUEUE_SIZE 10000
/*typedef struct {
	int key;

}element;*/
int queue[MAX_QUEUE_SIZE];

int rear = -1;
int front = -1;
int n;//나중에 확인하고 바꾸기
int visit[1005]; int visit2[1005];
int matrix[1005][1005];


void Enqueue(int item) {
	if (rear == MAX_QUEUE_SIZE - 1) {
	}
	queue[++rear] = item;
}

int Dequeue() {
	return queue[++front];
}
void dfs(int now) {
	int j;
	visit[now] = 1;
	printf("%d ", now);
	for (j = 1; j <= n; j++) {
		int next = j;
		if (matrix[now][next] == 1) {
			if (visit[next] != 1) {
				visit[next] = 1;
				dfs(next);
			}
		}
	}
}


void bfs(int start) {
	Enqueue(start);
	visit2[start] = 1;
	while (1) {
		if (front == rear) { break; }
		int now = Dequeue();
		printf("%d ", now);
		int j;
		for (j = 1; j <= n; j++) {
			int next = j;
			if (matrix[now][next]==1) {
				if (visit2[next] != 1) {
					visit2[next] = 1;
					Enqueue(next);
				}
			}
		}
	}
}

int main() {

	scanf("%d", &n);
	int e, start,i;
	scanf("%d%d", &e, &start);
	for (i=0; i < e; i++) {
		int row, col;
		scanf("%d%d", &row, &col);
		matrix[row][col] = matrix[col][row] = 1;
	}
	dfs(start);
	printf("\n");
	bfs(start);
	printf("\n");
}