#include <stdio.h>
#include <stdlib.h>

typedef struct Edge_t {
	int src;
	int dest;
	int weight;
} Edge;

typedef struct Graph_t {
	int V, E;
	Edge* edges;
} Graph;

Graph* build_graph(int V, int E) {
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->V = V;
	graph->E = E;
	graph ->edges = (Edge*)malloc(E * sizeof(Edge));
	return graph;
}

typedef struct Subset_t {
	int parent;
	int rank;
} Disjoint_Set;

int find_set(Disjoint_Set allsets[], int x) {
	if (allsets[x].parent != x) {
		allsets[x].parent = find_set(allsets, allsets[x].parent);
	}
	return allsets[x].parent;
} 

void union_set(Disjoint_Set allsets[], int x, int y) {
	int root_x = find_set(allsets, x);
	int root_y = find_set(allsets, y);
	if (allsets[root_x].rank > allsets[root_y].rank) {
		allsets[root_y].parent = root_x;
	} else if (allsets[root_x].rank < allsets[root_y].rank) {
		allsets[root_x].parent = root_y;
	} else {
		allsets[root_x].parent = root_y;
		allsets[root_y].rank++;
	}
}

int Cmp (const void* e1, const void* e2) {
	Edge* a = (Edge*) e1;	
	Edge* b = (Edge*) e2;	
	return a->weight > b->weight;
}

void kruskal(Graph* graph) {
	int V = graph->V;
	Edge results[V];
	int e = 0; //index to 

	//step 1: sorts all edges in non-decreasing order of their weight
	qsort(graph->edges, graph->E, sizeof(Edge), Cmp);
	//step 2: make disjoint sets
	Disjoint_Set allsets[V];
	for (int i = 0; i < V; i++) {
		allsets[i].parent = i;
		allsets[i].rank = 0;
	}
	int i = 0;//index for edges	
	while (e < V - 1) {
		Edge next_edge = graph->edges[i++];
		int root_x = find_set(allsets, next_edge.src);	
		int root_y = find_set(allsets, next_edge.dest);	

		if (root_x != root_y) {
			results[e++] = next_edge;
			union_set(allsets, root_x, root_y);
		}
	}
		
	for (i = 0; i < e; i++) {
		printf("%d -- %d == %d\n", results[i].src, results[i].dest, results[i].weight);
	}
	return ;
}

int main() {

	int V = 4;
	int E = 5;

	Graph* graph = build_graph(V, E);
	
	graph->edges[0].src = 0;
	graph->edges[0].dest = 1;
	graph->edges[0].weight= 10;
	graph->edges[1].src = 0;
	graph->edges[1].dest = 2;
	graph->edges[1].weight= 6;
	graph->edges[2].src = 0;
	graph->edges[2].dest = 3;
	graph->edges[2].weight= 5;
	graph->edges[3].src = 1;
	graph->edges[3].dest = 3;
	graph->edges[3].weight= 15;
	graph->edges[4].src = 2;
	graph->edges[4].dest = 3;
	graph->edges[4].weight= 4;
	kruskal(graph);
	return 0;

}
