#include <stdio.h>
#include <string.h>
#define MAX_LEN 200
char buff1[MAX_LEN + 10];
char buff2[MAX_LEN + 10];
unsigned int num1[MAX_LEN + 10];
unsigned int num22[MAX_LEN + 10];
unsigned int result[MAX_LEN + 10];

int subtract(int* p1, int* p2, int len1, int len2) {
	int i;
	if (len1 < len2) {
		return -1;
	}

	bool bLarger = false;
	if (len1 == len2) {
		for (i = len1 - 1; i >= 0; i--) {
			if (p1[i] > p2[i]) {
				bLarger = true;
			} else if (p1[i] < p2[i]) {
				if (!bLarger) {
					return -1;	
				}
			}
		}
	}

	for (i = 0; i < len1; i++) {
		p1[i] -= p2[i];
		if (p1[i] < 0) {
			p1[i] += 10;
			p1[i+1]--;
		}
	}	
		for (i = len1 - 1; i >= 0; i--) {
			if (p1[i]) {
				return i + 1;
			}
		}

	return 0;	
}

int main(int argc, char** argv) {
	int t, n;

	return 0;
}
