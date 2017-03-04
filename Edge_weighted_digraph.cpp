#include "Edge_weighted_digraph.h"

Edge_weighted_digraph::Edge_weighted_digraph(std::size_t num_vertices)
        : _num_vertices{num_vertices},
          _num_edges{0},
          _indegree(num_vertices, 0),
          _adjacency_lists(num_vertices, std::vector<Directed_edge>{}) {}

void Edge_weighted_digraph::add_edge(Directed_edge e)
{
    auto v = e.from();
    auto w = e.to();
    _adjacency_lists[v].push_back(e);
    ++_indegree[w];
    ++_num_edges;
}

std::vector<Directed_edge> Edge_weighted_digraph::edges()
{
    std::vector<Directed_edge> v(_num_edges);
    for (auto& l : _adjacency_lists) { for (auto& e : l) { v.push_back(e); }}
    return v;
}