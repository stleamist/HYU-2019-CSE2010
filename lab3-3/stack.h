#include <stdio.h>
#include <stdlib.h>

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