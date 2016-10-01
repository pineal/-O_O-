#include "BST.h"
#include <queue>
#include <iostream>
using namespace std;

BST::BST() {
	root = nullptr;
}

BST::~BST() {
	empty_tree(this->root);
}

void BST::empty_tree(TreeNode* root) {
	if (root) {
		empty_tree(root->left);
		empty_tree(root->right);
		delete(root);
	}
}

TreeNode* BST::search(TreeNode* root, int v) {
	if (root == nullptr) {
		return nullptr;
	}
	if (v < root -> val) {
		return search(root -> left, v);
	} else if (v > root -> val) {
		return search(root -> right, v);	
	} else {
		return root;
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
	//find the target node first

	//case 1: leave node
	//case 2:  
	//has only right child
	//case 3:	
	//has only left child
	//case 4:
	//two children exist for the target
	//find the smallest node of right subtree
	//which is the leftmost node of right child node
	//swap that leftmost node and target node
	//delete target node

	TreeNode* parent = nullptr;
	TreeNode* target = this -> root;
	while (target) {
		if (target->val == v) {
			break;
		} else if (v > target->val) {
			parent = target;
			target = target->right;
		}else{
			parent = target;
			target = target->left;
		}
	}

	if (!target->left && !target->right){
		delete(target);
		return;
	} else if (!target->left) {
		parent->right = target->right;
		delete(target);
		return;
	} else if (!target->right) {
		parent->left = target->left;
		delete(target);
		return;
	} else {
		TreeNode* left_most = target->right;			
		while (left_most->left) {
			left_most = left_most->left;
		}	
		target->val = left_most->val;
		delete(left_most);
		return;	
	} 
}


void BST::print_tree() {
	if (!this->root) return;
	queue<TreeNode*> q;
	q.push(this->root);
	cout<<this->root->val << " ";	
	while (!q.empty()) {
		size_t size = q.size();	
		for (size_t i = 0; i < size; i++) {
			TreeNode* node = q.front();
			q.pop();	
			if (node -> left) {
				cout<<node -> left -> val << " ";	
				q.push(node->left);			
			} else {
				cout<<"# ";	
			} 
			if (node -> right) {
				q.push(node->left);			
			} else {
				cout<<"# ";	
			} 
		}
	}
}

bool BST::valid_BST() {
	TreeNode* prev = nullptr;
	return valid_BST_helper(this->root, &prev);
}
bool BST::valid_BST_helper(TreeNode* root, TreeNode** prev) {
	if (root == nullptr) {
		return true;
	}
	prev = &root;
	valid_BST_helper(root->left, prev);
	valid_BST_helper(root->right, prev);
	return false;
}



