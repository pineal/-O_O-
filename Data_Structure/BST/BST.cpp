#include "BST.h"

BST::BST() {
	root = nullptr;
}

BST::~BST() {
	if (this->root) delete this->root;
}

TreeNode* BST::search(TreeNode* root, int v) {
	if (root == nullptr) {
		return root;
	}
	if (root -> val == v) {
		return root;
	}
	if (v < root -> val) {
		return search(root -> left, v);
	} else {
		return search(root -> right, v);	
	}
}

TreeNode* BST::search(int v) {
	if (this -> root == nullptr) {
		return nullptr;
	}

	TreeNode* cur = this->root;
	while (cur) {
		if (cur -> val == v) {
			return cur;
		}
		else if (cur -> val > v) {
			cur = cur -> left;
		} else {
			cur = cur -> right;	
		}
	}
		return nullptr;
}

void BST::insert(int v) {
	if (this->root == nullptr) {
		this->root = new TreeNode(v);
		return;
	}
	TreeNode* parent = nullptr;
	TreeNode* cur = this -> root;
	while (cur) {
		if (cur -> val > v) {
			parent = cur;
			cur = cur -> left;
		} else {
			parent = cur;
			cur = cur -> right;
		}

		if (parent -> val > v) {
			parent -> left = new TreeNode(v);
		} else {
			parent -> right = new TreeNode(v);
		}
	}
}

void BST::remove(int v) {
		
}
