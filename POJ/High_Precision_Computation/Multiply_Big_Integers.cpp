#include <stdio.h>
#include <string.h>
#define MAX_LEN 200
unsigned num1[MAX_LEN + 10];
unsigned num2[MAX_LEN + 10];
unsigned result[MAX_LEN * 2 + 10];
char buff1[MAX_LEN];
char buff2[MAX_LEN];

int main(int argc, char** argv) {
	strcpy(buff1, argv[1]);
	strcpy(buff2, argv[2]);
	int i, j;
	memset(num1, 0, sizeof(num1));
	memset(num2, 0, sizeof(num2));
	memset(result, 0, sizeof(result));
	j = 0;
	int len1 = strlen(buff1);
	int len2 = strlen(buff2);

	for (i = len1 - 1; i >= 0; i--) {
		num1[j++] = buff1[i] - '0';	
	}
	j = 0;
	for (i = len2 - 1; i >= 0; i--) {
		num2[j++] = buff2[i] - '0';
	}
	for (i = 0; i < len2; i++) {
		for (j = 0; j < len1; j++) {
			result[i + j] += num1[j] * num2[i];
		}
	}
	for (i = 0; i < MAX_LEN * 2; i++) {
		if (result[i] >= 10) {
			result[i+1] += result[i] / 10;
			result[i] %= 10;
		}
	}	
	bool flag = false;
	for (i = MAX_LEN * 2; i >= 0; i--) {
		if (flag) {
			printf("%d", result[i]);
		} else if (result[i]) {
			printf("%d", result[i]);
			flag = true;	
		}
	}

	if (!flag) {
		printf("0");
	}
		printf("\n");
	return 0;
}
