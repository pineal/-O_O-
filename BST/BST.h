#ifndef BST_H
#define BST_H
#include "Node.h"

class BST {
	public:
		BST();
		~BST();
		TreeNode* root;
		TreeNode* search(int v);
		TreeNode* search(TreeNode* root, int v);
		TreeNode* search(TreeNode** parent, int v);
		void insert(int v);
		void remove(int v);
		void empty_tree(TreeNode* root);
		void print_tree();
		TreeNode* find_parent(TreeNode* root);
		bool valid_BST();
		bool valid_BST_helper(TreeNode* root, TreeNode** parent);
};

#endif
