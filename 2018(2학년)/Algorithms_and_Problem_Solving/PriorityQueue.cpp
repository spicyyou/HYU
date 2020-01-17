//2017030519_홍유진_Algorithm
#include<stdio.h>
int heap[200000];
int heap2[200000];
int n = 0;
void insert_max_heap(int item)
{
	int i;
	i = ++n;
	while ((i != 1) && item >= heap[i / 2])
	{
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

int delete_max_heap()
{
	int item, temp;
	item = heap[1];
	temp = heap[n--];
	int parent = 1, child = 2;
	while (child <= n)
	{
		if ((child + 1 <= n) && heap[child] <= heap[child + 1])
		{
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

void heapify(int idx)
{
	if (heap[idx] > heap[idx / 2] && idx != 1)
	{
		//int temp = heap[idx];
		while (heap[idx] >= heap[idx / 2] && idx != 1)
		{
			int tmp = heap[idx / 2];
			heap[idx / 2] = heap[idx];
			heap[idx] = tmp;
			idx /= 2;
		}
	}
	else
	{
		int parent = idx;
		int child = idx * 2;
		while (child <= n)
		{
			if ((child + 1 <= n) && heap[child] <= heap[child + 1])
			{
				child++;
			}
			/*
			만일 내가( 현 parent 인 heap[idx] 가 child의 키보다 더 크면 바뀌면 안됨)
			//if (temp > heap[child]) break;
			int tmp = heap[parent];
			heap[parent] = heap[child];
			heap[child] = tmp;
			parent = child;
			child *= 2;
			밑에 코드가 내가 코드 수정한거
			*/
			if (heap[parent] > heap[child])
				break;
			else
			{
				int tmp = heap[parent];
				heap[parent] = heap[child];
				heap[child] = tmp;
				parent = child;
				child *= 2;
			}

		}
	}
}
/*void max_heapify(int idx) {
int l = idx * 2;
int r = idx * 2 + 1;
int largest = idx;
int tmp = 0;
if (l <= n&&heap[l]>heap[largest]) {
largest = l;
}
if (r <= n&&heap[r] >= heap[largest]) {
largest = r;
}
if (largest != idx) {
tmp = heap[largest];
heap[largest] = heap[idx];
heap[idx] = tmp;
max_heapify(largest);

}
}
void build_max_heap() {
int heap_size = n;
for (int i = n / 2; i > 0; i--) {
max_heapify(i);
}
}
void heap_sort() {
int tmp = 0;
build_max_heap();
}*/
int main()
{
	int i = 0, k = 0;
	while (1)
	{
		int a;
		scanf("%d", &a);
		switch (a)
		{
		case 0:
		{
			//출력하고
			//heap_sort();
			for (int j = 0; j < k; j++)
			{
				printf("%d ", heap2[j]);
			}
			printf("\n");
			for (int j = 1; j <= n; j++)
			{
				printf("%d ", heap[j]);
			}
			return 0;
		}
		case 1:
		{
			//++n;
			int input;
			scanf("%d", &input);
			insert_max_heap(input);
			//heap_sort();
			break;
		}
		case 2:
		{
			//heap_sort();
			heap2[k++] = delete_max_heap();
			break;
		}
		case 3:
		{
			int b, c;
			scanf("%d%d", &b, &c);
			heap[b] = c;
			heapify(b);
			break;
		}
		}
	}
}