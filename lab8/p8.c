#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
	int capacity;
	int size;
	int* array;
} Heap;

Heap* createHeap(int capacity);
void insert(Heap* heap, int item);
int _find(Heap* heap, int item);
void find(Heap* heap, int item);
void print(Heap* heap);
int isFull(Heap* heap);

Heap* createHeap(int capacity) {
	Heap* heap;
	heap = malloc(sizeof(Heap));
	
	heap->capacity = capacity;
	heap->size = 0;
	heap->array = malloc(sizeof(int) * capacity);
	
	return heap;
}

void insert(Heap* heap, int item) {
	if (isFull(heap)) {
		printf("heap is full\n");
		return;
	}
	if (_find(heap, item)) {
		printf("%d is already in the heap.\n", item);
		return;
	}
	
	heap->array[++heap->size] = item;
	
	int child = heap->size;
	int parent = child / 2;
	while (child > 1 && heap->array[parent] < heap->array[child]) {
		int tempItem = heap->array[child];
		heap->array[child] = heap->array[parent];
		heap->array[parent] = tempItem;
		
		child = parent;
		parent = child / 2;
	}
	
	printf("insert %d\n", item);
}

int _find(Heap* heap, int item) {
	for (int i = 1; i <= heap->size; i++) {
		if (heap->array[i] == item) {
			return 1;
		}
	}
	return 0;
}

void find(Heap* heap, int item) {
	if (_find(heap, item)) {
		printf("%d is in the heap.\n", item);
	} else {
		printf("%d is in not the heap.\n", item);
	}
}
void print(Heap* heap) {
	for (int i = 1; i <= heap->size; i++) {
		printf("%d ", heap->array[i]);
	}
	printf("\n");
}
int isFull(Heap* heap) {
	return (heap->size == heap->capacity);
}

int main(int argc, char *argv[]) {
	FILE* fpInput = fopen("input.txt", "r");
	FILE* fpOutput = freopen("output.txt", "w", stdout); // stdout 스트림 출력을 파일 스트림으로 리다이렉트한다.
	
	int capacity;
	fscanf(fpInput, "%d", &capacity);
	Heap* heap = createHeap(capacity);
	
	while (!feof(fpInput)) {
		char command;
		int number;
		
		fscanf(fpInput, "%c %d", &command, &number);
		
		switch (command) {
			case 'i':
				insert(heap, number);
				break;
			case 'f':
				find(heap, number);
				break;
			case 'p':
				print(heap);
				break;
		}
	}
	
	fclose(fpInput);
	fclose(fpOutput);
	
	return 0;
}