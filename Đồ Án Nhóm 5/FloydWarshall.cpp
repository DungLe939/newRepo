#include "FloydWarshall.h"

const int INF = 1000000000;  // hoặc INT_MAX/2 để tránh tràn

floydWarshall::floydWarshall(int vertex) : V(vertex) {
    adjMatrix.assign(V, vector<int>(V, INF));
    for (int i = 0; i < V; i++) {
        adjMatrix[i][i] = 0;
    }
}

void floydWarshall::addEdge(int start, int end, int weight) {
    adjMatrix[start][end] = weight;
}

void floydWarshall::FloydWarshall() {
    vector<vector<int>> dist = adjMatrix;

    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            if (dist[i][k] == INF) continue; 
            for (int j = 0; j < V; ++j) {
                if (dist[k][j] == INF) continue;
                int viaK = dist[i][k] + dist[k][j];
                if (viaK < dist[i][j]) {
                    dist[i][j] = viaK;
                }
            }
        }
    }
    cout << "\nAll pairs shortest paths (Floyd–Warshall):\n";
    printMatrix(dist);
}

void floydWarshall::printMatrix(const vector<vector<int>> &dist) {
    // In tiêu đề cột
    cout << setw(6) << "";
    for (int j = 0; j < V; ++j)
        cout << setw(6) << j;
    cout << "\n" << string(7 + 6 * V, '-') << "\n";

    // In từng hàng
    for (int i = 0; i < V; ++i) {
        cout << setw(6) << i << "|";
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INF)
                cout << setw(6) << "INF";
            else
                cout << setw(6) << dist[i][j];
        }
        cout << "\n";
    }
}
