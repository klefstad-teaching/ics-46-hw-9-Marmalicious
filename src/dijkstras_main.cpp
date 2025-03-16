#include "dijkstras.h"

int main() {
    Graph g;
    file_to_graph("src/small.txt", g);
    vector<int> p;
    vector<int> d = dijkstra_shortest_path(g, 0, p);
    for (int i = 0; i < g.numVertices; ++i) {
        vector<int> t = extract_shortest_path(d, p, i);
        print_path(t, d[i]);
    }
}