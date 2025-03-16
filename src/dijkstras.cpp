#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph &G, int source, vector<int> &previous) {
    vector<int> distances;
    vector<int> visited;

    distances.resize(G.numVertices, INF);
    visited.resize(G.numVertices, 0);
    previous.assign(G.numVertices, -1);

    struct Compare {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) { return a.second > b.second; }
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> minV;

    minV.push({source, 0});
    distances[source] = 0;

    while (!minV.empty()) {
        int current = minV.top().first;
        minV.pop();
        if (visited[current]) continue;
        visited[current] = 1;

        for (Edge e : G[current]) {
            int nextV = e.dst;
            int nextW = distances[current] + e.weight;
            if (!visited[nextV] && nextW < distances[nextV]) {
                distances[nextV] = nextW;
                previous[nextV] = current;
                minV.push({nextV, nextW});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    stack<int> reverse;
    vector<int> path;
    while (destination != -1) {
        reverse.push(destination);
        destination = previous[destination];
    }
    while (!reverse.empty()) {
        path.push_back(reverse.top());
        reverse.pop();
    }
    return path;
}

void print_path(const vector<int>& v, int total) {
    if (total != INF) {
        for (int i : v) cout << i << " ";
        cout << endl << "Total cost is " << total << endl;
    }
}