#include <stdio.h>
#include <stdlib.h>

// 리스트 관련 구조체들의 typedef 선언
typedef struct Node Node;
typedef struct Node List;
typedef struct Student Student;

// 리스트 관련 구조체들의 선언
struct Student {
	int id;
	char* name;
};
struct Node {
	Student student;
	Node* next;
};

// 리스트 관련 함수들의 프로토타입 선언
List* createList();
void insertStudent(List* list, Student student);
void deleteStudent(List* list, int studentID);
Node* findStudent(List* list, int studentID);
void printStudentList(List* list);

// 리스트 관련 내부 함수들의 프로토타입 선언
void _deleteNode(List* list, Node* node);
Node* _findStudentNode(List* list, int studentID);
Node* _findStudentNodeToInsertAfter(List* list, int studentID);
Node* _findPreviousNode(List* list, Node* node);
void _printInlineStudentList(List* list);

// 리스트 관련 함수들의 정의
List* createList() {
	List* list = (List*)malloc(sizeof(List));
	list->next = NULL;
	return list;
}
void insertStudent(List* list, Student student) {
	// 조건: 리스트는 오름차순으로 정렬되어 있어야 하고, ID가 중복되는 학생은 삽입할 수 없다.
	if (_findStudentNode(list, student.id) != NULL) {
		printf("Insertion Failed. ID %d already exists.\n", student.id);
		return;
	}
	
	Node* newNode = (Node*)malloc(sizeof(Node));
	Node* prevNode = _findStudentNodeToInsertAfter(list, student.id);
	
	newNode->student = student;
	newNode->next = prevNode->next;
	prevNode->next = newNode;
	
	printf("Insertion Success : %d\n", student.id);
	_printInlineStudentList(list);
}
void deleteStudent(List* list, int studentID) {
	Node* node = _findStudentNode(list, studentID);
	
	if (node != NULL) {
		_deleteNode(list, node);
		printf("Deletion Success : %d\n", studentID);
		_printInlineStudentList(list);
	} else {
		printf("Deletion Failed : Student ID %d is not in the list.\n", studentID);
	}
}
Node* findStudent(List* list, int studentID) {
	Node* node = _findStudentNode(list, studentID);
	
	if (node != NULL) {
		printf("Find Success : %d %s\n", node->student.id, node->student.name);
	} else {
		printf("Find %d Failed. There is no student ID\n", studentID);
	}
	
	return node;
}
void printStudentList(List* list) {
	Node* node = list->next;
	
	printf("-----LIST-----\n");
	while (node != NULL) {
		printf("%d %s\n", node->student.id, node->student.name);
		node = node->next;
	}
	printf("--------------\n");
}

// 리스트 관련 내부 함수들의 정의
void _deleteNode(List* list, Node* node) {
	Node* prevNode = _findPreviousNode(list, node);
	
	prevNode->next = node->next;
	free(node);
}
Node* _findStudentNode(List* list, int studentID) {
	Node* node = list->next;
	
	while (node != NULL) {
		if (node->student.id == studentID) {
			break;
		} else {
			node = node->next;
		}
	}
	
	return node;
}
Node* _findStudentNodeToInsertAfter(List* list, int studentID) {
	Node* node = list;
	
	while (node->next != NULL) {
		if (node->next->student.id > studentID) {
			break;
		} else {
			node = node->next;
		}
	}
	
	return node;
}
Node* _findPreviousNode(List* list, Node* node) {
	Node* prevNode = list;
	
	while (prevNode->next != NULL) {
		if (prevNode->next == node) { // FIXME: 주소값을 비교해야 하나?
			break;
		} else {
			prevNode = prevNode->next;
		}
	}
	
	return prevNode;
}
void _printInlineStudentList(List* list) {
	Node* node = list->next;
	
	printf("Current List > ");
	while (node != NULL) {
		printf("%d %s", node->student.id, node->student.name);
		
		if (node->next != NULL) {
			printf("-");
		}
		
		node = node->next;
	}
	printf("\n");
}

// 테스트 케이스를 실행하는 함수
void runTestCase() {
	List* list = createList();
	
	Student s1 = {.id = 201411, .name = "Brian Lee"};
	Student s2 = {.id = 201402, .name = "Susan Kim"};
	Student s3 = {.id = 201411, .name = "Brian Lee"};
	Student s4 = {.id = 201423, .name = "Nancy Park"};
	Student s5 = {.id = 111111, .name = "Tyler Lee"};
	
	insertStudent(list, s1);
	insertStudent(list, s2);
	insertStudent(list, s3);
	insertStudent(list, s4);
	deleteStudent(list, 201411);
	findStudent(list, 201402);
	findStudent(list, 201411);
	insertStudent(list, s5);
	deleteStudent(list, 111122);
	printStudentList(list);
}

// main 함수
int main(int argc, char *argv[]) {
	List* list = createList();
	
	FILE* fpInput = fopen("input.txt", "r");
	FILE* fpOutput = freopen("output.txt", "w", stdout); // stdout 스트림 출력을 파일 스트림으로 리다이렉트한다.
	
	while(!feof(fpInput)) {
		char buffer[100];
		
		char command;
		int studentID;
		char studentFirstName[30];
		char studentLastName[30];
		
		// 라인 내 단어가 4개 미만일 때도 원활하게 값을 읽어들이기 위해 fscanf 대신 fgets와 sscanf를 함께 사용한다.
		fgets(buffer, 100, fpInput);
		sscanf(buffer, "%c %d %s %s", &command, &studentID, studentFirstName, studentLastName);
		
		Student student;
		student.id = studentID;
		student.name = (char*)malloc(sizeof(char) * 61);
		sprintf(student.name, "%s %s", studentFirstName, studentLastName);
			
		switch (command) {
			case 'i': insertStudent(list, student); break;
			case 'd': deleteStudent(list, student.id); break;
			case 'f': findStudent(list, student.id); break;
			case 'p': printStudentList(list); break;
		}
	}
	
	fclose(fpInput);
	fclose(fpOutput);
	
	return 0;
}