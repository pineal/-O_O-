/*
	* http://www.geeksforgeeks.org/find-paths-given-source-destination/
	* Print all paths from a given source to a destination
	*/
#include <set>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Node {
	public:
		char val;
		set<Node*> neighbors;
		Node(char val) {
			this -> val = val;
		}
};

class Graph {
	public:
		Node* source;
		Node* destination;
		Node* nodes[26];
		Graph() {
			cout<<"constructor"<<endl;
		}
		Graph(const vector<string> & input) {
			graph_builder(input);
		}
		void graph_builder(const vector<string> & input);
		void print_graph();
		vector<string> find_path();
		void helper_dfs(Node* cur_node, vector<Node*> & cur_path, vector<vector<Node*>> & paths, set<Node*> & visited);
};

void
Graph::graph_builder(const vector<string> & input) {
	if (input.size() == 0) {
		cout<<"Err: input format";
		exit(0);
	}
	nodes[toupper(input[0][0]) - 'A'] = new Node(toupper(input[0][0]));
	source = nodes[toupper(input[0][0]) - 'A'];
	nodes[toupper(input[0][2]) - 'A'] = new Node(toupper(input[0][2]));
	destination = nodes[toupper(input[0][2]) - 'A'];

	for (int i = 1; i < input.size(); i++) {
		string cur_line = input[i];
		mark this line's parent node
			Node* p_node = nullptr;
		for (int j = 0; j < cur_line.size(); j++) {
			//skip all non-chars
			char c = toupper(cur_line[j]);
			if (!isalpha(c)) {
				continue;
			}
			//add parent node
			if (j == 0) {
				if (nodes[c - 'A'] == nullptr) {
					nodes[c - 'A'] = new Node(c);
				}
				p_node = nodes[c - 'A'];
				//add its neighbors
			} else {
				//add new nodes if never appear
				if (nodes[c - 'A'] == nullptr) {
					nodes[c - 'A'] = new Node(c);
					p_node->neighbors.emplace(nodes[c - 'A']);
				} else {
					//find this node
					Node* cur_node = nodes[c - 'A'];
					//add to parent's neighbors
					p_node->neighbors.emplace(cur_node);

				}

			}
		}
	}
}

void
Graph::print_graph() {
	for (int i = 0; i < 26; i++) {
		if (nodes[i]) {
			cout << nodes[i]->val<<" - ";
			for (Node* x : nodes[i]->neighbors) {
				cout << x->val;
			}
			cout<<endl;
		}
	}
}

vector<string>
Graph::find_path() {
	vector<Node*> path = {source};
	vector<vector<Node*>> paths;
	set<Node*> visited = {source};
	helper_dfs(source, path, paths, visited);
	vector<string> rst;
	for (auto path : paths) {
		string p;
		for (auto n : path) {
			p+= n -> val;
		}
		cout<<p<< endl;
	}
	return rst;
}

void
Graph::helper_dfs(Node* cur_node, vector<Node*> & cur_path, vector<vector<Node*>> & paths, set<Node*> & visited) {
	if (cur_node == destination) {
		paths.emplace_back(cur_path);
		return;
	}

	for (auto x : cur_node->neighbors) {
		if (visited.find(x) != visited.end()) {
			continue;
		}
		visited.emplace(x);
		cur_path.emplace_back(x);
		helper_dfs(x, cur_path, paths, visited);
		visited.erase(x);
		cur_path.pop_back();
	}
}

int main(int argc, const char * argv[]) {
	vector<string> input;
	input.emplace_back("A J");
	input.emplace_back("A : B C");
	input.emplace_back("B : C E G");
	input.emplace_back("C : A F");
	input.emplace_back("D : C J");
	input.emplace_back("F : B H");
	input.emplace_back("G : C D");
	input.emplace_back("H : A B F I");
	input.emplace_back("I : B");
	Graph g(input);
	//g.print_graph();
	g.find_path();
	return 0;
}

