#define MAX_ELEMENTS 100000
#define HEAP_FULL(n) (n==MAX_ELEMENTS-1)
#define HEAP_EMPTY(n)(!n)
#define SWAP(x,y,t) {t=x,x=y,y=t ;}
#include <math.h>
#include<stdio.h>
typedef struct {
	int key;
} element;
element heap[MAX_ELEMENTS];
int n = 0;

void insert_min_heap(element item) {
	int i;//insert될 위치찾아줄 변수
	if (HEAP_FULL(n)) {
		//바꾸기
	}
	i = ++(n);
	while ((i != 1) && (abs(item.key) <= abs(heap[i/2].key))) {
		if ((abs(item.key) == abs(heap[i / 2].key))) {
			if (item.key < heap[i / 2].key) {
				heap[i] = heap[i / 2];
				i /= 2;
			}
			else if (item.key == heap[i / 2].key) {
				heap[i] = heap[i / 2];
				i /= 2;
			}
			else {
				break;
			}
		}
		else {
			heap[i] = heap[i / 2];
			i /= 2;
		}
	}
	heap[i] = item;
}
element delete_min_heap() {
	element item, temp;
	if (HEAP_EMPTY(n)) {
		temp.key = 0;
		return temp;
	}
	item = heap[1];
	temp = heap[(n)--];
	int parent = 1, child = 2;
	while (child <= n) {
		if ((child <= n) && (abs(heap[child].key) >= abs(heap[child + 1].key))) {
			if (abs(heap[child].key) == abs(heap[child + 1].key)) {
				if (heap[child].key > heap[child + 1].key) {
					child++;
				}
			}
			else {
				child++;
			}
		}
		if (abs(temp.key) < abs(heap[child].key)) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}

int main(){
	int q;
	scanf("%d", &q);
	element main;
	for (int i = 0; i < q; i++) {
		int a;
		scanf("%d", &a);
		main.key = a;
		if (a != 0) {
			insert_min_heap(main);
		}
		else {
			int a = delete_min_heap().key;
			printf("%d\n", a);
		}
	}

}