#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_LEN 200
char szLine1[MAX_LEN + 10];
char szLine2[MAX_LEN + 10];
int an1[MAX_LEN + 10];
int an2[MAX_LEN + 10];
int aResult[MAX_LEN + 10];

int Substract(int* p1, int* p2, int nLen1, int nLen2) {
	int i;
	if (nLen1 < nLen2)
		return -1;
	bool bLarger = false;
	if (nLen1 == nLen2) {
		for (i = nLen1 - 1; i >= 0; i--) {
			if (p1[i] > p2[i])
				bLarger = true;
			else if (p1[i] < p2[i]) {
				if (!bLarger)
					return -1;
			}
		}
	}
	for (i = 0; i < nLen1; i++) {
		p1[i] -= p2[i];
		if (p1[i] < 0) {
			p1[i] += 10;
			p1[i + 1]--;
		}
	}
	for (i = nLen1 - 1; i >= 0; i--) {
		if (p1[i])
			return i + 1;
	}
	return 0;
}

int main(void) {
	int t, n;
	scanf("%d", &n);
	for (t = 0; t < n; t++) {
		scanf("%s", szLine1);
		scanf("%s", szLine2);
		int i, j;
		int nLen1 = strlen(szLine1);
		int nLen2 = strlen(szLine2);
		if (nLen1 < nLen2) {
			printf("0\n");
			continue;
		}
		memset(an1, 0, sizeof(an1));
		memset(an2, 0, sizeof(an2));
		memset(aResult, 0, sizeof(aResult));
		j = 0;
		for (i = nLen1 - 1; i >= 0; i--)
			an1[j++] = szLine1[i] - '0';
		j = 0;
		for (i = nLen2 - 1; i >= 0; i--)
			an2[j++] = szLine2[i] - '0';
		nLen1 = Substract(an1, an2, nLen1, nLen2);
		if (nLen1 < 0) {
			printf("0\n");
			continue;
		}
		else if (nLen1 == 0) {
			printf("1\n");
			continue;
		}
		aResult[0]++;
		int nPowers = nLen1 - nLen2;
		if (nPowers < 0)
			goto OutputResult;
		else if (nPowers > 0) {
			for (i = nLen1 - 1; i >= 0; i--) {
				if (i >= nPowers)
					an2[i] = an2[i - nPowers];
				else
					an2[i] = 0;
			}
		}
		nLen2 = nLen1;
		for (j = 0; j <= nPowers; j++) {
			int nTmp;
			while ((nTmp = Substract(an1, an2 + j, nLen1, nLen2 - j)) >= 0) {
				nLen1 = nTmp;
				aResult[nPowers - j]++;
			}
		}
OutputResult:
		for (i = 0; i < MAX_LEN; i++) {
			if (aResult[i] >= 10) {
				aResult[i + 1] += aResult[i] / 10;
				aResult[i] %= 10;
			}
		}
		bool bStartOutput = false;
		for (i = MAX_LEN; i >= 0; i--) {
			if (bStartOutput)
				printf("%d", aResult[i]);
			else if (aResult[i]) {
				printf("%d", aResult[i]);
				bStartOutput = true;
			}
		}
		printf("\n");
	}
	return 0;
}
