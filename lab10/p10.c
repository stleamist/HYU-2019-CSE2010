#include <stdio.h>
#include <stdlib.h>

// 큐 구조체 선언
typedef struct Queue {
	int capacity;
	int startIndex;
	int endIndex;
	int* array;
} Queue;

// 그래프 구조체 선언
typedef struct Graph {
	int size;
	int* nodes;
	int** matrix;
} Graph;

// 큐 관련 함수들의 프로토타입 선언
Queue* createQueue(int capacity); // capacity 크기의 배열을 가진 Queue 구조체를 생성해 반환한다.
void enqueue(Queue* queue, int item); // queue의 뒤로 item을 추가한다.
int dequeue(Queue* queue); // queue의 앞 요소를 제거한 다음 그 값을 반환한다.
int isEmpty(Queue* queue); // queue가 비어있는지의 여부를 반환한다.
int isFull(Queue* queue); // queue가 가득 찼는지의 여부를 반환한다.

// 위상 정렬 관련 함수들의 프로토타입 선언
Graph* createGraph(int* nodes, int size); // nodes 배열과 그 크기 size를 가진 Graph 구조체를 생성해 반환한다.
void insertEdge(Graph* graph, int startNode, int endNode); // graph에 startNode에서 endNode를 가리키는 에지를 추가한다.
void printTopologicalSort(Graph* graph); // graph를 위상 정렬 알고리즘으로 출력한다.
int* calculateIndegrees(Graph* graph); // graph 구조체 내 matrix의 각 열마다 in-degree를 계산한 다음 그 값을 배열로 반환한다.
void printMatrix(Graph* graph); // graph 구조체 내 matrix를 2차원으로 출력한다.
int _findIndex(int* array, int size, int element); // size 크기의 array 배열에서 element를 가진 인덱스를 반환한다.

// 큐 관련 함수들의 정의
Queue* createQueue(int capacity) {
	Queue* queue;
	queue = malloc(sizeof(queue));
	
	queue->capacity = capacity;
	queue->startIndex = 0;
	queue->endIndex = -1;
	queue->array = malloc(sizeof(int) * capacity);
	
	return queue;
}
void enqueue(Queue* queue, int item) {
	if (isFull(queue)) {
		printf("Full\n");
		return;
	}
	queue->endIndex += 1;
	queue->array[queue->endIndex] = item;
}
int dequeue(Queue* queue) {
	if (isEmpty(queue)) {
		printf("Empty\n");
		return -1;
	}
	int prevStart = queue->array[queue->startIndex];
	queue->startIndex += 1;
	return prevStart;
}
int isEmpty(Queue* queue) {
	return (queue->startIndex > queue->endIndex) ? 1 : 0;
}
int isFull(Queue* queue) {
	return (queue->startIndex >= queue->capacity) ? 1 : 0;
}

// 위상 정렬 관련 함수들의 정의
Graph* createGraph(int* nodes, int size) {
	Graph* graph;
	graph = malloc(sizeof(Graph));
	
	graph->size = size;
	graph->nodes = nodes;
	graph->matrix = (int **) malloc(sizeof(int*[size]));
	for (int i = 0; i < size; i++) {
		graph->matrix[i] = (int *) calloc(size, sizeof(int));
	}
	
	return graph;
}
void insertEdge(Graph* graph, int startNode, int endNode) {
	int startNodeIndex = _findIndex(graph->nodes, graph->size, startNode);
	int endNodeIndex = _findIndex(graph->nodes, graph->size, endNode);
	graph->matrix[startNodeIndex][endNodeIndex] = 1;
}
void printTopologicalSort(Graph* graph) {
	Queue* queue = createQueue(graph->size);
	int* indegrees = calculateIndegrees(graph);
	
	printf("Topological Sort Result: ");
	
	// 시작 노드(in-degree가 0인 노드)들을 큐에 추가한다.
	for (int i = 0; i < graph->size; i++) {
		if (indegrees[i] == 0) {
			enqueue(queue, i);
		}
	}
	
	// 큐의 앞 요소를 인덱스로 갖는 노드가 가리키는 에지들을 제거한 다음,
	// 다시 in-degree가 0인 노드들을 찾고 이를 반복한다.
	while (!isEmpty(queue)) {
		int dequeuedIndex = dequeue(queue);
		printf("%d ", graph->nodes[dequeuedIndex]); // 위상 정렬 출력
		for (int i = 0; i < graph->size; i++) {
			if (graph->matrix[dequeuedIndex][i] == 1) {
				indegrees[i] -= 1;
				if (indegrees[i] == 0) {
					enqueue(queue, i);
				}
			}
		}
	}
	printf("\n");
}
int* calculateIndegrees(Graph* graph) {
	int* degrees = calloc(graph->size, sizeof(int));
	
	for (int column = 0; column < graph->size; column++) {
		for (int row = 0; row < graph->size; row++) {
			if (graph->matrix[row][column] == 1) {
				degrees[column] += 1;
			}
		}
	}
	
	return degrees;
}
void printMatrix(Graph* graph) {
	printf("Adjacency Matrix\n");
	
	// Print Column Headers
	printf(" ");
	for (int i = 0; i < graph->size; i++) {
		printf(" %d", graph->nodes[i]);
	}
	printf("\n");
	
	// Print Rows
	for (int i = 0; i < graph->size; i++) {
		printf("%d", graph->nodes[i]);
		for (int j = 0; j < graph->size; j++) {
			printf(" %d", graph->matrix[i][j]);
		}
		printf("\n");
	}
}
int _findIndex(int* array, int size, int element) {
	for (int i = 0; i < size; i++) {
		if (array[i] == element) {
			return i;
		}
	}
	return -1;
}

// 테스트 케이스를 실행하는 함수
void runTestCase() {
	int size = 6;
	int nodes[6] = {1, 2, 3, 6, 5, 7};
	Graph* graph = createGraph(nodes, size);
	insertEdge(graph, 1, 2);
	insertEdge(graph, 1, 6);
	insertEdge(graph, 2, 5);
	insertEdge(graph, 2, 6);
	insertEdge(graph, 2, 3);
	insertEdge(graph, 3, 5);
	insertEdge(graph, 5, 6);
	insertEdge(graph, 7, 3);
	insertEdge(graph, 7, 5);
	
	printMatrix(graph);
	printf("\n");
	printTopologicalSort(graph);
}

// main 함수
int main(int argc, char *argv[]) {
	FILE* fpInput = fopen("input.txt", "r");
	FILE* fpOutput = freopen("output.txt", "w", stdout); // stdout 스트림 출력을 파일 스트림으로 리다이렉트한다.
	
	
	// 첫 라인의 노드 개수를 세는 트릭 코드:
	// "n-n" 포맷이 아닌 "n" 포맷이면 n2에 양의 정수가 담기지 않는다는 점을 이용해서 첫 줄의 노드 개수를 센다.
	// 그 후 rewind()로 파일 포인터를 처음으로 돌린다.
	
	int size = 0;
	
	while (!feof(fpInput)) {
		int n1 = 0;
		int n2 = -1;
		
		fscanf(fpInput, "%d-%d", &n1, &n2);
		if (n2 == -1) {
			size += 1;
		}
	}
	rewind(fpInput);
	
	// 다시 파일의 처음으로 돌아와 이전에 얻은 노드 개수를 바탕으로 파일 입력을 처리한다.
	
	int* nodes = (int*) malloc(sizeof(int[size]));
	
	for (int i = 0; i < size; i++) {
		fscanf(fpInput, "%d", &(nodes[i]));
	}
	
	Graph* graph = createGraph(nodes, size);
	
	while (!feof(fpInput)) {
		int n1;
		int n2;
		
		fscanf(fpInput, "%d-%d", &n1, &n2);
		
		insertEdge(graph, n1, n2);
	}
	
	printMatrix(graph);
	printf("\n");
	printTopologicalSort(graph);
	
	fclose(fpInput);
	fclose(fpOutput);
	
	return 0;
}