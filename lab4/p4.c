#include <stdio.h>

typedef struct Node Node;
struct Node {
	Node* left;
	Node* right;
	int leftIsThread;
	int rightIsThread;
	char data;
};

Node* inorderSuccessor(Node* node) { // node의 중위 후속자(다음 노드)의 포인터를 반환한다.
	// 참고: 중위 탐색에서 후속자는 노드의 오른쪽 자식 또는 오른쪽 자식의 가장 왼쪽 자식이다.
	Node* successor = node->right; // 후속자는 노드의 오른쪽 자식 또는 오른쪽 스레드이다.
	
	if (!node->rightIsThread) { // 노드의 오른쪽이 자식이라면
		// 노드의 오른쪽 자식의 가장 왼쪽 자식으로 타고 내려간다.
		while (!successor->leftIsThread) { // 후속자 변수의 왼쪽이 자식인 동안
			successor = successor->left; // 후속자 변수에 후속자의 왼쪽 자식을 대입한다.
		}
	}
	
	return successor;
}
void traverseInorder(Node* node) { // node를 중위 순회하며 그 값을 출력한다.
	Node* successor = node;
	
	while(1) {
		successor = inorderSuccessor(successor);
		if (successor == node) { break; } // 루트 노드에 도달하면 순회를 종료한다.
		printf("%c ", successor->data);
	}
}

int main(int argc, char *argv[]) {
	// 테스트 케이스 노드를 만든다.
	Node rootNode = {.leftIsThread = 0, .rightIsThread = 0};
	Node nodeA = {.data = 'A', .leftIsThread = 0, .rightIsThread = 0};
	Node nodeB = {.data = 'B', .leftIsThread = 0, .rightIsThread = 0};
	Node nodeC = {.data = 'C', .leftIsThread = 0, .rightIsThread = 0};
	Node nodeD = {.data = 'D', .leftIsThread = 0, .rightIsThread = 0};
	Node nodeE = {.data = 'E', .leftIsThread = 1, .rightIsThread = 1};
	Node nodeF = {.data = 'F', .leftIsThread = 1, .rightIsThread = 1};
	Node nodeG = {.data = 'G', .leftIsThread = 1, .rightIsThread = 1};
	Node nodeH = {.data = 'H', .leftIsThread = 1, .rightIsThread = 1};
	Node nodeI = {.data = 'I', .leftIsThread = 1, .rightIsThread = 1};
	
	rootNode.left = &nodeA;
	rootNode.right = &rootNode;
	
	nodeA.left = &nodeB;
	nodeA.right = &nodeC;
	
	nodeB.left = &nodeD;
	nodeB.right = &nodeE;
	
	nodeC.left = &nodeF;
	nodeC.right = &nodeG;
	
	nodeD.left = &nodeH;
	nodeD.right = &nodeI;
	
	nodeE.left = &nodeB;
	nodeE.right = &nodeA;
	
	nodeF.left = &nodeA;
	nodeF.right = &nodeC;
	
	nodeG.left = &nodeC;
	nodeG.right = &rootNode;
	
	nodeH.left = &rootNode;
	nodeH.right = &nodeD;
	
	nodeI.left = &nodeD;
	nodeI.right = &nodeB;
	
	
	FILE* fpOutput = freopen("output.txt", "w", stdout); // stdout 스트림 출력을 파일 스트림으로 리다이렉트한다.
	
	traverseInorder(&rootNode); // 스레드 이진 트리를 중위 순회한다.
	
	fclose(fpOutput);
	
	return 0;
}