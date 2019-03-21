#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Queue {
	int capacity;
	int startIndex;
	int endIndex;
	int* array;
} Queue;

Queue* createQueue(int capacity);
void enqueue(Queue* queue, int number);
int dequeue(Queue* queue);
int end(Queue* queue);
int isEmpty(Queue* queue);
int isFull(Queue* queue);

Queue* createQueue(int capacity) {
	Queue* queue;
	queue = malloc(sizeof(queue));
	
	queue->capacity = capacity;
	queue->startIndex = 0;
	queue->endIndex = -1;
	queue->array = malloc(sizeof(int) * capacity);
	
	return queue;
}
void enqueue(Queue* queue, int number) {
	if (isFull(queue)) {
		printf("Full");
		return;
	}
	queue->endIndex += 1;
	queue->array[queue->endIndex] = number;
}
int dequeue(Queue* queue) {
	if (isEmpty(queue)) {
		printf("Empty");
		return -1;
	}
	int prevStart = queue->array[queue->startIndex];
	queue->startIndex += 1;
	printf("%d\n", prevStart);
	return prevStart;
}
int isEmpty(Queue* queue) {
	return (queue->startIndex > queue->endIndex) ? 1 : 0;
}
int isFull(Queue* queue) {
	return (queue->startIndex >= queue->capacity) ? 1 : 0;
}

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

int main(int argc, char *argv[]) {
	Queue* queue = createQueue(100);
	
	FILE* fpInput = fopen("input.txt", "r");
	FILE* fpOutput = freopen("output.txt", "w", stdout); // stdout 스트림 출력을 파일 스트림으로 리다이렉트한다.
	
	int numberOfLines;
	fscanf(fpInput, "%d", &numberOfLines);
	
	for (int i = 0; i < numberOfLines; i++) {
		char command[5];
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