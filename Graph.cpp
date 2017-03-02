#include "Graph.h"

Graph::Graph(std::size_t num_vertices)
        : _num_vertices{num_vertices},
          _adjacency_lists(num_vertices, std::unordered_set<int>{}) {}

void Graph::add_edge(int v, int w)
{
    // validate vertices
    if (_adjacency_lists[v].find(w) == _adjacency_lists[v].end()
        && _adjacency_lists[w].find(v) == _adjacency_lists[w].end()) {
        ++_num_edges;
    }
    _adjacency_lists[v].insert(w);
    _adjacency_lists[w].insert(v);
}