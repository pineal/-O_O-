//Reference:
//http://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
//Time Complexity: O(ElogV)

//if we use fibonacci heap O(E + vlogv)
#include <vector>
#include <queue>
using namespace std;
class Graph {
    int V;
    vector<vector<pair<int, int>>> adj;
public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    void dijkstra(int s);
};

Graph::Graph(int V) {
    this -> V = V;
    adj = vector<vector<pair<int, int>>>(V);
}

void Graph::addEdge(int u, int v, int w){
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
}

void Graph::dijkstra(int src) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
    vector<int> dist (V, INT_MAX);
    min_heap.emplace(0, src);
    dist[src] = 0;
    while (!min_heap.empty()) {
        int u = min_heap.top().second;
        min_heap.pop();
        for (auto iter = adj[u].begin(); iter != adj[u].end(); iter++) {
            int v = iter->first;
            int w = iter->second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                min_heap.push(make_pair(dist[v], v));
            }
        }
    }
    
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; ++i) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

int main(int c, char** v) {
    // create the graph given in above fugure
    int V = 9;
    Graph g(V);
    
    //  making above shown graph
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
    g.dijkstra(0);
    
    return 0;
}
