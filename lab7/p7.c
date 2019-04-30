#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 벽의 방향을 표현하는 컴파일 상수
#define D_RIGHT 0
#define D_BOTTOM 1

// 벽의 상태를 표현하는 컴파일 상수
#define W_CLOSED 1
#define W_OPEN 0
#define W_BOUNDARY -1


// 서로소 집합 자료형 선언
typedef int DisjointSet;

// 미로 구조체 선언
typedef int Wall;
typedef struct Maze {
	int size;
	DisjointSet* cells;
	Wall** walls;
} Maze;


// 서로소 집합 관련 함수들의 프로토타입 선언
DisjointSet* createDisjointSet(int size); // 서로소 집합의 사용할 size + 1 크기의 배열을 생성해 반환한다.
int findRoot(DisjointSet* set, int value); // 서로조 집합의 루트 값을 찾아 반환한다.
void unionRoots(DisjointSet* set, int root1, int root2); // 서로소 집합을 합집합한다.
int getNumberOfSubsets(DisjointSet* set, int size); // 서로소 집합 내 부분집합의 개수를 반환한다.

// 미로 관련 함수들의 프로토타입 선언
Maze* createMaze(int size); // size 크기의 미로 정보를 담은 Maze 구조체를 생성해 반환한다.
Wall** _createWalls(int size); // 벽의 상태를 저장할 2차원 배열을 생성해 반환한다.
Maze* _shuffleMaze(Maze* maze); // 초기 상태의 Maze 구조체에 임의의 유효한 미로 정보를 담아 반환한다.
void printMaze(Maze* maze); // maze를 2차원 그림으로 출력한다.


// 서로소 집합 관련 함수들의 정의
DisjointSet* createDisjointSet(int size) {
	DisjointSet* set = (DisjointSet*) calloc(size + 1, sizeof(DisjointSet)); // 인덱스와 실제 값을 일치시키기 위해 size + 1 크기의 배열을 생성한다.
	return set;
}
int findRoot(DisjointSet* set, int value) {
	int root = value;
	while (set[root] > 0) {
		root = set[root];
	}
	return root;
}
void unionRoots(DisjointSet* set, int root1, int root2) {
	if (set[root1] < set[root2]) {
		set[root1] = root2;
	} else {
		set[root2] = root1;
	}
}
int getNumberOfSubsets(DisjointSet* set, int size) {
	int numberOfZero = 0;
	for (int i = 1; i <= size; i++) { // createDisjointSet(int size)에 설명한대로 집합의 0번째 인덱스는 사용하지 않는다.
		if (set[i] == 0) {
			numberOfZero += 1;
		}
	}
	return numberOfZero;
}

// 미로 관련 함수들의 프로토타입 정의
Maze* createMaze(int size) {
	Maze* maze = (Maze*) malloc(sizeof(Maze));
	maze->size = size;
	maze->cells = createDisjointSet(size * size);
	maze->walls = _createWalls(size);
	maze = _shuffleMaze(maze);
	return maze;
}
Wall** _createWalls(int size) {
	// 각 셀의 오른쪽 벽, 아랫쪽 벽의 존재 유무를 저장하기 위한 2차원 배열로, 그 값은 W_CLOSED(1) W_OPEN(0) W_BOUNDARY(-1) 중 하나로 표현된다.
	// 불필요하지만 코드 작성의 편의를 위해 최우측 셀과 최하단 셀의 테두리 벽의 존재 유무에 대한 정보도 포함하고 있으며, 그 값은 항상 W_BOUNDARY이다.
	Wall** walls = (Wall**) malloc(sizeof(Wall[size * size][2]));
	
	for (int cell = 1; cell <= size * size; cell++) {
		int isRightEnd = cell % size == 0 ? 1 : 0;
		int isBottomEnd = cell > size * (size - 1) ? 1 : 0;
		
		walls[cell - 1] = (int*) malloc(sizeof(int[2]));
		walls[cell - 1][D_RIGHT] = isRightEnd ? W_BOUNDARY : W_CLOSED;
		walls[cell - 1][D_BOTTOM] = isBottomEnd ? W_BOUNDARY : W_CLOSED;
	}
	
	return walls;
}
Maze* _shuffleMaze(Maze* maze) {
	int size = maze->size;
	srand(time(NULL));
	
	do {
		// 임의의 셀이 가진 오른쪽 벽과 아랫쪽 벽 중 하나를 다시 임의로 선택한다.
		int cellNumber = rand() % (size * size) + 1;
		Wall wallDirection = rand() % 2; // 0: D_RIGHT, 1: D_BOTTOM
		
		
		if (maze->walls[cellNumber - 1][wallDirection] == W_BOUNDARY) {
			continue;
		}
		
		int associatedCellNumber = wallDirection ? cellNumber + size : cellNumber + 1;
		
		int root1 = findRoot(maze->cells, cellNumber);
		int root2 = findRoot(maze->cells, associatedCellNumber);
		
		if (root1 != root2) {
			unionRoots(maze->cells, root1, root2);
			maze->walls[cellNumber - 1][wallDirection] = W_OPEN;
		}
	} while (getNumberOfSubsets(maze->cells, size * size) > 1);
	
	return maze;
}
void printMaze(Maze* maze) {
	int size = maze->size;
	int tableSize = size + (size + 1);
	
	// 2차원 동적 배열 초기화
	char** table = (char**) malloc(sizeof(int[tableSize][tableSize]));
	for (int i = 0; i < tableSize; i++) {
		table[i] = (char*) malloc(sizeof(char[tableSize]));
		for (int j = 0; j < tableSize; j++) {
			table[i][j] = ' ';
		}
	}
	
	// 교점
	for (int i = 0; i < tableSize; i += 2) {
		for (int j = 0; j < tableSize; j += 2) {
			table[i][j] = '+';
		}
	}
	
	// 테두리
	for (int i = 1; i < tableSize; i += 2) {
		table[0][i] = table[tableSize - 1][i] = '-';
		table[i][0] = table[i][tableSize - 1] = '|';
	}
	
	// 내부 벽
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int cellIndex = size * i + j;
			table[i*2 + 1][(j+1) * 2] = maze->walls[cellIndex][D_RIGHT] ? '|' : ' ';
			table[(i+1) * 2][j*2 + 1] = maze->walls[cellIndex][D_BOTTOM] ? '-' : ' ';
		}
	}
	
	// 입구 및 출구
	table[1][0] = table[tableSize - 2][tableSize - 1] = ' ';
	
	// 출력
	for (int i = 0; i < tableSize; i++) {
		for (int j= 0; j < tableSize; j++) {
			printf("%c", table[i][j]);
		}
		printf("\n");
	}
}

// 테스트 케이스를 실행하는 함수
void runTestCase() {
	int size = 5;
	Maze* maze = createMaze(size);
	printMaze(maze);
}

// main 함수
int main(int argc, char *argv[]) {
	FILE* fpInput = fopen("input.txt", "r");
	FILE* fpOutput = freopen("output.txt", "w", stdout); // stdout 스트림 출력을 파일 스트림으로 리다이렉트한다.
	
	int size;
	fscanf(fpInput, "%d", &size);
	
	Maze* maze = createMaze(size);
	printMaze(maze);
	
	fclose(fpInput);
	fclose(fpOutput);
	
	return 0;
}