
using namespace std;
#include <vector.h>

class TrieNode{
		public:
			bool isword;
			vector<TrieNode*> children;
			TrieNode() : isword(false) 
			{
				children.resize(26);
			}
};

class TrieTree {
	public:
		TrieTree(); 
		~TrieTree(); 
		void insert(const string & word);
		bool search(string word);
private:
		TrieNode* root;
};



TrieTree::insert(string word) {


}