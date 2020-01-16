#include<stdio.h>

int number;

typedef struct employee {
	char name[10];
	int age;
	int salary;
	char department[20];
} Employee;

Employee Empty = { 0,0,0,0 };

void insert(Employee *people, char *word) {
	int i=0;
	for (i = 0; i < number; i++) {
		if (strcmp(people[i].name, "") == 0) break;
	}
	if (i == number) {
		printf("Not enough space\n");
		return;
	}
	word = strtok(NULL, " ");
	strcpy(people[i].name, word);
	word = strtok(NULL, " ");
	people[i].age = atoi(word);
	word = strtok(NULL, " ");
	people[i].salary = atoi(word);
	word = strtok(NULL, " ");
	strcpy(people[i].department, word);
}

void delete_one(Employee *people, char *word) {
	int i;
	word = strtok(NULL, "\n");
	for (i = 0; i < number; i++) {
		if (strcmp(people[i].name, word) == 0) {
			people[i] = Empty; break;
		}
	}
	if (i == number) {
		printf("Not found\n");
		return;
	}
}

int find(Employee *people, char *word) {
	int i;
	word = strtok(NULL, "\n");
	for (i = 0; i < number; i++) {
		if (strcmp(people[i].name, word) == 0)
		{
			break;
		}
	}
	if (i == number) {
		return -1;
	}
	else { return i; }
}
void inform(Employee *people, char *word) {
	int i;
	word = strtok(NULL, "\n");
	int is=0;
	for (i = 0; i < number; i++) {
		if (strcmp(people[i].name, word) == 0) {
			printf("%s ", people[i].name);
			printf("%d ", people[i].age);
			printf("%d ", people[i].salary);
			printf("%s", people[i].department);
			is = 1;
		}
	}
	if (is==0) printf("Not found\n");
	return;
}

int avgBenefit(Employee *people, char *word) {
	int i;
	int sum = 0;
	int num=0;
	word = strtok(NULL, " ");
	for (i = 0; i < number; i++) {
		if (strcmp(people[i].department, word)==0) {
			num++;
			sum += people[i].salary;
		}
	}
	if (num == 0) {
		return 0;
	}
	else {
		return (sum / num);
	}
}

int main() {
	char input[100];
	char *word;
	Employee *people;
	int flag = 0, i;
	fgets(input,sizeof(input),stdin);
	word = strtok(input, " ");
	if (word == NULL) return 0;
	if (strcmp(word, "set") == 0) {
		word = strtok(NULL, " ");
		number = atoi(word);
		people = (Employee*)malloc(sizeof(Employee)*number);
		flag = 1;
	}
	if (!flag) return 0;
	for (i = 0; i < number; i++) {
		people[i] = Empty;
	}
	while (1) {
		fgets(input,sizeof(input),stdin);
		word = strtok(input, " ");
		if (word == NULL) break;
		if (strcmp(word, "insert") == 0) insert(people, word);
		else if (strcmp(word, "delete") == 0) delete_one(people, word);
		else if (strcmp(word, "find") == 0) printf("%d\n", find(people, word));
		else if (strcmp(word, "inform") == 0) inform(people, word);
		else if (strcmp(word, "avg") == 0) printf("%d\n", avgBenefit(people, word));
		 
	}
	free(people);
	return 0;
}