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
		printf("���� ����÷ο찡 �߻��߽��ϴ�.\n");
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
// �̷��� ������ ������ �迭�� s��� ��
// ������ �� ���ڿ��� ������ size
char* transition(Stack* stack, char** s, int size) {
	char res[1000] = "";
	// ������ ���� �����ڶ�� �ڱ⺸�� �켱������ ���� �͵��� ���ÿ��� ���� �ڿ� �ڽ��� ���ÿ� ����
	for (int i = 0; i < size; i++) {
		if (!strcmp(s[i], "+") || !strcmp(s[i], "-") || !strcmp(s[i], "*") || !strcmp(s[i], "/")) {
			while (stack->top != NULL && getPriority(getTop(stack)) >= getPriority(s[i])) {
				strcat(res, pop(stack));
				strcat(res, " ");
			}
			push(stack, s[i]);
		}
		// ���� ��ȣ��� �ٷ� ���ÿ� �ֱ�
		else if (!strcmp(s[i], "("))
			push(stack, s[i]);
		// �ݴ� ��ȣ��� ���� ��ȣ�� ���ö����� ���ÿ��� �̾Ƽ� ��� �迭�� ������ ��
		else if (!strcmp(s[i], ")")) {
			while (strcmp(getTop(stack), "(")) {
				strcat(res, pop(stack));
				strcat(res, " ");
			}
			pop(stack);
		}
		// �Ϲ� ������ ��� �ٷ� ���
		else {
			strcat(res, s[i]);
			strcat(res, " ");
		}
	}
	// ���� ���ÿ� ���� �� �ִٸ� �� �����ֱ�
	while (stack->top != NULL) {
		strcat(res, pop(stack));
		strcat(res, " ");
	}
	return res;
}

void calculate(Stack* stack, char** s, int size) {
	int x, y, z;
	for (int i = 0; i < size; i++) {
		// �����ڰ� ������ ��쿡�� ���ÿ��� 2���� �̾Ƽ� �װ��� ���
		if (!strcmp(s[i], "+") || !strcmp(s[i], "-") || !strcmp(s[i], "*") || !strcmp(s[i], "/")) {
			x = atoi(pop(stack));
			y = atoi(pop(stack));
			if (!strcmp(s[i], "+")) z = y + x;
			if (!strcmp(s[i], "-")) z = y - x;
			if (!strcmp(s[i], "*")) z = y * x;
			if (!strcmp(s[i], "/")) z = y / x;
			char buffer[100];
			//sprintf�� ���� ���������� ����� ���ڿ��� �ٲ�
			sprintf(buffer, "%d", z);
			// ����� ����� ���ÿ� ����
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
	// ������ ���ڿ��� ���⸦ �̿��ؼ� ��ū���� �з� 
	char* ptr = strtok(a, " ");
	// ����ǥ��� ���⿡ �ְ����ϴ� �Է°��� ����
	char** input = (char**)malloc(sizeof(char*) * size);
	// ��ū���� �и��� �� ���ڿ��� ����ؼ� input���ٰ� ����
	for (int i = 0; i < size; i++) {
		strcpy(input[i], ptr);
		ptr = strtok(NULL, " ");
	}
	// ����� ���е� ������ ���ڿ� �迭 ���·� input�� ���� ��
	char b[1000] = "";
	// �̸� ���� ����ǥ������� �ٲ㼭 �� ����� b���ٰ� ����
	strcpy(b, transition(&stack, input, size));
	printf("���� ǥ��� : %s\n", b);
	size = 1;
	for (int i = 0; i < strlen(b) - 1; i++) { // �������� �׻� ������ ���Ƿ� 1�� ����
		if (b[i] == ' ')
			size++;
	}
	// �ش� ���� �� ��ū���� ������ �ٽ� input���� �־���
	char* ptr2 = strtok(b, " ");
	for (int i = 0; i < size; i++) {
		strcpy(input[i], ptr2);
		ptr2 = strtok(NULL, " ");
	}
	calculate(&stack, input, size);
	system("pause");
	return 0;
}