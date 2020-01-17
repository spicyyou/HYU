//2017030519_홍유진_Algorithm
#include<stdio.h>
#include<iostream>
#include<math.h>
#include<utility>
#include<vector>
#include<string.h>
#include<string>
#include<stdlib.h>
#include<queue>
#include<cmath>
using namespace std;

#define ALPHABET 26 
#define MAX_LEN 60000
#define MAX_ELEMENT 60000
#define logB(x, base) log(x)/log(base)

typedef struct {
	int alpha; // 알파벳 저장을 위한 배열 
	int freq; // 빈도수 저장을 위한 배열 
}AlphaType;

typedef struct TreeNode {
	AlphaType weight;
	TreeNode *left_child;
	TreeNode *right_child;
}TreeNode;

typedef struct {
	TreeNode *pTree;
	int key;
}Element;

typedef struct {
	Element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;


void InsertHeap(HeapType *h, Element item)
{
	int i;
	i = ++(h->heap_size);

	while (i != 1 && item.key < h->heap[i / 2].key) // 부모노드와 비교 
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}

	h->heap[i] = item;
}

Element DeleteHeap(HeapType *h)
{
	int parent = 1, child = 2;
	Element data, temp;

	data = h->heap[parent];
	temp = h->heap[(h->heap_size)--]; // 삭제에 의한 size 감소 

	while (child <= h->heap_size)
	{
		//자식 노드간 작은 수 비교  
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
			child++;

		if (temp.key <= h->heap[child].key) break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2; // 다음 자식 노드와 비교 
	}

	h->heap[parent] = temp;
	return data;
}

TreeNode* MakeNode(TreeNode *left, TreeNode *right) // 노드 생성 
{
	TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));

	if (node == NULL)
	{
		printf("메모리 할당 에러\n");
		exit(-1);
	}

	node->left_child = left;
	node->right_child = right;

	return node;
}
int res;
void PrintTree(TreeNode *p, int i, char *pCode)
{
	if (p)
	{
		i++;
		pCode[i] = '1';
		PrintTree(p->left_child, i, pCode);
		pCode[i] = '0';
		PrintTree(p->right_child, i, pCode);
		pCode[i] = '\0';

		if (p->left_child == NULL && p->right_child == NULL)
		{
			int sum = strlen(pCode);
			res += sum*p->weight.freq;
		}
	}
}

int DestroyTree(TreeNode *p)
{
	if (p == NULL) return -1;

	DestroyTree(p->left_child);
	DestroyTree(p->right_child);

	free(p);

	return 1;
}

void HuffmanTree(AlphaType *pArr, int n)
{
	TreeNode *node, *temp;
	Element e, e1, e2;
	HeapType heap;
	char binaryCode[100];
	int i;

	heap.heap_size = 0;

	for (i = 0; i<n; i++)
	{
		node = MakeNode(NULL, NULL);
		node->weight.alpha = pArr[i].alpha;
		e.key = node->weight.freq = pArr[i].freq;
		e.pTree = node;
		InsertHeap(&heap, e); // 생성한 노드를 힙에 삽입 
	}

	for (i = 0; i<n - 1; i++) // n-1까지 반복, 마지막 남은 노드가 루트 
	{
		e1 = DeleteHeap(&heap); // 최소값을 가지는 노드 2개를 빼낸다 
		e2 = DeleteHeap(&heap);

		temp = MakeNode(e1.pTree, e2.pTree); // 2개의 노드를 가지는 노드 생성 

		e.key = temp->weight.freq = e1.key + e2.key; // 2개의 노드 값을 더한다 
		e.pTree = temp; // 위에서 만든 노드를 대입 

		InsertHeap(&heap, e); // 트리로 구성된 노드를 힙에 삽입 
	}
	e = DeleteHeap(&heap); // 여기서 꺼낸 데이터는 완성된 트리 

	PrintTree(e.pTree, -1, binaryCode); // 허프만 코드 출력 

	DestroyTree(e.pTree); // 메모리 반환 

}


char str[5];
int main()
{
	AlphaType *copyData; // 존재하는 문자열의 갯수 저장을 위한 변수 


	int input;
	scanf("%d", &input);
	copyData = (AlphaType*)malloc(sizeof(AlphaType)*input);
	for (int i = 0; i < input; i++) {
		int n;
		scanf("%s", &str);
		scanf("%d", &n);
		copyData[i].alpha = str[0];
		copyData[i].freq = n;
	}
	int s;
	scanf("%d", &s);

	HuffmanTree(copyData, input);

	int fixed = ceil(logB(input, 2))  * s;
	printf("%d\n", fixed);
	printf("%d\n", res);
	free(copyData);

	return 0;
}