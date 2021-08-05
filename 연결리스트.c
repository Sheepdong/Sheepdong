#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int data;
	struct Node* next;
} Node;

Node* head;

int main(void) {
	head = (Node*)malloc(sizeof(Node));
	Node* node1 = (Node*)malloc(sizeof(Node));
	node1->data = 1;
	Node* node2 = (Node*)malloc(sizeof(Node));
	node2->data = 2;
	head->next = node1;
	node1->next = node2;
	node2->next = NULL;
	Node* cur = head->next;
	while (cur != NULL) {
		printf("%d ", cur->data);
		cur = cur->next;
	}
	system("pause");
	return 0;

}

void addFront(Node* root, int data) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = root->next;
	root->next = node;
}

void removeFront(Node* root) {
	Node* front = root->next;
	root->next = front->next;
	free(front);
}

void freeAll(Node* root) {
	Node* cur = head->next;
	while (cur != NULL) {
		Node* next = cur->next;
		free(cur);
		cur = next;
	}
}

void showAll(Node* root) {
	Node* cur = head->next;
	while (cur != NULL) {
		printf("%d", cur->data);
		cur = cur->next;
	}
}

int main(void) {
	head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	addFront(head, 2);
	addFront(head, 1);
	addFront(head, 7);
	addFront(head, 9);
	addFront(head, 8);
	removeFront(head);
	showAll(head);
	freeAll(head);
	system("pause");
	return 0;
}