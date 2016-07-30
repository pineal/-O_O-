#ifndef BST_H
#define BST_H
#include "Node.h"

class BST {
	public:
		TreeNode* root;
		BST();
		~BST();
		TreeNode* search(int v);
		TreeNode* search(TreeNode* root, int v);
		void insert(int v);
		void remove(int v);
};

#endif
