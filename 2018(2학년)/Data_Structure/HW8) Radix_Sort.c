#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX_ELEMENTS 100000
#define HEAP_FULL(n) (n==MAX_ELEMETS-1)
#define HEAP_EMPTY(n)(!n)
#define SWAP(n,m,t)(t=n,n=m,m=t)
typedef struct {
	char name[100];
	int korean;
	int english;
	int math;
}student;

student heap[MAX_ELEMENTS];
int n = 0;

int studentComp(student stu1, student stu2);
void adjust(int root, int n);
void mHeapsort();



int main() {
	int num = 0;
	int i = 0;
	int tempKor, tempEng, tempMath;
	char tempName[100];
	scanf("%d", &num);
	for (i = 0; i < num; i++) {
		//입력된 이름 및 점수를 Heap 구조체에 저장
		++n;
		scanf("%s", tempName);
		scanf("%d%d%d", &tempKor, &tempEng, &tempMath);
		student temp = { "",tempKor,tempEng,tempMath };
		heap[n] = temp;
		strcpy(heap[n].name, tempName);
	}
	mHeapsort();
	for (i = n; i > 0; i--) {
		printf("%s\n", heap[i].name);
	}
	//system("pause");
	return 0;
}
void mHeapsort() {
	int i;
	student temp;
	for (i = n / 2; i > 0; i--) {
		adjust(i, n);
	}
	for (i = n - 1; i > 0; i--) {
		temp = heap[i + 1];
		heap[i + 1] = heap[1];
		heap[1] = temp;
		adjust(1, i);
	}
}
void adjust(int root, int n) {
	int child;
	student rootStu;
	rootStu = heap[root];
	child = 2 * root;
	while (child <= n) {
		if ((child < n) && (studentComp(heap[child], heap[child + 1]) > 0)) {
			child++;
			//child+1 priority is high
		}
		if (studentComp(rootStu, heap[child]) < 0) {
			//rootStu priority is high
			break;
		}
		else {
			heap[child / 2] = heap[child];
			child *= 2;
		}
	}
	heap[child / 2] = rootStu;
}
int studentComp(student stu1, student stu2) {
	if (stu1.korean != stu2.korean) {
		return (stu1.korean>stu2.korean ? -1 : 1);
		//국어점수가 높은 학생이 누구인지 판별하여 return 값으로 알려줌
	}
	else {//same Korean score
		if (stu1.english != stu2.english) {
			return (stu1.english<stu2.english ? -1 : 1);
			//영어점수가 낮은 학생이 누구인지 판별하여 return 값으로 알려줌
		}
		else {//smae Korean score
			if (stu1.math != stu2.math) {
				return(stu1.math>stu2.math ? -1 : 1);
			}
			else {//same math
				return strcmp(stu1.name, stu2.name);
			}
		}
	}
}