#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

struct Edge {
	int u, v, w;
};

class Graph {
private:
	int V;
	vector<vector<pair<int, int>>> adjList;
	vector<Edge> dscanh;
	vector<int> h;
public:
	Graph(int vertex) :V(vertex) {
		adjList.resize(V + 1);
		h.resize(V + 1, INT_MAX);
	}
	void AddEdge(int u, int v, int w) {
		dscanh.push_back(Edge{u, v, w});
	}

	// Buoc 1: Them dinh phu vao do thi voi dinh la V
	void AddVertex() {
		for (int i = 0; i < V; i++) {
			dscanh.push_back(Edge{ V, i, 0 });
		}
	}

	bool Bell_Man_Ford() {
		h[V] = 0;
		for (int i = 0; i < V; i++) {
			bool finish = true;
			for (Edge x : dscanh) {
				int u = x.u, v = x.v, w = x.w;
				if (h[u] < INT_MAX && h[v] > h[u] + w) {
					h[v] = h[u] + w;
					finish = false;
				}
			}
			if (finish) break;
		}
		for (Edge x : dscanh) {
			int u = x.u, v = x.v, w = x.w;
			if (h[u] < INT_MAX && h[v] > h[u] + w) {
				h[v] = h[u] + w;
				return false;
			}
		}
		return true;
	}

	void Reweight_Edges() {
		for (Edge &x : dscanh) {
			x.w = x.w + h[x.u] - h[x.v];
		}
	}

	void AddEdgeIntoAdjList() {
		for (Edge e : dscanh) {
			adjList[e.u].push_back({e.v, e.w});
		}
	}

	void Dijkstra(int src) {
		priority_queue < pair<int, int>, vector < pair<int, int>> , greater<pair<int, int>>> pq;
		vector<int> disc(V, INT_MAX);
		vector<int> parent(V, -1);
		vector<bool> check(V, false);
		disc[src] = 0;
		pq.push({ 0, src });
		parent[src] = -1;

		while (!pq.empty()) {
			pair<int, int> top = pq.top(); pq.pop();
			int weight = top.first, u = top.second;
			if (check[u] == true) continue;
			check[u] = true;
			for (pair<int, int> x : adjList[u]) {
				int v = x.first, w = x.second;
				if (!check[v] && disc[v] > disc[u] + w) {
					disc[v] = disc[u] + w;
					parent[v] = u;
					pq.push({ disc[v], v });
				}
			}
		}

		for (int dest = 0; dest < V; ++dest) {
			if (disc[dest] == INT_MAX) {
				cout << "Khong co duong tu " << src << " den " << dest << endl;
			}
			else {
				cout << "Duong tu " << src << " den " << dest << ": ";
				Print(parent, dest);
				cout << " | Do dai = " << disc[dest] - h[src] + h[dest] << endl;
			}
		}
	}

	void John_Son() {
		AddVertex();
		if (!Bell_Man_Ford())
		{
			cout << "Do thi co chu trinh am" << endl;
			return;
		}
		Reweight_Edges();
		AddEdgeIntoAdjList(); // Chuyển vào đây, thay vì bên trong Dijkstra
		// Bat dau tu moi dinh
		for (int i = 0; i < V; ++i) {
			cout << "\n  ----------- Duong di tu dinh " << i << " ------------- \n";
			Dijkstra(i);
		}
	}

	void Print(vector<int>& parent, int dest) {
		if (parent[dest] == -1) {
			cout << dest;
			return;
		}
		Print(parent, parent[dest]);
		cout << " -> " << dest;
	}
};

int main() {
	Graph g(4);
	g.AddEdge(0, 1, 1);
	g.AddEdge(1, 2, -2);
	g.AddEdge(2, 3, 2);
	g.AddEdge(3, 0, 4);
	g.John_Son();
	return 0; 
}