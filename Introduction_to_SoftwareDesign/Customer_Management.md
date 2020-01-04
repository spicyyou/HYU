# Customer Management Progam

## 과제설명

서울 시내 한 비디오 대여점의 고객 관리 프로그램을 아래의 Requirement 에 맞춰 C언어로 작성

### Requirement

1. 메뉴 화면 구성
  a. 사용자 추가
  b. 사용자 제거
  c. 사용자 검색
2. 사용자 추가 화면
  a. 이름
  b. 전화번호
  c. 자동으로 사용자 고유 아이디 부여 (입력받는 항목이 아님)
  d. 추가 완료 후, 사용자 정보 모두 출력
  e. 추가후, 메인 메뉴로 진입
3. 사용자 제거
  a. 이름, 전화번호, 고유 아이디중 하나를 입력받아 제거
  b. 제거후, 메인 메뉴로 진입
4. 사용자 검색
  a. 전체검색 / 항목검색으로 구분
  b. 항목 검색시 검색할 항목을 선택 후, 문자열을 입력받아 검색
  c. 이름, 전화번호, 고유 아이디 출력
  d. 출력후, 메인 메뉴로 진입




## 코드 설명

### Insert

사용자 추가

```c
//입력
	printf("=====+ Insert User +=====\n");
	printf("Input Name : \n");
	scanf("%s", ptr->name);
	printf("Input Phone :\n");
	scanf("%s", ptr->phone_num);
	ptr->Id = ++CustomId;
```

```c++
//출력
	printf("(Name : %s / Phone Number : %s / Id : %d)", ptr->name,ptr->phone_num,ptr->Id);
	printf("\n\n");
```

### Delete

: 사용자 제거

- switch를 통해 name, id, phone_num을 통해 삭제

```c
while (ptr->link != NULL) {
			prev = ptr;
			ptr = ptr->link;
			if (strcmp(phone, ptr->phone_num) == 0) {//phone대신 name, id를 통해서도 삭제가능
				prev->link = ptr->link;
				free(ptr);
				break;
			}
		}
```



### Search

: 사용자 검색

- 전체검색

```c
printf("=====+ Entire Search +=====\n\n");
		if (ptr->link == NULL)
			printf("No user\n\n");
		else
			while (ptr->link != NULL) {
				ptr = ptr->link;
				printf("(Name : %s / Phone Number : %s / Id : %d)\n", ptr->name, ptr->phone_num, ptr->Id);
			}
```



- 항목검색

```c
printf("Input name :\n");
			scanf("%s", name);
			while (ptr->link != NULL) {
				ptr = ptr->link;
				if (strcmp(name, ptr->name) == 0) {
					printf("(Name : %s / Phone Number : %s / Id : %d)\n\n", ptr->name, ptr->phone_num, ptr->Id);
				}
			}
```

