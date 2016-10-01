#include <stdio.h>
#include <string.h>
#define MAX_LEN 200
int num1[MAX_LEN + 10];
int num2[MAX_LEN + 10];
char buff1[MAX_LEN + 10];
char buff2[MAX_LEN + 10];

int main(int argc, char** argv) {
	strcpy(buff1, argv[1]);
	strcpy(buff2, argv[2]);
	int i, j;
	memset(num1, 0, sizeof(num1));
	memset(num2, 0, sizeof(num2));
	int len1 = strlen(buff1);
	j = 0;
	for (i = len1 - 1; i >= 0; i--) {
		num1[j++] = buff1[i] - '0';
	}
	int len2 = strlen(buff2);
	j = 0;
	for (i = len2 - 1; i>= 0; i--) {
		num2[j++] = buff2[i] - '0';
	}
	for (i = 0; i < MAX_LEN; i++) {
		num1[i] += num2[i];
		if (num1[i] >= 10) {
			num1[i] -= 10;
			num1[i+1]++;
		}	
	}

	bool flag = false;
	for (i = MAX_LEN; i >= 0; i--) {
		if (flag) {
			printf("%d", num1[i]);
		} else if (num1[i]) {
			printf("%d", num1[i]);
			flag = true;
		}
	}
	if (flag == false) {
			printf("%d", 0);
	}
	printf("\n");
	return 0;
}
