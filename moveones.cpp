#include <stdlib.h>
#include <iostream>
using namespace std;

void moveone(int *array, int len) {
	int slow = 0;
	int fast = 0;
	while (fast < len) {
		if (*(array + fast) == 1) {
			fast++;
		} else {
			array[slow++] = array[fast++];
		}
	}
	while (slow < len) {
		array[slow++] = 1;
	}
}

void moveone2(int *array, int len) {
	int last = 0;
	int cur = 0;
	while (cur < len) {
		if (array[cur] != 1) {
			swap(array[last++], array[cur]);
		}
		cur++;
	}
}

void printarray(int *array, int len) {
	for (int i = 0; i < len; i++) {
		cout<<array[i];
	}
	cout<<endl;
}

void test(int *array, int len) {
	printarray(array, len);
	moveone2(array, len);
	printarray(array, len);
}
int main(int argc, char *argv[]) {
	int a1[10] = {2,1,3,1,6,5,4,1,4,1};		
	test(a1, 10);
	int a2[1] = {1};		
	test(a2, 1);
	int a3[1] = {2};		
	test(a3, 1);
}
