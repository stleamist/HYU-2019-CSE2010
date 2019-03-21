#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack {
	int capacity;
	int topIndex;
	int *array;
} Stack;

Stack* createStack(int capacity);
void push(Stack* stack, int number);
int pop(Stack* stack);
int top(Stack* stack);
int isEmpty(Stack* stack);
int isFull(Stack* stack);

Stack* createStack(int capacity) {
	Stack* stack;
	stack = malloc(sizeof(Stack));
	
	stack->capacity = capacity;
	stack->topIndex = -1;
	stack->array = malloc(sizeof(int) * capacity);
	
	return stack;
}
void push(Stack* stack, int number) {
	if (isFull(stack)) {
		printf("Full\n");
		return;
	}
	stack->topIndex += 1;
	stack->array[stack->topIndex] = number;
}
int pop(Stack* stack) {
	if (isEmpty(stack)) {
		printf("Empty\n");
		return -1;
	}
	int prevTop = stack->array[stack->topIndex];
	stack->topIndex -= 1;
	printf("%d\n", prevTop);
	return prevTop;
}
int top(Stack* stack) {
	if (isEmpty(stack)) {
		return -1;
	}
	return stack->array[stack->topIndex];
}
int isEmpty(Stack* stack) {
	return (stack->topIndex == -1) ? 1 : 0;
}
int isFull(Stack* stack) {
	return (stack->topIndex == (stack->capacity - 1)) ? 1 : 0;
}

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

int main(int argc, char *argv[]) {
	Stack* stack = createStack(100);
	
	FILE *fpInput, *fpOutput;
	fpInput = fopen("input.txt", "r");
	fpOutput = freopen("output.txt", "w", stdout); // stdout 스트림 출력을 파일 스트림으로 리다이렉트한다.
	
	int numberOfLines;
	fscanf(fpInput, "%d", &numberOfLines);
	
	for (int i = 0; i < numberOfLines; i++) {
		char command[5];
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