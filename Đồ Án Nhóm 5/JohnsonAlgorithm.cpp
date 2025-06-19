#include "JohnsonAlgorithm.h"

JohnsonAlgorithm::JohnsonAlgorithm(int vertex) :V(vertex) {
	adjList.resize(V + 1);
	potential.resize(V + 1, INT_MAX);
}

void JohnsonAlgorithm::addEdge(int start, int end, int weight) {
	edges.push_back(Edge{start, end, weight});
}

// Buoc 1: Them dinh phu vao do thi voi dinh la V
void JohnsonAlgorithm::addAuxiliaryVertex() {
	for (int i = 0; i < V; i++) {
		edges.push_back(Edge{ V, i, 0 });
	}
}

bool JohnsonAlgorithm::BellmanFord() {
	potential[V] = 0;
	for (int i = 0; i < V; i++) {
		bool finish = true;
		for (Edge x : edges) {
			int start = x.start, end = x.end, weight = x.weight;
			if (potential[start] < INT_MAX && potential[end] > potential[start] + weight) {
				potential[end] = potential[start] + weight;
				finish = false;
			}
		}
		if (finish) break;
	}
	for (Edge x : edges) {
		int start = x.start, end = x.end, weight = x.weight;
		if (potential[start] < INT_MAX && potential[end] > potential[start] + weight) {
			potential[end] = potential[start] + weight;
			return false;
		}
	}
	return true;
}

void JohnsonAlgorithm::reweightEdges() {
	for (Edge &x : edges) {
		x.weight = x.weight + potential[x.start] - potential[x.end];
	}
}

void JohnsonAlgorithm::AdjacencyList() {
	for (Edge e : edges) {
		adjList[e.start].push_back({e.end, e.weight});
	}
}

void JohnsonAlgorithm::JohnsonAlgorithm::Dijkstra(int src) {
	priority_queue < pair<int, int>, vector < pair<int, int>> , greater<pair<int, int>>> pq;
	vector<int> disc(V, INT_MAX);
	vector<int> parent(V, -1);
	vector<bool> check(V, false);
	disc[src] = 0;
	pq.push({ 0, src });
	parent[src] = -1;

	while (!pq.empty()) {
		pair<int, int> top = pq.top(); pq.pop();
		int weight = top.first, start = top.second;
		if (check[start] == true) continue;
		check[start] = true;
		for (pair<int, int> x : adjList[start]) {
			int end = x.first, Weight = x.second;
			if (!check[end] && disc[end] > disc[start] + Weight) {
				disc[end] = disc[start] + Weight;
				parent[end] = start;
				pq.push({ disc[end], end });
			}
		}
	}

	cout << "\nShortest paths from vertex " << src << ":\n";
	cout << " Dest | Path                      | Cost\n";
	cout << "-----------------------------------------------\n";

	for (int dest = 0; dest < V; ++dest) {
		if (src == dest) continue;
		if (disc[dest] == INT_MAX) {
			cout << setw(5) << dest << " | ";
			cout << setw(25) << "No path" << " | ";
			cout << "INF" << endl;
		}
		else {
			cout << setw(5) << dest << " | ";

			// Tạo đường đi
			vector<int> path;
			for (int v = dest; v != -1; v = parent[v])
				path.push_back(v);
			reverse(path.begin(), path.end());

			// In đường đi
			ostringstream oss;
			for (size_t i = 0; i < path.size(); ++i) {
				oss << path[i];
				if (i + 1 < path.size()) oss << " -> ";
			}
			cout << setw(25) << oss.str() << " | ";

			// In độ dài thực tế
			cout << disc[dest] - potential[src] + potential[dest] << endl;
		}
	}
}

void JohnsonAlgorithm::Johnson() {
	addAuxiliaryVertex();
	if (!BellmanFord())
	{
		cout << "The graph contains a negative-weight cycle" << endl;
		return;
	}
	reweightEdges();
	AdjacencyList(); // Chuyển vào đây, thay vì bên trong Dijkstra
	// Bat dau tu moi dinh
	for (int i = 0; i < V; ++i) {
		Dijkstra(i);
	}
}


