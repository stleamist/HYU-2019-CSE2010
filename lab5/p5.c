#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 트리 노드 구조체 선언
typedef struct Node Node;
struct Node {
	int value;
	Node* left;
	Node* right;
};

// 이진 탐색 트리 관련 함수들의 프로토타입 선언
Node* createNode(int value); // value를 가진 노드를 생성해 반환한다.
Node* insertNode(Node* node, int value); // node 트리에 value를 가진 노드를 삽입해 반환한다.
Node* deleteNode(Node* node, int value); // node 트리에서 value를 가진 노드를 삭제해 반환한다.
Node* deleteNodeSafely(Node* node, int value); // node 트리에서 value를 가진 노드를 삭제해 반환한다. 삭제할 노드가 자식이 없는 최상단 루트일 때는 삭제를 수행하지 않는다.
Node* findNode(Node* node, int value); // node 트리에서 value를 가진 노드를 찾아 반환한다.
Node* findMaxNode(Node* node); // node 트리에서 가장 큰 값을 가진 노드를 찾아 반환한다.
Node* findMinNode(Node* node); // node 트리에서 가장 작은 값을 가진 노드를 찾아 반환한다.
void printInorder(Node* node); // node 트리의 노드 값을 중위 순회하여 개행 문자와 함께 출력한다.
void printPreorder(Node* node); // node 트리의 노드 값을 전위 순회하여 개행 문자와 함께 출력한다.
void printPostorder(Node* node); // node 트리의 노드 값을 후위 순회하여 개행 문자와 함께 출력한다.
void _printInorderElements(Node* node); // node 트리의 노드 값을 중위 순회하여 출력한다.
void _printPreorderElements(Node* node); // node 트리의 노드 값을 전위 순회하여 출력한다.
void _printPostorderElements(Node* node); // node 트리의 노드 값을 후위 순회하여 출력한다.

// 이진 탐색 트리 관련 함수들의 정의
Node* createNode(int value) {
	Node* node = malloc(sizeof(Node));
	node->value = value;
	node->left = node->right = NULL;
	return node;
}
Node* insertNode(Node* node, int value) {
	if (node == NULL) {
		return createNode(value);
	} else if (value < node->value) {
		node->left = insertNode(node->left, value);
	} else if (value > node->value) {
		node->right = insertNode(node->right, value);
	} else if (value == node->value) {
		printf("%d already exists.\n", value);
	}
	
	return node;
}
Node* deleteNodeSafely(Node* node, int value) {
	if (node == NULL) {
		printf("Deletion failed. %d does not exist.\n", value);
		return NULL;
	} else if ((value == node->value) && (node->left == NULL) && (node->right == NULL)) {
		// node의 value가 node와 같고, node가 자식이 없는 최상단 루트일 때는 삭제를 수행하지 않는다.
		printf("Root node that doesn't have any children cannot be deleted.\n");
		return NULL;
	} else {
		return deleteNode(node, value);
	}
}
Node* deleteNode(Node* node, int value) {
	if (node == NULL) {
		printf("Deletion failed. %d does not exist.\n", value);
		return NULL;
	} else if (value < node->value) {
		node->left = deleteNode(node->left, value);
	} else if (value > node->value) {
		node->right = deleteNode(node->right, value);
	} else if (value == node->value) {
		if ((node->left != NULL) && (node->right != NULL)) {
			// node의 value를 왼쪽 트리의 최대값으로 치환하고, 최대값을 가졌던 노드를 삭제한다.
			Node* maxNodeOfLeft = findMaxNode(node->left);
			node->value = maxNodeOfLeft->value;
			node->left = deleteNode(node->left, node->value);
		} else if ((node->left == NULL) && (node->right != NULL)) {
			// node를 삭제하고 그 자리를 오른쪽 자식으로 대체한다.
			Node* rightNode = node->right;
			free(node);
			return rightNode;
		} else if ((node->left != NULL) && (node->right == NULL)) {
			// node를 삭제하고 그 자리를 왼쪽 자식으로 대체한다.
			Node* leftNode = node->left;
			free(node);
			return leftNode;
		} else {
			free(node);
			return NULL;
		}
	}
	
	return node;
}
Node* findNode(Node* node, int value) {
	if (node == NULL) {
		printf("%d is not in the tree.\n", value);
		return NULL;
	}
	if (value < node->value) {
		findNode(node->left, value);
	} else if (value > node->value) {
		findNode(node->right, value);
	} else if (value == node->value) {
		printf("%d is in the tree.\n", value);
		return node;
	}
	return NULL;
}
Node* findMaxNode(Node* node){
	if (node == NULL) {
		return NULL;
	} else {
		while (node->right != NULL) {
			node = node->right;
		}
		return node;
	}
}
Node* findMinNode(Node* node){
	if (node == NULL) {
		return NULL;
	} else {
		while (node->left != NULL) {
			node = node->left;
		}
		return node;
	}
}
void printInorder(Node* node) {
	printf("pi - ");
	_printInorderElements(node);
	printf("\n");
}
void printPreorder(Node* node) {
	printf("pr - ");
	_printPreorderElements(node);
	printf("\n");
}
void printPostorder(Node* node) {
	printf("po - ");
	_printPostorderElements(node);
	printf("\n");
}
void _printInorderElements(Node* node) {
	if (node) {
		_printInorderElements(node->left);
		printf("%d ", node->value);
		_printInorderElements(node->right);
	}
}
void _printPreorderElements(Node* node) {
	if (node) {
		printf("%d ", node->value);
		_printPreorderElements(node->left);
		_printPreorderElements(node->right);
	}
}
void _printPostorderElements(Node* node) {
	if (node) {
		_printPostorderElements(node->left);
		_printPostorderElements(node->right);
		printf("%d ", node->value);
	}
}

// 테스트 케이스를 실행하는 함수
void runTestCase() {
	Node* root = createNode(4);
	insertNode(root, 2);
	insertNode(root, 6);
	insertNode(root, 1);
	insertNode(root, 3);
	insertNode(root, 5);
	insertNode(root, 7);
	insertNode(root, 3);
	printInorder(root);
	deleteNode(root, 4);
	deleteNode(root, 2);
	deleteNode(root, 6);
	printInorder(root);
	insertNode(root, 4);
	insertNode(root, 2);
	deleteNode(root, 10);
	printInorder(root);
	printPreorder(root);
	printPostorder(root);
	findNode(root, 4);
	findNode(root, 8);
}

// main 함수
int main(int argc, char *argv[]) {
	Node* root;
	
	FILE* fpInput = fopen("input.txt", "r");
	FILE* fpOutput = freopen("output.txt", "w", stdout); // stdout 스트림 출력을 파일 스트림으로 리다이렉트한다.
	
	while (!feof(fpInput)) {
		char command[3]; // NULL이 들어갈 고려해 크기를 한 칸 더 늘려줘야 한다.
		int number;
		
		fscanf(fpInput, "%s %d", command, &number);
		
		if (!strcmp(command, "i")) {
			root = insertNode(root, number);
		} else if (!strcmp(command, "d")) {
			deleteNodeSafely(root, number);
		} else if (!strcmp(command, "f")) {
			findNode(root, number);
		} else if (!strcmp(command, "pi")) {
			printInorder(root);
		} else if (!strcmp(command, "pr")) {
			printPreorder(root);
		} else if (!strcmp(command, "po")) {
			printPostorder(root);
		}
	}
	
	fclose(fpInput);
	fclose(fpOutput);
	
	return 0;
}