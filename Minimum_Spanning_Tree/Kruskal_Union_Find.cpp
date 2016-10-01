class Edge {
public:
    Edge() {}
    Edge(string s, string d, int w) {
        src = s;
        dst = d;
        weight = w;
    }
    string src;
    string dst;
    int weight;
};

class Group {
public:
    Group(){}
    Group(int p, int r) {
        parent = p;
        group_id = r;
    }
    int parent;
    int group_id;
    
};

struct {
    bool operator() (Edge & e1, Edge & e2){
        if (e1.weight < e2.weight) {
            return true;
        } else if (e1.weight == e2.weight) {
            return (e1.src < e2.src || e1.dst < e2.dst );
        } else {
            return false;
        }
     }
} Cmp;

int find(vector<Group> & group, int node_id) {
    if (group[node_id].parent != node_id) {
        group[node_id].parent = find(group, group[node_id].parent);
    }
    return group[node_id].parent;
}

void union_group(vector<Group> & group, int node_a, int node_b) {
    int root_a = find(group, node_a);
    int root_b = find(group, node_b);
    if (group[root_a].group_id < group[root_b].group_id) {
        group[root_a].parent = root_b;
    } else if (group[root_a].group_id > group[root_b].group_id) {
        group[root_b].parent = root_a;
    } else {
        group[root_b].parent = root_a;
        group[root_a].group_id++;
    }
}

vector<Edge> MST(vector<Edge> edges, int V) {
    vector<Edge> result;
    sort(edges.begin(), edges.end(), Cmp);
    priority_queue<Edge, vector<Edge>, decltype(Cmp)> pq(edges.begin(), edges.end());

    int id = 0;
    unordered_map<string, int> node_id;
    for (int i = 0; i < edges.size(); i++) {
        if (node_id.count(edges[i].src) == 0) {
            node_id[edges[i].src] = id++;
        }
        if (node_id.count(edges[i].dst) == 0) {
            node_id[edges[i].dst] = id++;
        }
    }
    
    vector<Group> group(V);
    for (auto p : node_id) {
        group[p.second] = (Group(p.second, 0));
    }
    
    for (int i = 0; i < edges.size(); i++) {
        if (result.size() == V - 1) {
            return result;
        }
        int root_a = find(group, node_id[edges[i].src]);
        int root_b = find(group, node_id[edges[i].dst]);
        if (root_a != root_b) {
            result.emplace_back(edges[i]);
            union_group(group, root_a, root_b);
        }
    }
    return {};
}