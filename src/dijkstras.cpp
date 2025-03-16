#include "dijkstras.h"
#include <queue>

vector<int> dijkstra_shortest_path(const Graph &G, int source, vector<int> &previous) {
    vector<int> distances;
    vector<int> visited;

    distances.resize(G.numVertices, INF);
    visited.resize(G.numVertices, 0);
    previous.resize(G.numVertices, -1);

    struct Comp {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) { return a.second > b.second; }
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, Comp> minV;

    minV.push({source, 0});
    distances[source] = 0;

    while (pee pee poo poo poopie caka)

}

