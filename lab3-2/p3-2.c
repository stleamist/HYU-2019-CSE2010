//
//
//
//
//
//
//
//
// 함수의 설명은 함수의 프로토타입 선언 우측에 작성해 놓았습니다.
//
//
//
//
//
//
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 큐 구조체 요소의 자료형 선언
typedef int Element;

// 큐 구조체 선언
typedef struct Queue {
	int capacity;
	int startIndex;
	int endIndex;
	Element* array;
} Queue;

// 큐 관련 함수들의 프로토타입 선언
Queue* createQueue(int capacity); // capacity 크기의 배열을 가진 Queue 구조체를 생성해 반환한다.
int enqueue(Queue* queue, Element item); // queue의 뒤로 item을 추가한다.
int dequeue(Queue* queue); // queue의 앞 요소를 제거한 다음 그 값을 반환한다.
int isEmpty(Queue* queue); // queue가 비어있는지의 여부를 반환한다.
int isFull(Queue* queue); // queue가 가득 찼는지의 여부를 반환한다.

// 큐 관련 함수들의 정의
Queue* createQueue(int capacity) {
	Queue* queue;
	queue = malloc(sizeof(queue));
	
	queue->capacity = capacity;
	queue->startIndex = 0;
	queue->endIndex = -1;
	queue->array = malloc(sizeof(Element) * capacity);
	
	return queue;
}
int enqueue(Queue* queue, Element item) {
	if (isFull(queue)) {
		printf("Full\n");
		return -1;
	}
	queue->endIndex += 1;
	queue->array[queue->endIndex] = item;
	return 0;
}
int dequeue(Queue* queue) {
	if (isEmpty(queue)) {
		printf("Empty\n");
		return -1;
	}
	Element prevStart = queue->array[queue->startIndex];
	queue->startIndex += 1;
	printf("%d\n", prevStart);
	return 0;
}
int isEmpty(Queue* queue) {
	return (queue->startIndex > queue->endIndex) ? 1 : 0;
}
int isFull(Queue* queue) {
	return (queue->startIndex >= queue->capacity) ? 1 : 0;
}

// 테스트 케이스를 실행하는 함수
void runTestCase() {
	Queue* queue = createQueue(100);
	enqueue(queue, 1);
	enqueue(queue, 2);
	enqueue(queue, 12);
	dequeue(queue);
	dequeue(queue);
	dequeue(queue);
	dequeue(queue);
}

// main 함수
int main(int argc, char *argv[]) {
	Queue* queue = createQueue(100);
	
	FILE* fpInput = fopen("input.txt", "r");
	FILE* fpOutput = freopen("output.txt", "w", stdout); // stdout 스트림 출력을 파일 스트림으로 리다이렉트한다.
	
	int numberOfLines;
	fscanf(fpInput, "%d", &numberOfLines);
	
	for (int i = 0; i < numberOfLines; i++) {
		char command[4]; // NULL이 들어갈 고려해 크기를 한 칸 더 늘려줘야 한다.
		int number;
		
		fscanf(fpInput, "%s %d", command, &number);
		
		if (!strcmp(command, "enQ")) {
			enqueue(queue, number);
		} else if (!strcmp(command, "deQ")) {
			dequeue(queue);
		}
	}
	
	fclose(fpInput);
	fclose(fpOutput);
	
	return 0;
}