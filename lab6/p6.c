#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct Node Node;
struct Node {
	Node* left;
	Node* right;
	int height;
	int value;
};

Node* createNode(int value);
Node* insertNode(Node* node, int value);
Node* rotateLeft(Node* prevRoot);
Node* rotateRight(Node* prevRoot);
Node* rotateLeftDouble(Node* prevRoot);
Node* rotateRightDouble(Node* prevRoot);
int height(Node* node);

void printInorder(Node* node);
void _printInorderElements(Node* node);

Node* createNode(int value) {
	Node* node = malloc(sizeof(Node));
	node->left = node->right = NULL;
	node->height = 0;
	node->value = value;
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
		printf("%d already in the tree!\n", value);
	}
	
	node->height = MAX(height(node->left), height(node->right)) + 1;
	
	int balance = height(node->left) - height(node->right); 
	
	if (balance > 1) {
		if (value < node->left->value) {
			node = rotateRight(node);
		} else if (value > node->left->value) {
			node = rotateLeftDouble(node);
		}
	} else if (balance < -1) {
		if (value > node->right->value) {
			return rotateLeft(node);
		} else if (value < node->right->value) {
			return rotateRightDouble(node);
		}
	}
	
	return node;
}
Node* rotateLeft(Node* prevRoot) {
	Node* newRoot = prevRoot->right;
	Node* rightOfPrevRoot = newRoot->left;
	
	newRoot->left = prevRoot;
	prevRoot->right = rightOfPrevRoot;
	
	prevRoot->height = MAX(height(prevRoot->left), height(prevRoot->right)) + 1;
	newRoot->height = MAX(height(newRoot->left), height(newRoot->right)) + 1;
	
	return newRoot;
}
Node* rotateRight(Node* prevRoot) {
	Node* newRoot = prevRoot->left;
	Node* leftOfPrevRoot = newRoot->right;
	
	newRoot->right = prevRoot;
	prevRoot->left = leftOfPrevRoot;
	
	prevRoot->height = MAX(height(prevRoot->left), height(prevRoot->right)) + 1;
	newRoot->height = MAX(height(newRoot->left), height(newRoot->right)) + 1;
	
	return newRoot;
}
Node* rotateLeftDouble(Node* prevRoot) {
	prevRoot->left = rotateLeft(prevRoot->left);
	return rotateRight(prevRoot);
}
Node* rotateRightDouble(Node* prevRoot) {
	prevRoot->right = rotateRight(prevRoot->right);
	return rotateLeft(prevRoot);
}
int height(Node* node) {
	if (node == NULL) {
		return -1;
	} else {
		return node->height;
	}
}
void printInorder(Node* node) {
	_printInorderElements(node);
	printf("\n");
}
void _printInorderElements(Node* node) {
	if (node) {
		_printInorderElements(node->left);
		printf("%d(%d) ", node->value, node->height);
		_printInorderElements(node->right);
	}
}


void runTestCase() {
	Node* root;
	// AVL 정렬 중 최상단 루트 노드가 변경될 가능성이 있기 때문에 매번 insertNode()의 결과값을 root에 대입해야 한다.
	root = insertNode(root, 7); printInorder(root);
	root = insertNode(root, 5); printInorder(root);
	root = insertNode(root, 3); printInorder(root);
	root = insertNode(root, 10); printInorder(root);
	root = insertNode(root, 23); printInorder(root);
	root = insertNode(root, 4); printInorder(root);
	root = insertNode(root, 20); printInorder(root);
	root = insertNode(root, 21); printInorder(root);
	root = insertNode(root, 22); printInorder(root);
	root = insertNode(root, 23); printInorder(root);
	root = insertNode(root, 24); printInorder(root);
	root = insertNode(root, 25); printInorder(root);
}

int main(int argc, char *argv[]) {
	Node* root;
		
	FILE* fpInput = fopen("input.txt", "r");
	FILE* fpOutput = freopen("output.txt", "w", stdout); // stdout 스트림 출력을 파일 스트림으로 리다이렉트한다.
	
	while (!feof(fpInput)) {
		int value;
		
		fscanf(fpInput, "%d", &value);
		
		root = insertNode(root, value);
		printInorder(root);
	}
	
	fclose(fpInput);
	fclose(fpOutput);
	
	return 0;
}