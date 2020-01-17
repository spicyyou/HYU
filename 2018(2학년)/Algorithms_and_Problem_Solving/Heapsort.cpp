//2017030519_È«À¯Áø_Algorithm
#include<stdio.h>
int heap[100005];
int heap2[100005];
int n = 0;

void insert_max_heap(int item) {
	int i;
	i = ++n;
	while ((i != 1) && item >= heap[i / 2]) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

int delete_max_heap() {
	int item, temp;
	item = heap[1];
	temp = heap[n--];
	int parent = 1, child = 2;
	while (child <= n) {
		if ((child <= n) && heap[child] <= heap[child + 1]) {
			child++;
		}
		if (temp> heap[child]) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) {
		int a;
		scanf("%d", &a);
		insert_max_heap(a);
	}
	for (int i = 0; i < k; i++) {
		printf("%d ",delete_max_heap());
	}
	printf("\n");
	for (int i = 0; i < n - k; i++) {
		printf("%d ", delete_max_heap());
	}
}


void heapify_buttom_up(int* arr, int length) {

	int end = length - 1;
	int current = get_parent(end);

	while (current >= 0) {
		sift_down(arr, current--, end);
	}
}
