#include <stdio.h>
#include<string.h>
#include<stdlib.h>

struct management
{
	char name[30];
	char phone_num[30];
	int Id;
	struct management *link;
};

typedef struct management User;

void Insert(User*);
void Delete(User*);
void Display(User*);
void Search(User*);
int CustomId = 0;

int main(void) {
	User *ptr;
	int choice;
	ptr = (User*)malloc(sizeof(User));
	ptr->link = NULL;
	strcpy(ptr->name, "");
	strcpy(ptr->phone_num, "");
	ptr->Id = NULL;

	//화면 실행
	while (1) {
		printf("Hello VideoWorld\n");
		printf("//This is our coustomer management program\n\n");
		printf("=========+ MENU +==========\n");
		printf("     1. Insert User \n");
		printf("     2. Delete User \n");
		printf("     3. Search User \n");
		printf("===========================\n\n");
		printf(" >> Select Number: \n");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			Insert(ptr);
			break;
		case 2:
			Delete(ptr);
			break;
		case 3:
			Search(ptr);
			break;
		default:
			break;
		}
	}
}

//사용자 추가(입력)
void Insert(User *ptr) {

	while (ptr->link != NULL)
		ptr = ptr->link;
	ptr->link = (User*)malloc(sizeof(User));
	ptr = ptr->link;
	//입력
	printf("=====+ Insert User +=====\n");
	printf("Input Name : \n");
	scanf("%s", ptr->name);
	printf("Input Phone :\n");
	scanf("%s", ptr->phone_num);
	ptr->Id = ++CustomId;
	//출력
	printf("(Name : %s / Phone Number : %s / Id : %d)", ptr->name,ptr->phone_num,ptr->Id);
	printf("\n\n");
	ptr->link = NULL;
}

// 사용자 제거
void Delete(User *ptr) {
	User *prev;
	char name[30];
	char phone[30];
	int Id;
	int num;
	printf("======+ Delete User +=====\n");
	printf("     1. Name \n");
	printf("     2. Phone Number \n");
	printf("     3. Id\n");
	printf("=========================\n");
	printf(" Select number: ");
	scanf("%d", &num);
	printf("\n\n");

	// 이름,아이디, 고유번호 중 하나 선택해서 지우기
	switch (num)
	{
	case(1):
		printf("Input the delete name : \n");
		scanf("%s", name);
		while (ptr->link != NULL) {
			prev = ptr;
			ptr = ptr->link;
			if (strcmp(name, ptr->name) == 0) {
				prev->link = ptr->link;
				free(ptr);
			}
			ptr = prev;
		}
		break;
	case(2):
		printf("Input Phone Number :\n");
		scanf("%s", phone);
		while (ptr->link != NULL) {
			prev = ptr;
			ptr = ptr->link;
			if (strcmp(phone, ptr->phone_num) == 0) {
				prev->link = ptr->link;
				free(ptr);
				break;
			}
		}
		break;
		case 3:
	 	printf("Input Id :\n");
		scanf("%d", &Id);
		while (ptr->link != NULL) {
			prev = ptr;
			ptr = ptr->link;
			if (Id == ptr->Id) {
				prev->link = ptr->link;
				free(ptr);
				break;
			}
		}
		break;
	}
}

//전체검색, 항목검색
void Search(User *ptr) {
	char name[30];
	char phone[30];
	int Id;
	int num;
	int num2;
	printf("=====+ Search +=====\n");
	printf("  1. Entire Search\n");
	printf("  2. Part Search\n");
	printf("====================\n");
	printf(" select the number\n");
	scanf("%d", &num2);
	switch (num2) {
	//전체 검색
	case(1):
		printf("=====+ Entire Search +=====\n\n");
		if (ptr->link == NULL)
			printf("No user\n\n");
		else
			while (ptr->link != NULL) {
				ptr = ptr->link;
				printf("(Name : %s / Phone Number : %s / Id : %d)\n", ptr->name, ptr->phone_num, ptr->Id);
			}
		break;

	//부분 검색
	case (2):
		printf("=====+ Part Search +=====\n");
		printf("1. Name\n");
		printf("2. Phone Number\n");
		printf("3. Id\n");
		printf("====================\n");
		printf("Select Number :\n");
		scanf("%d", &num);
		switch (num)
		{
		case(1):
			printf("Input name :\n");
			scanf("%s", name);
			while (ptr->link != NULL) {
				ptr = ptr->link;
				if (strcmp(name, ptr->name) == 0) {
					printf("(Name : %s / Phone Number : %s / Id : %d)\n\n", ptr->name, ptr->phone_num, ptr->Id);
				}
			}
			break;
		case(2):
			printf("Input Phone Number :\n");
			scanf("%s", phone);
			while (ptr->link != NULL) {
				ptr = ptr->link;
				if (strcmp(phone, ptr->phone_num) == 0) {
					printf("(Name : %s / Phone Number : %s / Id : %d)\n\n", ptr->name, ptr->phone_num, ptr->Id);
					break;
				}
			}
			break;

		case (3):
			printf("Input Id :\n");
			scanf("%d", &Id);
			while (ptr->link != NULL) {
				ptr = ptr->link;
				if (Id == ptr->Id) {
					printf("(Name : %s / Phone Number : %s / Id : %d)\n\n", ptr->name, ptr->phone_num, ptr->Id);
					break;
				}
			}
			break;
		}
		break;
	}
}