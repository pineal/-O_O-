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
