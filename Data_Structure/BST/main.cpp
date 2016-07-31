#include "BST.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_cmd(int argc, char** argv) {
	if (argc % 2 == 0) {
	}
	int cursor = 1;
	char* filename = nullptr;
	FILE* file = nullptr;
	while (cursor < argc - 1) {
		if (strcmp(argv[cursor], "-f") == 0){
			filename = argv[cursor+1];
			file = fopen(filename, "r");
			if (file == 0) {
				fprintf(stderr,"%s \n", "Failed to open file");
				exit(1);
			}
		} else if (strcmp(argv[cursor], "-r") == 0) {

		}
	}
}

int main(int argc, char** argv) {
	read_cmd(argc, argv);
	BST* tree = new BST();
	int c;
	while((c = getchar()) != EOF) {
		switch (c) {
			case 'i':
				break;
			case 'p':
				tree->print_tree();
				break;
			case 'q':
				exit(0);
		}
	}
	return 0;
}
