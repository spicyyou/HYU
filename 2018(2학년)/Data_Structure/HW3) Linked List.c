#include<stdio.h>
#include<stdlib.h>
typedef struct node * pNode;
typedef pNode List;
typedef pNode Node;

struct node{
	int value;
	Node next;
} typedef node;

List makeEmptyList(List L) {
	L->value = NULL;
	L->next = NULL;
	return L;
}

void insert(int v, List L, Node N) {
	N = NULL;
	N = (Node)malloc(sizeof(node));
	N->next = L->next;
	N->value = v;

	L->next = N;
}


Node findPrev(int v, List L)
{
	while (L->next!= NULL) {
		if (L->next->value == v) {
			return L;
		}
		L = L->next;
	}
	return (Node)-1;
}
Node find(int v, List L) {
	int isOkay = 0;
	while (L!= NULL) {
		if (L->value == v) {
			isOkay = 1;
			return L;
		}
		L = L->next;
	}

	if (isOkay == 0) {
		//printf("Find error. The %d isn't in the list.", v);
		return (Node)-1;
	}
}

void delete_(int v, List L) {
	int isOkay = 0;
	Node dummy;
	if (findPrev(v, L) != (Node)-1) {
		L = findPrev(v, L);
		dummy = L->next;
		L->next = dummy->next;
		free(dummy);
	}
	else
		printf("Delete error. The %d isn't in the list.\n", v);
	return;
}
void deleteList(List L) {
	Node dummy;
	while (L != NULL) {
		dummy = L;
		L = L->next;
		free(dummy);
	}
	free(L);
	return ;
}
void showlist(List L) {
	L = L->next;
	while (L!= NULL) {
		printf("%d ", L->value);
		L = L->next;
	}
	printf("\n");
	return ;
}


int main() {
	List LL = (List)malloc(sizeof(node));
	makeEmptyList(LL);	
	Node NN = (Node)malloc(sizeof(node));
	while (1) {
		char c;
		scanf("%c", &c);
		switch (c) {
		case 'e':
		{
			deleteList(LL);
			return 0;
		}
		case 's':
		{
			showlist(LL);
			break;
		}
		case 'f':
		{
			int a;
			scanf("%d", &a);
			if (find(a, LL) == (Node)-1) {
				printf("Find error. The %d isn't in the list.\n", a);
				break;
			}
			else if (find(a, LL) != (Node)-1 && LL==findPrev(a, LL) ) {
				printf("The %d is next of The header.\n", a);
				break;
			}
			else if (find(a, LL) != (Node)-1 && findPrev(a, LL) != (Node)-1) {
				printf("The %d is next of The %d.\n", a, findPrev(a, LL)->value);
				break;
			}
			break;
		}
		case 'd': {
			int a;
			scanf("%d", &a);
			delete_(a, LL);
			break;
		}
		case 'i': 
		{
			int a, b;
			scanf("%d%d", &a, &b);
			if (b == 0) {
				insert(a, LL, NN);
			}
			else {
				if (find(b, LL) == (Node)-1) {
					printf("Insert error. The %d isn't in the list.\n", b);
					break;
				}
				insert(a, find(b, LL), NN);
			}
			break;
		}
		}
		getchar();
		}
}