#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct Node {
	char data[100];
	struct Node* next;
}Node;

typedef struct Stack {
	Node* top;
}Stack;

void push(Stack* stack, char* data) {
	Node* node = (Node*)malloc(sizeof(Node));
	strcpy(node->data, data);
	node->next = stack->top;
	stack->top = node;
}

char getTop(Stack* stack) {
	Node* top = stack->top;
	return top->data;
}

char pop(Stack* stack) {
	if (stack->top == NULL) {
		printf("스택 언더플로우가 발생했습니다.\n");
		return NULL;
	}
	Node* node = stack->top;
	char* data = (char*)malloc(sizeof(char) * 100);
	strcpy(data, node->data);
	stack->top = node->next;
	free(node);
	return data;
}

int getPriority(char* i) {
	if (!strcmp(i, "(")) return 0;
	if (!strcmp(i, "+") || !strcmp(i, "-")) return 1;
	if (!strcmp(i, "*") || !strcmp(i, "/")) return 2;
	return 3;
}

// 37 + 5
// "37" "+" "5"
// 이렇게 나뉘어 들어오는 배열을 s라고 함
// 들어오는 각 문자열의 개수를 size
char* transition(Stack* stack, char** s, int size) {
	char res[1000] = "";
	// 들어오는 값이 연산자라면 자기보다 우선순위가 높은 것들을 스택에서 뽑은 뒤에 자신을 스택에 넣음
	for (int i = 0; i < size; i++) {
		if (!strcmp(s[i], "+") || !strcmp(s[i], "-") || !strcmp(s[i], "*") || !strcmp(s[i], "/")) {
			while (stack->top != NULL && getPriority(getTop(stack)) >= getPriority(s[i])) {
				strcat(res, pop(stack));
				strcat(res, " ");
			}
			push(stack, s[i]);
		}
		// 여는 괄호라면 바로 스택에 넣기
		else if (!strcmp(s[i], "("))
			push(stack, s[i]);
		// 닫는 괄호라면 여는 괄호가 나올때까지 스택에서 뽑아서 결과 배열에 담으면 됨
		else if (!strcmp(s[i], ")")) {
			while (strcmp(getTop(stack), "(")) {
				strcat(res, pop(stack));
				strcat(res, " ");
			}
			pop(stack);
		}
		// 일반 숫자인 경우 바로 출력
		else {
			strcat(res, s[i]);
			strcat(res, " ");
		}
	}
	// 이후 스택에 남은 게 있다면 다 꺼내주기
	while (stack->top != NULL) {
		strcat(res, pop(stack));
		strcat(res, " ");
	}
	return res;
}

void calculate(Stack* stack, char** s, int size) {
	int x, y, z;
	for (int i = 0; i < size; i++) {
		// 연산자가 나오는 경우에는 스택에서 2개를 뽑아서 그것을 계산
		if (!strcmp(s[i], "+") || !strcmp(s[i], "-") || !strcmp(s[i], "*") || !strcmp(s[i], "/")) {
			x = atoi(pop(stack));
			y = atoi(pop(stack));
			if (!strcmp(s[i], "+")) z = y + x;
			if (!strcmp(s[i], "-")) z = y - x;
			if (!strcmp(s[i], "*")) z = y * x;
			if (!strcmp(s[i], "/")) z = y / x;
			char buffer[100];
			//sprintf는 계산된 숫자형태의 결과를 문자열로 바꿈
			sprintf(buffer, "%d", z);
			// 계산한 결과를 스택에 넣음
			push(stack, buffer);
		}
		else {
			push(stack, s[i]);
		}
	}
	printf("%s\n", pop(stack));
}

int main(void) {
	Stack stack;
	stack.top = NULL;
	char a[100] = "( ( 3 + 4 ) * 5 ) - 5 * 7  * 5 - 5 * 10";
	int size = 1;
	for (int i = 0; i < strlen(a); i++) {
		if a[i] == ' '
			size++;
	}
	// 각각의 문자열을 띄어쓰기를 이용해서 토큰으로 분류 
	char* ptr = strtok(a, " ");
	// 후위표기법 계산기에 넣고자하는 입력값을 마련
	char** input = (char**)malloc(sizeof(char*) * size);
	// 토큰으로 분리된 각 문자열을 계속해서 input에다가 넣음
	for (int i = 0; i < size; i++) {
		strcpy(input[i], ptr);
		ptr = strtok(NULL, " ");
	}
	// 띄어쓰기로 구분된 각각의 문자열 배열 형태로 input에 담기게 됨
	char b[1000] = "";
	// 이를 이제 후위표기법으로 바꿔서 그 결과를 b에다가 담음
	strcpy(b, transition(&stack, input, size));
	printf("후위 표기법 : %s\n", b);
	size = 1;
	for (int i = 0; i < strlen(b) - 1; i++) { // 마지막은 항상 공백이 들어가므로 1을 빼줌
		if (b[i] == ' ')
			size++;
	}
	// 해당 식을 또 토큰으로 나눠서 다시 input으로 넣어줌
	char* ptr2 = strtok(b, " ");
	for (int i = 0; i < size; i++) {
		strcpy(input[i], ptr2);
		ptr2 = strtok(NULL, " ");
	}
	calculate(&stack, input, size);
	system("pause");
	return 0;
}