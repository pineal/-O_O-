#include <stdio.h>
#include <iostream>
#include <stack>
using namespace std;

class TreeNode {
	public:
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int val) {
			this -> val = val;
			this -> left = nullptr;
			this -> right = nullptr;
		}
};

class Iterator {
	public:
		virtual TreeNode* next() = 0;
};

class PreorderIterator : public Iterator {
	private:
		stack<TreeNode*> s;
	public:
		PreorderIterator(TreeNode* root) {
			if (root) {
				s.push(root);
			}
		}
		virtual TreeNode* next() {
			if (s.empty()) {
				return nullptr;
			}
			TreeNode* node = s.top();
			s.pop();

			if (node -> right) {
				s.push(node -> right);
			}

			if (node -> left) {
				s.push(node -> left);
			}

			return node;
		}
};

class InorderIterator : public Iterator {
	private:
		stack<TreeNode*> s;
	public:
		InorderIterator (TreeNode* root) {
			while (root) {
				s.push(root);
				root = root -> left;
			}
		}

		virtual TreeNode* next() {
			if (s.empty()) {
				return nullptr;
			}

			TreeNode* parent = s.top();
			s.pop();
			TreeNode* cur = parent -> right;
			while (cur) {
				s.push(cur);
				cur = cur -> left;
			}
			return parent;
		}
};

class PostorderIterator : public Iterator {
	private:
		stack<TreeNode*> s;
	public:
		PostorderIterator (TreeNode* root) {
			while (root) {
				s.push(root);
				root = root -> left;
			}
		}
		virtual TreeNode* next() {
			if (s.empty()) {
				return nullptr;
			}

			TreeNode* parent = s.top();
			s.pop();
			TreeNode* cur = parent -> right;
			//TODO: NOT IMPLEMENTATED YET
			return parent;
		}
};




int main(int argc, const char * argv[]) {
	TreeNode* n0 = new TreeNode(0);
	TreeNode* n1 = new TreeNode(1);
	TreeNode* n2 = new TreeNode(2);
	TreeNode* n3 = new TreeNode(3);
	TreeNode* n4 = new TreeNode(4);
	TreeNode* n5 = new TreeNode(5);
	TreeNode* n6 = new TreeNode(6);
	TreeNode* n7 = new TreeNode(7);
	TreeNode* n8 = new TreeNode(8);
	n0 -> left = n1;
	n0 -> right = n2;
	n1 -> left = n3;
	n1 -> right = n5;
	n3 -> right = n4;
	n2 -> left = n6;
	n2 -> right = n7;
	n6 -> left = n8;
	PreorderIterator iter(n0);
	TreeNode* cur = iter.next();
	while (cur) {
		cout << cur -> val << endl;
		cur = iter.next();
	}
	return 0;
}
