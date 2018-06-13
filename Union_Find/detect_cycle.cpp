#include <stdio.h>
#include <stdlib.h>

typedef struct Edge_t {
	int src;
	int dest;
} Edge;

typedef struct Graph_t {
	int V, E;
	Edge* edges;
} Graph;

typedef struct disjoint_set_t {
	int parent;
	int rank;
}Disjoint_Set;

Graph* build_graph(int V, int E) {
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->V = V;
	graph->E = E;
	graph->edges = (Edge*)malloc(E * sizeof(Edge));
	return graph;
}

int find_set(Disjoint_Set allsets[], int x) {
	if (allsets[x].parent != x) {
		allsets[x].parent = find_set(allsets, allsets[x].parent);
	}
	return allsets[x].parent;
}

void union_set(Disjoint_Set allsets[], int x, int y) {

	int xroot = find_set(allsets, x);
	int yroot = find_set(allsets, y);
	
	if (allsets[xroot].rank > allsets[yroot].rank) {
		allsets[yroot].parent = xroot;
	} else if (allsets[xroot].rank < allsets[yroot].rank) {
		allsets[xroot].parent = yroot;
	} else {
		allsets[xroot].parent = yroot;
		allsets[yroot].rank++;
	}
}

bool is_cycle(Graph* graph) {
	int V = graph->V;
	int E = graph->E;

	Disjoint_Set* allsets = (Disjoint_Set*)malloc(V * sizeof(Disjoint_Set));
	for (int v = 0;  v < V; v++) {
		allsets[v].parent = v;
		allsets[v].rank = 0;
	}
	
	for (int e = 0; e < E; e++) {
		int x = find_set(allsets, graph->edges[e].src);
		int y = find_set(allsets, graph->edges[e].dest);

		if(x == y) {
			return true;
		}
		union_set(allsets, x, y);
	}
	return false;
}

int main () {

	int V = 3;
	int E = 3;

	Graph* graph = build_graph(V, E);
	graph->edges[0].src = 0;
	graph->edges[0].dest = 1;
	graph->edges[1].src = 1;
	graph->edges[1].dest = 2;
	graph->edges[2].src = 0;
	graph->edges[2].dest = 2;
	if (is_cycle(graph)) {
		printf("Cycle detected.");
	} else {
		printf("No cycle detected.");
	}
	return 0;
}


/*
class TreeNode {
 public:
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};

int helper(const vector<vector<int>>& matrix, int k, int left, int right) {
    if (left >= right) {
        return left;
    }
    //pick a reference value
    int mid = left + (right - left)/2;
    int n = matrix.size();
    int m = 0;
    //counts number of elements smaller than or equal to mid
    for (int i = 0; i < n; i++) {
        
        /*
         *
         *The upper bound idea if optimized from:
         for (int j = 0; j < matrix[i].size(); j++) {
         if (matrix[i][j] <= mid) {
         m++;
         }
         }
         * using for loop is the basic idea to help understand,
         * actually we can use binary search again to find the smallest element that larger than mid
 
        
    int num = upper_bound(matrix[i].begin(), matrix[i].end(), mid) - matrix[i].begin();
        m += num;
    }
    // now we know that there are m elements <= mid[include mid]
    // thus mid is **at least** m th smallest element in the matrix
    // but not the exact m th!
    // beacause we don't know whether mid exsits in matrix
    // if m < k, then kth smallest element must appear after mid
    // otherwise, kth element must appear before mid
    
    if (m < k) {
        return helper(matrix, k, mid + 1, right);
    } else {
        return helper(matrix, k, left, mid);
    }
}
int kthSmallest(vector<vector<int>>& matrix, int k) {
    return helper(matrix, k, 1, 10000);
}


void testkthSmallest() {
    vector<vector<int>> matrix;
    matrix.push_back({1,2,3,4,5});
    matrix.push_back({2,3,4,5});
    matrix.push_back({3,4,5,6,8,12});
    matrix.push_back({9,10});
    for (int i = 0; i <= 20; i++) {
        cout << kthSmallest(matrix, i) << endl;
    }
    
}
int smallestDistancePair(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    int n = nums.size(), low = 0, high = 1000000;
    while (low < high) {
        int mid = (low + high)/2, cnt = 0;
        for (int i = 0, j = 0; i < n; i++) {
            while (j < n && nums[j]-nums[i] <= mid) {
             j++;
            }
            cout << i << " " << j << endl;
            cnt += j-i-1;
        }
        if (cnt < k)
            low = mid+1;
        else
            high = mid;
    }
    return low;
}

void testSmallestDistancePair () {
    vector<int> nums = {1, 1, 3, 3, 4, 6, 7};
    for (int i = 0; i < nums.size() * nums.size(); i++) {
        cout << smallestDistancePair(nums, i) << endl;
    }
    
    
}

vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
    auto cmp = [&A](const pair<int, int> & a, const pair<int, int> & b) {
        return A[a.first] * A[b.second] >  A[a.second] * A[b.first];
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> min_heap(cmp);
    int p1 = 0, p2 = A.size() - 1;
    min_heap.emplace(p1, p2);
    deque<deque<bool>> visited(A.size(), deque<bool>(A.size(), false));
    visited[p1][p2] = true;
    int count = 1;
    while (count < K) {
        p1 = min_heap.top().first;
        p2 = min_heap.top().second;
        min_heap.pop();
        
        if (p1 + 1 < A.size() && visited[p1 + 1][p2] == false) {
            min_heap.emplace(p1 + 1, p2);
            visited[p1 + 1][p2] = true;
        }
        if (p2 - 1 >= 0 && visited[p1][p2 - 1] == false) {
            min_heap.emplace(p1, p2 - 1);
            visited[p1][p2 - 1] = true;
        }
        count++;
    }
    return {A[min_heap.top().first], A[min_heap.top().second]};
}

void testkthSmallestPrimeFraction() {
    vector<int> A = {1, 7, 23, 29, 47};
    for (int k = 1; k <= A.size() * (A.size() - 1)/2; k++) {
        vector<int> ans = kthSmallestPrimeFraction(A, k);
        cout << ans[0] << " " << ans[1] <<  endl;
    }
}

int minCost(vector<int> cuts, int length) {
    // write your solution here
    int n = cuts.size();
    vector<vector<int>> M(n, vector<int>(n, 999));
    
    for (int i = 0; i < n - 1; i++) {
        M[i][i + 1] = 0;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = i + 1; k < j; k++) {
                M[i][j] = min(M[i][j], cuts[j] - cuts[i] + M[i][k] + M[k][j]);
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << M[i][j] << "    ";
        }
        cout << endl;
    }
    return M[0][n - 1];
}

void testMinCost() {
    vector<int> cuts = {0,2,4,7,10};
    minCost(cuts, 16);
}

int minSquareNumbers(int n) {
    vector<int> M(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int curMin = i;
        for (int j = 1; j * j <= i; j++) {
            curMin = min(curMin, M[i - j * j] + 1);
        }
        M[i] = curMin;
    }
    return M[n];
}

TreeNode* deserializeTreeHelper(const vector<int> & in, int in_left, int in_right,
                 const vector<int> & pre, int pre_left,
                 unordered_map<int, int> table) {
    if (in_left > in_right) {
        return nullptr;
    }
    
    TreeNode* root = new TreeNode(pre[pre_left]);
    int index = table[root->val];
    root->left = deserializeTreeHelper(in, in_left, index - 1, pre, pre_left + 1, table);
    root->right = deserializeTreeHelper(in, index + 1, in_right, pre, pre_left + index - in_left + 1, table);
    return root;
}

TreeNode* deserializeTree(vector<int> & in, vector<int> & pre) {
    unordered_map<int, int> table;
    for (int i =0; i < in.size(); i++) {
        table[in[i]] = i;
    }
    return deserializeTreeHelper(in, 0, in.size() - 1, pre, 0, table);
}

void pushleft(TreeNode* root, stack<TreeNode*> & s) {
    while (root) {
        s.push(root);
        root = root->left;
    }
}

vector<int> postorder(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        auto cur = s1.top();
        s2.push(cur);
        s1.pop();
        if (cur->left) {
            s1.push(cur->left);
        }
        if (cur->right) {
            s1.push(cur->right);
        }
    }
    while (!s2.empty()) {
        auto cur = s2.top();
        s2.pop();
        res.emplace_back(cur->val);
    }
    return res;
}


vector<int> postorderII(TreeNode* root) {
    if (root == nullptr) {
        return {};
    }
    vector<int> res;
    stack<TreeNode*> s;
    s.push(root);
    TreeNode* prev = nullptr;
    while (!s.empty()) {
        auto cur = s.top();
        //s.pop();
        if (prev == nullptr || cur == prev->left || cur == prev->right) {
            if (cur->left) {
                s.push(cur->left);
            }
            else if (cur->right) {
                s.push(cur->right);
            }
            else {
                s.pop();
                res.emplace_back(cur->val);
            }
        }
        else if (prev == cur->right || prev == cur->left && cur->right == nullptr) {
            s.pop();
            res.emplace_back(cur->val);
        }
        else {
            s.push(cur->right);
        }
        prev = cur;
    }
    return res;
}


void testinorder() {
    TreeNode* a1 = new TreeNode(5);
    TreeNode* a2 = new TreeNode(3);
    TreeNode* a3 = new TreeNode(6);
    TreeNode* a4 = new TreeNode(1);
    TreeNode* a5 = new TreeNode(4);
    TreeNode* a6 = new TreeNode(7);
    TreeNode* a8 = new TreeNode(8);
    TreeNode* a9 = new TreeNode(2);
    a1->left = a2;
    a1->right = a3;
    a2->left = a4;
    a2->right = a5;
    a5->left = a9;
    a3->left = a6;
    a3->right = a8;
    auto res = postorder(a1);
    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << " ";
    }
    cout << endl;
}

class InorderIterator
{
public:
    InorderIterator() {}
    ~InorderIterator() {}
    InorderIterator(TreeNode* root);
    int getNext();
private:
    stack<TreeNode*> _s;
    TreeNode* _cur;
};

*/