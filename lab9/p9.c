#include <stdio.h>
#include <stdlib.h>

// 최대 자식 개수를 나타내는 컴파일 상수
#define DEGREE 3


// B-Tree 구조체 선언
typedef struct BNode BNode;
struct BNode {
	int elementsCount;
	int elements[DEGREE - 1];
	BNode* children[DEGREE];
};

// 삽입 결과를 나타내는 데에 사용할 열거형 선언
typedef enum InsertionResult {
	Success,
	Insert
} InsertionResult;


// B-Tree 관련 함수들의 프로토타입 선언
BNode* insert(BNode* root, int element);
InsertionResult _insert(BNode *node, int element, int *upElement, BNode **rightNode);
int findPositionToInsert(BNode* node, int element);
void printInorder(BNode* node);


// B-Tree 관련 함수들의 프로토타입 정의
BNode* insert(BNode* root, int element) {
	// result 말고도 upElement, rightNode를 _insert 함수에서 반환값으로 받기 위해 포인터 주소를 넘긴다.
	int upElement; // 자식 노드에서 올라온 요소
	BNode* rightNode; // 분리된 노드의 오른쪽. 분리된 노드의 왼쪽은 root이다.
	InsertionResult result = _insert(root, element, &upElement, &rightNode);
	
	if (result == Insert) {
		// root를 leftNode에 대입하고 leftNode와 rightNode를 자식으로 갖는 새로운 루트 노드를 생성해 반환한다.
		BNode* leftNode = root;
		root = malloc(sizeof(BNode));
		root->elementsCount = 1;
		root->elements[0] = upElement;
		root->children[0] = leftNode;
		root->children[1] = rightNode;
	}

	return root;
}
InsertionResult _insert(BNode *node, int element, int *upElement, BNode **rightNode) {
	int position, splitPosition;
	int newElement, lastElement;
	BNode *newChildNode, *lastChildNode;
	
	if (node == NULL) {
		*rightNode = NULL;
		*upElement = element;
		return Insert;
	}
	
	position = findPositionToInsert(node, element);
	
	InsertionResult result = _insert(node->children[position], element, &newElement, &newChildNode);
	if (result != Insert) {
		return result;
	}
	
	// node의 elements가 아직 가득차지 않았을 경우
	if (node->elementsCount < DEGREE - 1) {
		position = findPositionToInsert(node, newElement);
		
		// position ~ elementCount 범위의 요소와 자식을 오른쪽으로 한 칸씩 밀어낸다.
		for (int i = node->elementsCount; i > position; i--) {
			node->elements[i] = node->elements[i - 1];
			node->children[i + 1] = node->children[i];
		}
		
		// element를 elements[position]에 삽입한다.
		node->elements[position] = newElement;
		node->children[position + 1] = newChildNode;
		node->elementsCount += 1;
		return Success;
	}
	
	// node의 elements가 가득찼을 때
	if (position == DEGREE - 1) { // 삽입할 위치가 elements의 마지막인 경우
		lastElement = newElement;
		lastChildNode = newChildNode;
	} else { // 삽입할 위치가 elements의 마지막이 아닌 경우
		lastElement = node->elements[DEGREE - 2];
		lastChildNode = node->children[DEGREE - 1];
		for (int i = DEGREE - 2; i > position; i--) {
			node->elements[i] = node->elements[i - 1];
			node->children[i + 1] = node->children[i];
		}
		node->elements[position] = newElement;
		node->children[position + 1] = newChildNode;
	}
	
	splitPosition = (DEGREE - 1) / 2;
	(*upElement) = node->elements[splitPosition];
	
	// node에서 분리해낼 rightNode를 생성한다.
	(*rightNode) = malloc(sizeof(BNode));
	
	// node와 rightNode의 elementsCount를 업데이트한다.
	node->elementsCount = splitPosition;
	(*rightNode)->elementsCount = (DEGREE - 1) - splitPosition;
	
	// rightNode의 childs를 node에서 가져온다.
	for (int i = 0; i < (*rightNode)->elementsCount; i++) {
		(*rightNode)->children[i] = node->children[splitPosition + i + 1];
		if (i < (*rightNode)->elementsCount - 1) {
			(*rightNode)->elements[i] = node->elements[splitPosition + i + 1];
		} else {
			(*rightNode)->elements[i] = lastElement;
		}
	}
	(*rightNode)->children[(*rightNode)->elementsCount] = lastChildNode;
	
	return Insert;
}
int findPositionToInsert(BNode* node, int element) {
	int position = 0;
	while (position < node->elementsCount && element > node->elements[position])
		position += 1;
	return position;
}
void printInorder(BNode* node) {
	if (node == NULL) {
		return;
	}
	
	for (int i = 0; i < node->elementsCount; i++) {
		if (i == 0) {
			printInorder(node->children[i]);
		}
		printf("%d ", node->elements[i]);
		printInorder(node->children[i+1]);
	}
}

// 테스트 케이스를 실행하는 함수
void runTestCase() {
	BNode* root = NULL;
	root = insert(root, 1);
	root = insert(root, 7);
	root = insert(root, 6);
	root = insert(root, 2);
	root = insert(root, 11);
	root = insert(root, 4);
	root = insert(root, 8);
	root = insert(root, 5);
	root = insert(root, 15);
	root = insert(root, 3);
	root = insert(root, 12);
	printInorder(root);
}

// main 함수
int main(int argc, char *argv[]) {
	FILE* fpInput = fopen("input.txt", "r");
	FILE* fpOutput = freopen("output.txt", "w", stdout); // stdout 스트림 출력을 파일 스트림으로 리다이렉트한다.
	
	BNode* root = NULL;
	
	while (!feof(fpInput)) {
		char command;
		int number;
		
		fscanf(fpInput, "%c %d", &command, &number);
		
		switch (command) {
			case 'i':
				root = insert(root, number);
				break;
			case 'p':
				printInorder(root);
				break;
		}
	}
	
	fclose(fpInput);
	fclose(fpOutput);
	
	return 0;
}