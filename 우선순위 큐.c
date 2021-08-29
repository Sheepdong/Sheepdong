#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 10000

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

typedef struct {
	int heap[MAX_SIZE];
	// heap에 들어있는 원소의 개수 count
	int count;
} priorityQueue;

void push(priorityQueue* pq, int data) {
	if (pq->count >= MAX_SIZE) return;
	pq->heap[pq->count] = data;
	// 항상 마지막 원소에 data 삽입
	int now = pq->count;
	// 완전이진트리에서 부모의 index는 자식의 index에서 1을 빼고 2로 나눈 몫임
	int parent = (pq->count - 1) / 2;
	// 새 원소를 삽입한 이후에 상향식으로 힙을 구성
	while (now > 0 && pq->heap[now] > pq->heap[parent]) {
		// 부모보다 현재 값이 더 크다면 바꿔줌
		swap(&pq->heap[now], &pq->heap[parent]);
		// 그 다음은 계속 반복
		now = parent;
		parent = (parent - 1) / 2;
	}
	pq->count++;
}

int pop(priorityqQueue* pq) {
	if (pq->count <= 0) return -9999;
	// 추출할 원소가 없다면 -9999 출력 
	int res = pq->heap[0];
	pq->count--;
	pq->heap[0] = pq->heap[pq->count];
	// 가장 마지막 원소를 루트노드로 옮기기
	int now = 0, leftChile = 1, rightChild = 2;
	int target = now;
	// target은 바꾸고자 하는 자식 노드 
	// 새 원소를 추출한 이후에 하향식으로 힙 구성
	while (leftChile < pq->count) {
		// 원소가 존재할 때까지만 반복
		if (pq->heap[target] < pq->heap[leftChild]) target = leftChild;
		if (pq->heap[target] < pq->heap[rightChile] && rightChile < pq->count) target = rightChild;
		if (target == now) break; // 다 끝났을 때는 반복문 탈출
		else {
			swap(&pq->heap[now], &pq->heap[target]);
			now = target;
			leftChild = now * 2 + 1;
			rightChild = now * 2 + 2;
		}
	}
	return res;
}

int main(void) {
	int n, data;
	scanf("%d", &n);
	priorityQueue pq;
	pq.count = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &data);
		push(&pq, data);
	}
	for (int i = 0; i < n; i++) {
		int data = pop(&pq);
		printf("%d ", data);
	}
	system("pause");
	return 0;
}