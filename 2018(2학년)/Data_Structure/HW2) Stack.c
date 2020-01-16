#include<stdio.h>
#include<stdlib.h>

typedef struct stack *Stack;
char arr[150];
int cnt;
struct stack {
	char * array;
	int size;
	int top;
};
Stack S;
Stack createStack(int arraySize) {
	S = (Stack)malloc(sizeof(struct stack));
	S->size = arraySize;
	S->top = -1;
	S->array = (char*)malloc(sizeof(char)*arraySize);
	return S;
}

Stack makeEmptyStack(Stack S) {
	int num = 0;
	while (num <S->size) {
		S->array[num] = NULL;
		arr[num] = NULL;
		num++;
	}
	return S;
}
//����ֳ� check
int isEmpty(Stack S) {
	if (S->top == -1) return 1;
	else return 0;

}
void push(char X, Stack S) {

	if (S->top > S->size) {
		printf("���� ����\n");
		return;
	}

	S->array[++S->top] = X;
	//ä���

}
char pop(Stack S) {
	if (isEmpty(S)) {
		printf("���ÿ� �ƹ� �͵� ����\n");
		return NULL;
	}
	else {
		S->array[S->top--] = NULL;
		return NULL;
	}
	return NULL;
}

void deletestack(Stack S){
	free(S);
	return;
}

int main(void) {
	int temp=0;
	int cnt = 0;
	int ch = 0;
	int isOkay = 0, is = 0;
	while (1) {
		char c;
		scanf("%c", &c);
		if (temp == 0) {
			createStack(150);
			makeEmptyStack(S);
		}
		if (c == ' ') continue;
		if (c == '!'&&ch != 1) { return 0; }
		else if (c == '('&&ch != 1) {
			//)�� �Էµɶ����� ���ÿ� �ִ´�.
			isOkay = 1;
			push(c, S);
		}
		else if (isEmpty(S) == 1 && c == ')'&&ch != 1)
		{
			is = 1;
			ch = 1;
			//#�������� �� ���� //����� ��� �ؾ��ϴ��� ���� ????
		}
		else if (c == ')'&&ch != 1) {
			while (1) {
				if (S->array[S->top] == '(') {
					pop(S);
					break;
				}
				else {
					arr[cnt++] = S->array[S->top];
					pop(S);
				}
			}
			//( �� pop�ɶ����� ��� pop�ؼ� ��� ���ڿ��� ����
		}
		else if (c == '#') {
			int i = 0;
			if (isEmpty(S) == 1&&ch!=1) {
				printf("right. ");
			}
			else {
				printf("wrong. ");
			}
			i = 0;
			while (1) {
				printf("%c ", arr[i]);
				i++;
				if (i == cnt) {
					break;
				}
			}
		}
		else {
			if (isEmpty(S) == 0 && ch != 1) {
				push(c, S);
			}
			else if (isEmpty(S) == 1&&ch!=1) {
				arr[cnt++] = c;
			}
		}
		if (c == '\n') {
			makeEmptyStack(S);
			deletestack(S);
			createStack(150);
			makeEmptyStack(S);
			cnt = 0; ch = 0; isOkay = 0, is = 0;
			printf("\n");
		}
		temp++;
	}
	return 0;
}