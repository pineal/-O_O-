/*
 第一题：Path Finder
 有向图，图中可能存在环，找Source到Destination的所有路径，DFS + backtracking 做的，参考 http://www.geeksforgeeks.org/find-paths-given-source-destination/. From 1point 3acres bbs
 输入形式是：vector<string> lines
 A J
 A : B C
 B : C E G
 C : A F
 D : C J
 F : B H
 G : C D
 H : A B F I
 I : B
 输出形式:["ABGDJ", "ACFBGDJ", "ACFHBGDJ", "ACFHIBGDJ"] vector<string>
 
	* http://www.geeksforgeeks.org/find-paths-given-source-destination/
	* Print all paths from a given source to a destination
	*/
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

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
        //mark this line's parent node
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

void dfs (const char & start, const char & end, const char & node, unordered_map<char, unordered_set<char>> nodes, string & path, vector<string> & result, unordered_set<char> visited) {
    if (node == end) {
        result.push_back(path);
        return;
    }
    for (auto iter = nodes[node].begin(); iter != nodes[node].end(); iter++) {
        if (visited.find(*iter) != visited.end()) {
            continue;
        }
        visited.insert(*iter);
        path+=(*iter);
        dfs(start, end, *iter, nodes, path, result, visited);
        visited.erase(*iter);
        path.pop_back();
    }
}


vector<string> parseLines(const vector<string> & lines) {
    unordered_map<char, unordered_set<char>> nodes;
    if (lines.size() == 0) {
        return {};
    }
    
    char start = toupper(lines[0][0]);
    char end = toupper(lines[0][2]);
    nodes.insert({start, {}});
    nodes.insert({end, {}});
    for (int i = 1; i < lines.size(); i++) {
        string cur_line = lines[i];
        char parent;
        for (int j = 0; j < cur_line.size(); j++) {
            char c = toupper(cur_line[j]);
            //skip all non-letters
            if (!isalpha(c)) {
                continue;
            }
            //detect parent node
            if (j == 0) {
                if (nodes.find(c) == nodes.end()) {
                    nodes.insert({c, {}});
                }
                parent = c;
            } else {
                //add new nodes to hashmap
                if (nodes.find(c) == nodes.end()) {
                    //put it into hashmap
                    nodes.insert({c, {}});
                    //add it to the parent's neighbor
                    nodes[parent].insert({c});
                } else {
                    nodes[parent].insert({c});
                }
            }
        }
    }

    
    //backtracking
    string path = {start};
    vector<string> result;
    unordered_set<char> visited = {start};
    dfs(start, end, start, nodes, path, result, visited);
    return result;
}



//    for (auto iter = nodes.begin(); iter != nodes.end(); iter++) {
//        cout << iter -> first << "->  ";
//        for (auto x : iter -> second) {
//            cout << x;
//        }
//        cout << endl;
//    }


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
    //Graph g(input);
    //g.print_graph();
//    g.find_path();
    auto x = parseLines(input);
    for (auto xx : x) {
        cout <<xx<<endl;
    }
    return 0;
}
