#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;
#define DEL -1
#define ADD 1
#define UNCHANGE 0
int minEditDistance(string word1, string word2) {
    int m = word1.size();
    int n = word2.size();
    vector<vector<int>> M(m + 1, vector<int>(n + 1, 0));
    vector<vector<int>> OP(m + 1, vector<int>(n + 1, UNCHANGE));
    
    
    for (int i = 1; i <= m; i++) {
        M[i][0] = 2;
        OP[i][0] = DEL;
    }
    for (int i = 1; i <= n; i++) {
        M[0][i] = i + 2;
        OP[0][i] = ADD;
    }

    
    for (int i = 1; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            int min_cost = INT_MAX;
            int del_min_cost = INT_MAX;
            if (OP[i-1][j] == DEL) {
                del_min_cost = M[i-1][j];
            } else {
                del_min_cost = M[i-1][j] + 2;
            }
            
            int add_min_cost = INT_MAX;
            if (OP[i][j-1] == ADD) {
                add_min_cost = M[i][j-1] + 1;
            } else {
                add_min_cost = M[i][j-1] + 3;
            }
            
            if (del_min_cost > add_min_cost) {
                OP[i][j] = ADD;
                min_cost = add_min_cost;
            } else {
                OP[i][j] = DEL;
                min_cost = del_min_cost;
            }
            int unchange_min_cost = word1[i - 1] == word2[j - 1]? M[i - 1][j - 1] : M[i - 1][j - 1] + 5;
            if (unchange_min_cost < min_cost) {
                OP[i][j] = UNCHANGE;
                min_cost = unchange_min_cost;
            }
            
            M[i][j] = min_cost;
        }
    }
    
    return M.back().back();
}

int main() {
    int N = 0;
    cin >> N;
    string a;
    string b;
    vector<int> result;
    while (N > 0) {
        cin >> a >> b;
        result.push_back(minEditDistance(a, b));
        N--;
    }
    for (auto r : result) {
        cout << r << endl;
    }
}