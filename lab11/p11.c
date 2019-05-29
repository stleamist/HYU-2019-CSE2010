#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// MARK: 컴파일 상수
#define MAX_DISTANCE 99999
#define UNDEFINED -1


// MARK: 자료형 프로토타입 선언
typedef struct Heap Heap;
typedef struct Node Node;
typedef Node* Element;


// MARK: Heap 구조체 선언
struct Heap {
	int capacity;
	int size;
	Element* array;
};


// MARK: Heap 함수 프로로타입 선언
Heap* createHeap(int capacity); // capacity 크기의 배열을 가진 Heap 구조체를 생성해 반환한다.
void insertToHeap(Heap* heap, Element item); // heap에 item을 삽입한다.
Node* popFromHeap(Heap* heap); // heap의 최상단 항목을 반환한다.
int compareHeapItems(Element x, Element y); // 숫자가 아닌 자료형의 Heap 정렬을 사용하는 데에 필요한 함수이다. 재정렬(swap)이 필요하면 1을, 그렇지 않으면 0을 반환한다.
int _isFull(Heap* heap); // heap이 가득 찼는지의 여부를 반환한다.


// MARK: Heap 함수 정의

Heap* createHeap(int capacity) {
	Heap* heap;
	heap = malloc(sizeof(Heap));
	
	heap->capacity = capacity;
	heap->size = 0;
	heap->array = calloc(capacity, sizeof(Element));
	
	return heap;
}

void insertToHeap(Heap* heap, Element item) {
	if (_isFull(heap)) {
		printf("Heap is full\n");
		return;
	}
	
	heap->array[++heap->size] = item;
	
	int child = heap->size;
	int parent = child / 2;
	while (child > 1 && compareHeapItems(heap->array[parent], heap->array[child])) {
		Element tempItem = heap->array[child];
		heap->array[child] = heap->array[parent];
		heap->array[parent] = tempItem;
		
		child = parent;
		parent = child / 2;
	}
}

Element popFromHeap(Heap* heap) {
	Element firstItem = heap->array[1];
	Element lastItem = heap->array[heap->size--];
	
	int parent = 1;
	int child = parent * 2;
	
	while (child <= heap->size) {
		if (child != heap->size && compareHeapItems(heap->array[child + 1], heap->array[child])) {
			child += 1;
		}
		
		if (compareHeapItems(heap->array[child], lastItem)) {
			heap->array[parent] = heap->array[child];
		} else {
			break;
		}
		
		parent = child;
		child = parent * 2;
	}
	
	heap->array[parent] = lastItem;
	
	return firstItem;
}

int _isFull(Heap* heap) {
	return (heap->size == heap->capacity);
}


// MARK: Dijkstra 그래프 구조체
struct Node { // 다익스트라 알고리즘에서 방문하지 않은 노드들을 우선순위 큐에 넣는 데에 사용된다.
	int index;
	int distance;
};


// MARK: 숫자가 아닌 자료형의 Heap 정렬을 위한 함수 정의
int compareHeapItems(Element x, Element y) {
	// x: 부모 노드, y: 자식 노드
	return (x->distance) < (y->distance);
}


// MARK: Dijkstra 함수 프로로타입 선언
Node* createNode(int index, int distance); // Node 구조체를 생성해 반환한다.
char* calculateDijkstraPath(int** adjacencyMatrix, int adjacencyMatrixSize, int startIndex, int endIndex); // 에지의 가중치가 저장된 크기 adjacencyMatrixSize의 인접 행렬 adjacencyMatrix를 이용해서 startIndex에서 endIndex로 가는 최단 경로를 구한다.


// MARK: Dijkstra 함수 프로로타입 정의

Node* createNode(int index, int distance) {
	Node* node;
	node = malloc(sizeof(Node));
	
	node->index = index;
	node->distance = distance;
	
	return node;
}

char* calculateDijkstraPath(int** adjacencyMatrix, int adjacencyMatrixSize, int startIndex, int endIndex) {
	int* distances = (int *) calloc(adjacencyMatrixSize, sizeof(int));
	int* predecessorIndexes = (int *) calloc(adjacencyMatrixSize, sizeof(int));
	Heap* unvisitedNodes = createHeap(adjacencyMatrixSize);
	
	for (int i = 0; i < adjacencyMatrixSize; i++) {
		distances[i] = (i == startIndex) ? 0 : MAX_DISTANCE;
		predecessorIndexes[i] = UNDEFINED;
	}
	
	Node* startNode = createNode(startIndex, 0);
	insertToHeap(unvisitedNodes, startNode);
	
	for (int unvisitedNodesCount = adjacencyMatrixSize; unvisitedNodesCount > 0; unvisitedNodesCount--) {
		Node* unvisitedNodeWithMinDistance = popFromHeap(unvisitedNodes);
		int currentIndex = unvisitedNodeWithMinDistance->index;
		
		for (int i = 0; i < adjacencyMatrixSize; i++) {
			int weight = adjacencyMatrix[currentIndex][i];
			if (weight != UNDEFINED) {
				int linkedIndex = i;
				int currentDistance = distances[currentIndex];
				if (currentDistance + weight < distances[linkedIndex]) {
					distances[linkedIndex] = currentDistance + weight;
					Node* linkedNode = createNode(linkedIndex, currentDistance + weight);
					insertToHeap(unvisitedNodes, linkedNode);
					predecessorIndexes[linkedIndex] = currentIndex;
				}
			}
		}
	}
	
	// predecessorIndexes[]를 역추적하며 얻은 경로 노드 인덱스들을 pathString의 앞에 붙여 반환한다.
	char* pathString = (char*) calloc(adjacencyMatrixSize + 1, sizeof(char));
	pathString[0] = '\0';
	for (int i = endIndex; i != UNDEFINED; i = predecessorIndexes[i]) {
		char* copiedPathString = (char*) malloc(sizeof(pathString));
		strcpy(copiedPathString, pathString);
		sprintf(pathString, "%d %s", i, copiedPathString);
		free(copiedPathString);
	}
	
	return pathString;
}


// MARK: 테스트 케이스를 실행하는 함수
void runTestCase() {
	int adjacencyMatrixSize = 8;
	int** adjacencyMatrix = (int**) calloc(adjacencyMatrixSize, sizeof(int*));
	for (int i = 0; i < adjacencyMatrixSize; i++) {
		adjacencyMatrix[i] = (int*) calloc(adjacencyMatrixSize, sizeof(int));
		for (int j = 0; j < adjacencyMatrixSize; j++) {
			adjacencyMatrix[i][j] = UNDEFINED;
		}
	}
	adjacencyMatrix[1][2] = 2;
	adjacencyMatrix[1][4] = 1;
	adjacencyMatrix[2][5] = 10;
	adjacencyMatrix[2][4] = 3;
	adjacencyMatrix[3][1] = 4;
	adjacencyMatrix[3][6] = 5;
	adjacencyMatrix[4][3] = 2;
	adjacencyMatrix[4][6] = 8;
	adjacencyMatrix[4][7] = 4;
	adjacencyMatrix[4][5] = 2;
	adjacencyMatrix[5][7] = 6;
	adjacencyMatrix[7][6] = 1;
	
	char* pathString = calculateDijkstraPath(adjacencyMatrix, adjacencyMatrixSize, 3, 5);
	
	printf("%s", pathString);
}


// MARK: main
int main(int argc, const char * argv[]) {
	FILE* fpInput = fopen("input.txt", "r");
	FILE* fpOutput = freopen("output.txt", "w", stdout); // stdout 스트림 출력을 파일 스트림으로 리다이렉트한다.
	
	int maxNodeIndex = UNDEFINED;
	int adjacencyMatrixSize;
	int** adjacencyMatrix;
	int startIndex;
	int endIndex;
	
	while (getc(fpInput) != '\r') {
		int nodeIndex;
		fscanf(fpInput, "%d", &nodeIndex);
		if (nodeIndex > maxNodeIndex) {
			maxNodeIndex = nodeIndex;
		}
	}
	
	// adjacencyMatrix 초기화
	adjacencyMatrixSize = maxNodeIndex + 1;
	adjacencyMatrix = (int**) calloc(adjacencyMatrixSize, sizeof(int*));
	for (int i = 0; i < adjacencyMatrixSize; i++) {
		adjacencyMatrix[i] = (int*) calloc(adjacencyMatrixSize, sizeof(int));
		for (int j = 0; j < adjacencyMatrixSize; j++) {
			adjacencyMatrix[i][j] = UNDEFINED;
		}
	}
	
	while (getc(fpInput) != '\r') {
		int index, linkedIndex, weight;
		fscanf(fpInput, "%d-%d-%d", &index, &linkedIndex, &weight);
		adjacencyMatrix[index][linkedIndex] = weight;
	}
	
	while (!feof(fpInput)) {
		fscanf(fpInput, "%d %d", &startIndex, &endIndex);
	}
	
	char* pathString = calculateDijkstraPath(adjacencyMatrix, adjacencyMatrixSize, startIndex, endIndex);
	
	printf("%s", pathString);
	
	fclose(fpInput);
	fclose(fpOutput);
	
	return 0;
}
