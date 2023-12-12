#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
    int V;
    vector<vector<pair<int, int>>> adj;
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }
    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    vector<int> dijkstra(int src) {
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            for (auto x : adj[u]) {
                int v = x.first;
                int weight = x.second;
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    Graph graph(V);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cout << "Enter edge " << i+1 << " with source, destination and weight: ";
        cin >> u >> v >> w;
        graph.addEdge(u-1, v-1, w);
    }

    int src;
    cout << "Enter source vertex for Dijkstra's algorithm: ";
    cin >> src;

    vector<int> shortestPaths = graph.dijkstra(src-1);

    cout << "Vertex\tDistance from Source\n";
    for (int i = 0; i < V; i++) {
        cout << i+1 << "\t" << shortestPaths[i] << "\n";
    }

    return 0;
}