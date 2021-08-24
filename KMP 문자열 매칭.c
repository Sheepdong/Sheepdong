#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* parent = "ABCDEFG";
char* pattern = "EF";

int main(void) {
	int parentSize = strlen(parent);
	int patternSize = strlen(pattern);
	for (int i = 0; i <= parentSize - patternSize; i++) {
		int found = 1;
		for (int j = 0; j < patternSize; j++) {
			if (parent[i + j] != pattern[j]) { found = 0; break; }
		}
		if (found) {
			printf("%d번째에서 찾았습니다.\n", i + 1);
		}
	}
	system("pause");
}

// 단순 문자열 매칭

char* parent = "acabacdabac";
char* pattern "abacdab";

int* makeTable(char* pattern) {
	int patternSize = strlen(pattern);
	int* table = (int*)malloc(sizeof(int) * patternSize);
	for (int i = 0; i < patternSize; i++) {
		table[i] = 0;
	}
	int j = 0;
	for (int i = 1; i < patternSize; i++) {
		while (j > 0 && pattern[i] != pattern[j]) {
			j = table[j - 1];
		}
		if (pattern[i] == pattern[j]) {
			table[i] = ++J;
		}
	}
	return table;
}

void KMP(char* parent, char* pattern) {
	int* table = makeTable(pattern);
	int parentSize = strlen(parent);
	int patternSize = strlen(pattern);
	int j = 0;
	for (int i = 0; i < parentSize; i++) {
		while (j > 0 && parent[i] != pattern[j]) {
			j = table[j - 1];
		}
		if (parent[i] == pattern[j]) {
			if (j == patternSize - 1) {
				printf("[인덱스 %d]에서 매칭 성공\n", i - patternSize + 2);
				j = table[j];
			}
			else {
				j++;
			}
		}
	}
}

int main(void) {
	KMP(parent, pattern);
	system("pause");
}

// KMP 문자열 매칭