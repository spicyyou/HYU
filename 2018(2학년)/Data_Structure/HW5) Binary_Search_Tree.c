#include<stdio.h>
#include<stdlib.h>

typedef struct node* Node;
typedef struct node* Tree;
typedef struct node {
	int value;
	Node parent;
	Node leftChild;
	Node rightChild;
}node;

Tree createTree();
int isEmpty(Tree t);
Node search(Tree t, int key);
Node deleteNode(Tree t, int key);
void insertNode(Tree t, int key);
void showAll(Tree t);
int getHeight(Tree t, int key);
Node findMaxNode(Node Tree);

Tree createTree() {
	Tree tmp = (Tree)malloc(sizeof(struct node));
	tmp->value = 0;
	tmp->leftChild = NULL;
	tmp->rightChild = NULL;
	tmp->parent = NULL;
	return tmp;
}

int isEmpty(Tree t) {
	if (t->rightChild == NULL) {
		return 1;
	}
	return 0;
}

Node search(Tree t, int key)
{
	if (!t) return NULL;
	if (key == t->value) { return t; }
	if (key < t->value) { return search(t->leftChild, key); }
	return search(t->rightChild, key);
}

Node findMaxNode(Node Tree)
{
	if (Tree == NULL) return NULL;
	else {
		while (Tree->rightChild != NULL) { Tree = Tree->rightChild; }
	}
	return Tree;
	/*if (Tree->leftChild != NULL) return findMinNode(Tree->leftChild);
	else return Tree;*/
}


void insertNode(Tree t, int key) {
	Node parent = { 0 };
	Node tmp;
	int dif = 0;
	if (isEmpty(t)) {
		tmp = createTree();
		tmp->value = key;
		tmp->parent = t;
		t->rightChild = tmp;
		return;
	}
	else {
		while (t) {
			if (key == t->value) { break; }
			parent = t;
			if (t->value < key) {
				t = parent->rightChild;
				dif = 1;
			}
			else if (t->value > key) {
				t = parent->leftChild;
				dif = 0;
			}
		}
		//새로 삽입될 노드
		t = createTree();
		t->value = key;
		t->parent = parent;
		if (dif == 1) {
			parent->rightChild = t;
		}
		else {
			parent->leftChild = t;
		}
		return;
	}
	/*if (isEmpty(t)) {
	t =(Tree) malloc(sizeof(struct node));
	if (!isEmpty(t)) {
	t->value = key;
	t->leftChild = t->rightChild = NULL;
	}
	}
	else if (key < t->value) {
	t->leftChild = insertNode(t->leftChild, key);
	}
	else if (key>t->value) {
	t->rightChild = insertNode(key, t->rightChild);
	}
	return t;*/
}
Node deleteNode(Tree t, int key) {
	//t = search(t, key);
	int dif = 0;
	/*if (t == NULL) {
	printf("Not Found\n");
	return t;
	}
	/*if (del->parent->leftChild == del) {
	dif = 0;
	}
	else {
	dif = 1;
	}*/
	Node tmp;
	int value = 0;
	if (t == NULL) {
		printf("Not Found\n");
		return t;
	}
	else if (key < t->value) {
		t->leftChild = deleteNode(t->leftChild, key);
	}
	else if (key > t->value) {
		t->rightChild = deleteNode(t->rightChild, key);
	}
	else if (t->leftChild&&t->rightChild) {
		tmp = findMaxNode(t->leftChild);
		t->value = tmp->value;
		t->leftChild = deleteNode(t->leftChild, t->value);
	}
	else {
		tmp = t;
		if (t->leftChild == NULL) {
			t = t->rightChild;
		}
		else if (t->rightChild == NULL) {
			t = t->leftChild;
		}
		free(tmp);
	}
	return t;
}

void showAll(Tree t) {
	if (t) {
		showAll(t->leftChild);
		if (t->value != 0) {
			printf("%d ", t->value);
		}
		showAll(t->rightChild);
	}
}
int cnt;
Node height;
int getHeight(Tree t, int key)
{
	int dep0, depl, depr;
	if (cnt == 0) {
		height = search(t, key);
		if (height == NULL) {
			printf("Not Found\n");
			return -1;
		}
		cnt++;
		if (height == NULL) {
			dep0 = 0;
		}
		else {
			depl = getHeight(height->leftChild, key);
			depr = getHeight(height->rightChild, key);
			if (depl >= depr) {
				dep0 = depl + 1;
			}
			else {
				dep0 = depr + 1;
			}
		}
	}
	else {
		if (t == NULL) {
			dep0 = 0;
		}
		else {
			depl = getHeight(t->leftChild, key);
			depr = getHeight(t->rightChild, key);
			if (depl >= depr) {
				dep0 = depl + 1;
			}
			else {
				dep0 = depr + 1;
			}
		}

	}
	return dep0;
	/*if (!t) return 0;
	else {
	int left_h = getHeight(height->leftChild, key);
	int right_h = getHeight(height->rightChild, key);
	return 1 + (left_h > right_h ? left_h : right_h);
	}*/
}


int main() {
	Tree tree = createTree();
	char input;
	scanf("%c", &input);
	while (1) {
		int n;
		switch (input) {
		case 'i': {
			scanf("%d", &n);
			insertNode(tree, n);
			break;
		}
		case 'h': {
			scanf("%d", &n);
			int h = getHeight(tree, n);
			if (h != -1) {
				printf("The height of the node (%d) is %d\n", n, h - 1);
			}
			cnt = 0;
			break;
		}
		case 'd': {
			scanf("%d", &n);
			deleteNode(tree, n);
			break;
		}
		case 's': {
			showAll(tree);
			printf("\n");
			break;
		}
		case 'e': {
			return 0;
		}
		}
		getchar();
		scanf("%c", &input);
	}
}