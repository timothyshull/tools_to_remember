#include "Digraph.h"

Digraph::Digraph(std::size_t num_vertices)
        : _num_vertices{num_vertices},
          _num_edges{0},
          _adjacency_lists(num_vertices, std::unordered_set<int>{}),
          _indegree(num_vertices, 0) {}

void Digraph::add_edge(int v, int w)
{
    if (_adjacency_lists[v].find(w) == _adjacency_lists[v].end()) {
        ++_num_edges;
        ++_indegree[w];
    }
    _adjacency_lists[v].insert(w);
}

Digraph Digraph::reverse()
{
    Digraph reverse{_num_vertices};
    for (auto v = 0; v < _num_vertices; ++v) {
        for (int w : adjacent(v)) {
            reverse.add_edge(w, v);
        }
    }
    return reverse;
}
