#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h" // lab3-1에서 만든 스택 구조체를 헤더 파일로 분리하여 include했다.

#define MAX_EXP_LEN 100 // 표현식의 최대 길이

// 계산기 관련 함수들의 프로토타입 선언
void convertToPostfixExp(char* infixExp, char* postfixExp); // infixExp를 중위 표기법에서 후위 표기법으로 변환해 postfixExp에 담는다.
int calculatePostfixExp(char* postfixExp); // 후위 표기법으로 표현된 postfixExp를 계산해 결과값을 반환한다.

// 계산기 관련 내부 함수들의 프로토타입 선언
void _outputUntilSpecificOperatorIsTop(Stack* stack, char* postfixExp, const char* operators); // operators 문자열에 포함된 연산자가 stack의 윗 요소가 될 때까지 스택의 연산자들을 팝한 다음 postfixExp에 출력한다.
void _outputAllOperators(Stack* stack, char* postfixExp); // stack의 모든 연산자들을 팝한 다음 postfixExp에 출력한다.
void _appendCharToString(char* string, char c); // 문자열 string에 문자 c를 덧붙인다.
int _calculateTopTwoOperands(Stack* stack, char operator); // stack에서 두 개의 피연산자를 팝해 operator로 계산한 결과값을 반환한다.

// 계산기 관련 함수들의 정의
void convertToPostfixExp(char* infixExp, char* postfixExp) {
	Stack* stack = createStack(MAX_EXP_LEN); // calculatePostfixExp 함수에서 두 자리가 넘는 10진수들의 연산이 필요하기에 int를 요소로 하는 stack을 사용했다.
	
	for (int i = 0; i < strlen(infixExp); i++) {
		char c = infixExp[i];
		switch (c) {
			case '0' ... '9': { // GCC에서만 지원하는 Case Range 표현
				_appendCharToString(postfixExp, c);
				break;
			}
			case '*':
			case '/':
			case '%': {
				_outputUntilSpecificOperatorIsTop(stack, postfixExp, "+-()");
				push(stack, c);
				break;
			}
			case '+':
			case '-': {
				_outputUntilSpecificOperatorIsTop(stack, postfixExp, "()");
				push(stack, c);
				break;
			}
			case '(': {
				push(stack, c);
				break;
			}
			case ')': {
				_outputUntilSpecificOperatorIsTop(stack, postfixExp, "(");
				pop(stack);
				break;
			}
		}
	}
	
	_outputAllOperators(stack, postfixExp);
	return;
}
int calculatePostfixExp(char* postfixExp) {
	Stack* stack = createStack(MAX_EXP_LEN);
	
	for (int i = 0; i < strlen(postfixExp); i++) {
		char c = postfixExp[i];
		switch (c) {
			case '0' ... '9': { // GCC에서만 지원하는 Case Range 표현
				int operand = c - '0'; // 10진수의 연산이 필요하므로 문자로 표현된 10진수를 ASCII 코드값을 이용해 int형으로 변환한다.
				push(stack, operand);
				break;
			}
			case '*':
			case '/':
			case '%':
			case '+':
			case '-': {
				int result = _calculateTopTwoOperands(stack, c);
				push(stack, result);
				break;
			}
		}
	}
	
	return top(stack);
}

// 계산기 관련 내부 함수들의 정의
void _outputUntilSpecificOperatorIsTop(Stack* stack, char* postfixExp, const char* operators) {
	while(!isEmpty(stack)) {
		char topOperator = top(stack);
		if (strpbrk(&topOperator, operators)) {
			break;
		} else {
			pop(stack);
			_appendCharToString(postfixExp, topOperator);
		}
	}
}
void _outputAllOperators(Stack* stack, char* postfixExp) {
	_outputUntilSpecificOperatorIsTop(stack, postfixExp, "");
}
void _appendCharToString(char* string, char c) {
	string[strlen(string)] = c;
}
int _calculateTopTwoOperands(Stack* stack, char operator) {
	// 나눗셈, 뺄셈, 모듈러 연산에서는 피연산자의 순서가 바뀌면 안 되므로 주의한다.
	// 첫 번째로 팝한 피연산자가 뒤에, 두 번째로 팝한 피연산자가 앞에 와야 한다.
	int latterOperand = top(stack); pop(stack);
	int formerOperand = top(stack); pop(stack);
	
	switch (operator) {
		case '*': return formerOperand * latterOperand; break;
		case '/': return formerOperand / latterOperand; break;
		case '%': return formerOperand % latterOperand; break;
		case '+': return formerOperand + latterOperand; break;
		case '-': return formerOperand - latterOperand; break;
	}
}

// main 함수
int main(int argc, char *argv[]) {
	FILE* fpInput = fopen("input.txt", "r");
	FILE* fpOutput = fopen("output.txt", "w");
	
	char infixExp[MAX_EXP_LEN] = "";
	char postfixExp[MAX_EXP_LEN] = "";
	fscanf(fpInput, "%[^#]s", &infixExp); // '#'이 나오기 전까지의 문자열을 읽어들여 infixExp에 담는다.
	
	convertToPostfixExp(infixExp, postfixExp);
	int result = calculatePostfixExp(postfixExp);
	
	fprintf(fpOutput, "Infix Form : %s\n", infixExp);
	fprintf(fpOutput, "Postfix Form : %s\n", postfixExp);
	fprintf(fpOutput, "Evaluation Result : %d\n", result);
	
	fclose(fpInput);
	fclose(fpOutput);
	
	return 0;
}