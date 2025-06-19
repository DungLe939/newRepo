#pragma once
#include "Standard_Library.h"

using namespace std;

class floydWarshall {
private:
	int V;
	vector<vector<int>> adjMatrix;
public:
	floydWarshall(int vertex);
	void addEdge(int start, int end, int weight);
	void FloydWarshall();
	void printMatrix(const vector<vector<int>>& dist);
};