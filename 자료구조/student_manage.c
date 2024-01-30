#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum level { freshman = 1, sophomore, junior, senior };  // 학년
struct student {		// 학생 정보를 저장할 구조체 모양
	char name[20];		// 이름
	enum level year;	// 학년
	int score;			// 점수
	struct student* next;	// 다른 학생을 가리킬 포인터
};

typedef struct student STUDENT;	// 닉네임 정의

STUDENT* buildClass(STUDENT* list) {

	
	STUDENT* tmp = (STUDENT*)malloc(sizeof(STUDENT));

	while (tmp->name != "끝" && tmp->year != 0 && tmp->score != 0) {
		STUDENT* tmp = (STUDENT*)malloc(sizeof(STUDENT));
		printf("학생 정보 (이름 학년 점수): ");
		scanf("%s %d %d", &tmp->name, &tmp->year, &tmp->score);
		if (tmp->name != "끝" && tmp->year != 0 && tmp->score != 0) {
			tmp->next = list;
			list = tmp;
		}
		else {
			free(tmp);
			break;
		}
	}
	
	return list;

	
}


void printClass(STUDENT* list) {   
	printf("\n** 학생 리스트 출력 **\n");
	for (STUDENT* p = list; p != NULL; p = p->next)
		printf("%s : %2d학년, %2d점\n", p->name, p->year, p->score);
}

void printStudent(STUDENT* list, char* p) {
	STUDENT* search = list;
	STUDENT* found = list;

	while (search != NULL) {
		if (!strcmp(search->name, p)) {
			found = search;
			printf("\n%s : %d학년, %d점\n", found->name, found->year, found->score);
		}
		search = search->next;
	}
	
	return NULL;
}

void findStudents(STUDENT* list, int low, int high) { 
	STUDENT* search = list;
	STUDENT* found = list;

	printf("\n*** %d점과 %d점 사이의 학생 정보 ***", low, high);
	while (search != NULL) {
		if (low <= search->score && search->score <= high) {
			found = search;
			printf("\n%s : %d학년, %d점", found->name, found->year, found->score);
		}
		search = search->next;
	}
	return NULL;
}

void printFour(STUDENT* list) { 
	STUDENT* p = list;

}

int main() {
	STUDENT* list = NULL;
	list = buildClass(list);
	printClass(list);
	printStudent(list, "윤이화");
	findStudents(list, 70, 80);
	//printFour(list);
	return 0;
}

