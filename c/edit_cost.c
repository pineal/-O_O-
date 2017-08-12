#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define INF 3000
using namespace std;
int de[2010][2010], ae[2010][2010], ne[2010][2010];
char s1[2010], s2[2010];
int main() {
	int n, l1, l2;
	char c;
	scanf("%d%c", &n, &c);
	while (n--) {
		char* tmp = s1;
		char c;
		while ((scanf("%c", &c) != EOF) && c != '\n')*(tmp++) = c;
		*tmp = '\0';
		tmp = s2;
		while ((scanf("%c", &c) != EOF) && c != '\n')*(tmp++) = c;
		*tmp = '\0';
		l1 = strlen(s1);
		l2 = strlen(s2);
		for (int i = 0; i <= l1; i++) {
			de[0][i] = 2; ae[0][i] = ne[0][i] = INF;
		}
		for (int i = 0; i <= l2; i++) {
			ae[i][0] = i + 2; de[i][0] = ne[i][0] = INF;
		}
		ne[0][0] = 0;
		for (int j = 1; j <= l2; j++)
			for (int i = 1; i <= l1; i++) {
				ne[j][i] = s1[i - 1] == s2[j - 1] ? min(min(ne[j-1][i-1], ae[j-1][i-1]), de[j-1][i-1]) : INF;
				ae[j][i] = de[j][i] = INF;
				for (int k = 1; k <= j; k++)
					ae[j][i] = min(ae[j][i], min(ae[j - k][i] + k, min(de[j - k][i] + k + 2, ne[j - k][i] + k + 2)));
				for (int k = 1; k <= i; k++)
					de[j][i] = min(de[j][i], min(de[j][i - k], min(ae[j][i - k] + 2, ne[j][i - k] + 2)));
			}
		printf("%d\n", min(min(ne[l2][l1], ae[l2][l1]), de[l2][l1]));
	}
	return 0;
}
