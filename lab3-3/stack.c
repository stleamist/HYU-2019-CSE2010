#include "stack.h"

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