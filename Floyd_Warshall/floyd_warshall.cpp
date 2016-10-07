#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define V 4
#define INF 99999
//we can use INT_MAX to represent the max_int, 
//but need to pay attention to overflow
void print_solution(int dist[][V]) {
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (dist[i][j] == INF) {
				printf("%7s", "INF");
			} else {
				printf("%7d", dist[i][j]);
			}
		}
		printf("\n");
	}
}

void floyd_warshall(int graph[][V]) {
	int dist[V][V], i, j, k;
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			dist[i][j] = graph[i][j];
		}
	}	

	for (k = 0; k < V; k++) {
		for (i = 0; i < V; i++) {
			for (j = 0; j < V; j++) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] =  dist[i][k] + dist[k][j];
				}
			}
		}
	}
	print_solution(dist);
}

int main() {
	int graph[V][V] = {
		{0, 5, INF, 10},
		{INF, 0, 3, INF},
		{INF, INF, 0, 1},
		{INF, INF, INF, 0},
	};
	floyd_warshall(graph);
	return 0;
}


