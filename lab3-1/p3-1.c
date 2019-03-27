#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 스택 구조체 요소의 자료형 선언
typedef int Element;

// 스택 구조체 선언
typedef struct Stack {
	int capacity;
	int topIndex;
	Element* array;
} Stack;

// 스택 관련 함수들의 프로토타입 선언
Stack* createStack(int capacity); // capacity 크기의 배열을 가진 Stack 구조체를 생성해 반환한다.
int push(Stack* stack, Element item); // stack의 위로 item을 푸시한다.
int pop(Stack* stack); // stack의 윗 요소를 팝한다.
Element top(Stack* stack); // stack의 윗 요소를 반환한다.
int isEmpty(Stack* stack); // stack이 비어있는지의 여부를 반환한다.
int isFull(Stack* stack); // stack이 가득 찼는지의 여부를 반환한다.

// 스택 관련 함수들의 정의
Stack* createStack(int capacity) {
	Stack* stack;
	stack = malloc(sizeof(Stack));
	
	stack->capacity = capacity;
	stack->topIndex = -1;
	stack->array = malloc(sizeof(Element) * capacity);
	
	return stack;
}
int push(Stack* stack, Element item) {
	if (isFull(stack)) {
		printf("Full\n");
		return -1;
	}
	stack->topIndex += 1;
	stack->array[stack->topIndex] = item;
	return 0;
}
int pop(Stack* stack) {
	if (isEmpty(stack)) {
		printf("Empty\n");
		return -1;
	}
	Element prevTop = top(stack);
	stack->topIndex -= 1;
	printf("%d\n", prevTop);
	return 0;
}
Element top(Stack* stack) {
	if (!isEmpty(stack)) {
		return stack->array[stack->topIndex];
	}
}
int isEmpty(Stack* stack) {
	return (stack->topIndex == -1) ? 1 : 0;
}
int isFull(Stack* stack) {
	return (stack->topIndex == (stack->capacity - 1)) ? 1 : 0;
}

// 테스트 케이스를 실행하는 함수
void runTestCase() {
	Stack* stack = createStack(100);
	push(stack, 1);
	push(stack, 2);
	push(stack, 12);
	pop(stack);
	pop(stack);
	pop(stack);
	pop(stack);
}

// main 함수
int main(int argc, char *argv[]) {
	Stack* stack = createStack(100);
	
	FILE* fpInput = fopen("input.txt", "r");
	FILE* fpOutput = freopen("output.txt", "w", stdout); // stdout 스트림 출력을 파일 스트림으로 리다이렉트한다.
	
	int numberOfLines;
	fscanf(fpInput, "%d", &numberOfLines);
	
	for (int i = 0; i < numberOfLines; i++) {
		char command[5]; // NULL이 들어갈 고려해 크기를 한 칸 더 늘려줘야 한다.
		int number;
		
		fscanf(fpInput, "%s %d", command, &number);
		
		if (!strcmp(command, "push")) {
			push(stack, number);
		} else if (!strcmp(command, "pop")) {
			pop(stack);
		}
	}
	
	fclose(fpInput);
	fclose(fpOutput);
	
	return 0;
}