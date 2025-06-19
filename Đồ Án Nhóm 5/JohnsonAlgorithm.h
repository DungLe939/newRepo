#pragma once
#include "Standard_Library.h"

using namespace std;

class JohnsonAlgorithm {
private:

	struct Edge {
		int start, end, weight;
	};

	int V;
	vector<vector<pair<int, int>>> adjList;
	vector<Edge> edges;
	vector<int> potential;

public:
	JohnsonAlgorithm(int vertex);

	void addEdge(int start, int end, int weight);

	void addAuxiliaryVertex();

	bool BellmanFord();

	void reweightEdges();

	void AdjacencyList();

	void Dijkstra(int src);

	void Johnson();
};