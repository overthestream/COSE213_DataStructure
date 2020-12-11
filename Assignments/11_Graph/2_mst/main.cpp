#define NUM_NODES 6
#define NUM_EDGES 9
#define INF 0x7FFF
#include <stdio.h>
#include <stdbool.h>
/*
 크루스칼은 그냥 모든 간선중에
 유니온파인드 하면서
 연결 안된 간선만 모으는거고
 프림은 source를 하나 정해서
 거기서 연결된 것중에 최소 간선으로 트리를 만들어나가는거네
*/
typedef struct {
	int from;
	int to;
	bool processed;
	int weight;
}edge;
void printGraph(int(*graph)[NUM_NODES], int* from) {
	int sum = 0;
	printf("*******Prim's Algorithm********\n");
	for (int i = 1; i < NUM_NODES; ++i) {
		printf("%c - %c : weight - %d\n", 'A' + from[i], 'A' + i, graph[i][from[i]]);
		sum += graph[i][from[i]];
	}
	printf("Total weight : %d\n", sum);
}

void prim(int(*graph)[NUM_NODES]) {

	bool visited[NUM_NODES];
	int dist[NUM_NODES];
	int from[NUM_NODES];

	// initialize
	for (int i = 0; i < NUM_NODES; ++i) {
		dist[i] = INF;
		visited[i] = false;
	}

	// select source
	dist[0] = 0;
	from[0] = -1;

	int node, min;

	for (int i = 0; i < NUM_NODES - 1; ++i) {
		min = INF;
		// in fact, dist is edge which is not connected to spanning tree when it is not INF.
		// find vertex in minimum distance from tree(not source) (un visited)  == 트리에서의 최소 엣지 .
		for (int j = 0; j < NUM_NODES; ++j)
			if (visited[j] == false)
				if (dist[j] < min) {
					min = dist[j];
					node = j;
				}

		visited[node] = true;
		for (int j = 0; j < NUM_NODES; ++j)
			if (graph[node][j] && visited[j] == false) // if node is adjcacent and unvisited
				if (graph[node][j] < dist[j]) { // renew distance from graph 
					from[j] = node;
					dist[j] = graph[node][j];
				}
	}

	/*
	min heap <- source;

	while(!all the vertex visited){
		min heap 꺼내기
		if(visited) continue;
		min heap<-인접 vertex;
		curNode -> visited;
	}
	
	*/



	printGraph(graph, from);
}
void initEdges(int(*graph)[NUM_NODES], edge* edges) {
	int edgeCount = 0;
	for (int i = 0; i < NUM_NODES; ++i) {
		for (int j = i + 1; j < NUM_NODES; ++j) {
			if (0 < graph[i][j] && graph[i][j] < INF) {
				edges[edgeCount].from = i;
				edges[edgeCount].to = j;
				edges[edgeCount].processed = false;
				edges[edgeCount++].weight = graph[i][j];
			}
		}
	}
}
void printEdges(edge* edges) {
	int sum = 0;
	printf("*****Kruscal's Algorithm******\n");
	for (int i = 0; i < NUM_EDGES; ++i) {
		if (!edges[i].processed) continue;
		printf("%c - %c : weight - %d\n", 'A' + edges[i].from, 'A' + edges[i].to, edges[i].weight);
		sum += edges[i].weight;
	}
	printf("Total weight : %d\n", sum);

}

int __find(int node, int* root) {

	if (root[node] == node) return node;

	else return root[node] = __find(root[node], root);

}

void __union(int a, int b, int* root) {

	int node1 = __find(a, root), node2 = __find(b, root);
	root[node2] = node1;
	return;


}

void kruscal(int(*graph)[NUM_NODES]) {
	edge edges[NUM_EDGES];
	initEdges(graph, edges);
	int parent[NUM_NODES];
	int node1, node2;
	for (int i = 0; i < NUM_NODES; ++i) parent[i] = i;
	int minWeight, minIndex;
	for (int i = 0; i < NUM_NODES - 1; ++i) {
		minWeight = INF;
		for (int j = 0; j < NUM_EDGES; ++j) {
			if (edges[j].processed) continue;
			node1 = edges[j].from;
			node2 = edges[j].to;
			if (minWeight > edges[j].weight) {
				if (__find(node1, parent) != __find(node2, parent)) {
					minIndex = j;
					minWeight = edges[j].weight;
				}
			}
		}
		__union(edges[minIndex].from, edges[minIndex].to, parent);
		edges[minIndex].processed = true;
	}

	printEdges(edges);

}

int main()
{
	int graph[NUM_NODES][NUM_NODES] = {
		{0,6,3,INF,INF,INF},
		{6,0,2,5,INF,INF},
		{3,2,0,3,4,INF},
		{INF,5,3,0,2,3},
		{INF,INF,4,2,0,5},
		{INF,INF,INF,3,5,0}
	};
	kruscal(graph);

	prim(graph);
	return 0;
}