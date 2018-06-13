#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <stack> 
#include <iostream> 

using namespace std;

class Graph {
private:
	int size;
	unordered_map<int, list<int>> neighbors;
	void fillOrder(int v, unordered_set<int> & visited, stack<int> & st);
	void dfs(int v, unordered_set<int> & visited);
public:
	Graph(int size);
	void addEdge(int start, int end);
	void printSCC();
	Graph getReverse();
	bool isSC();
};

Graph::Graph(int size) {
	this->size = size;
	neighbors.clear();
}


void Graph::dfs(int v, unordered_set<int> & visited) {
	visited.emplace(v);
	cout << v << " ";
	for (auto iter = neighbors[v].begin(); iter != neighbors[v].end(); iter++) {
		if (!visited.count(*iter)) {
			dfs(*iter, visited);
		}
	}
}


Graph Graph::getReverse() {
	Graph g(size);
	for (int v = 0; v < size; v++) {
		for (auto iter = neighbors[v].begin(); iter != neighbors[v].end(); iter++) {
			g.neighbors[*iter].push_back(v);
		}
	}
	return g;
}

void Graph::addEdge(int start, int end) {
	neighbors[start].push_back(end);
}

void Graph::fillOrder(int v, unordered_set<int> & visited, stack<int> & st) {
	visited.emplace(v);
	for (auto iter = neighbors[v].begin(); iter != neighbors[v].end(); iter++) {
		if (!visited.count(*iter)) {
			fillOrder(*iter, visited, st);
		}
	}
	st.push(v);
}

void Graph::printSCC() {
	stack<int> st;
	unordered_set<int> visited;

	// first time dfs push into stack
	for (int i = 0; i < size; i++) {
		if (visited.count(i) == 0) {
			fillOrder(i, visited, st);
		}
	}

	Graph reverse = getReverse();

	// second time dfs on reversed one start popping from stack
	visited.clear();
	while (!st.empty()) {
		int v = st.top();
		st.pop();
		
		if (visited.count(v) == 0) {
			reverse.dfs(v, visited);
			cout << endl;
		}
	}
}

bool Graph::isSC() {
	unordered_set<int> visited;
	dfs(0, visited);
	for (int i = 0; i < size; i++) {
		if (visited.count(i) == 0) {
			return false;
		}
	}
	Graph reverse = getReverse();
	visited.clear();
	reverse.dfs(0, visited);

	for (int i = 0; i < size; i++) {
		if (visited.count(i) == 0) {
			return false;
		}
	}
	return true;
}

int main() {
	    // Create a graph given in the above diagram
    Graph g(5);
    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(0, 3);
		g.addEdge(3, 4);
		g.isSC()? cout << "Yes\n" : cout << "No\n";
		cout << "Following are strongly connected components in "
			"given graph \n";
		g.printSCC();

		    // Create graphs given in the above diagrams
    Graph g1(5);
    g1.addEdge(0, 1);
    g1.addEdge(1, 2);
    g1.addEdge(2, 3);
    g1.addEdge(3, 0);
    g1.addEdge(2, 4);
    g1.addEdge(4, 2);
    g1.isSC()? cout << "Yes\n" : cout << "No\n";

    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.isSC()? cout << "Yes\n" : cout << "No\n";
		return 0;
}