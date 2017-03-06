#include "Adj_matrix_edge_weighted_digraph.h"

Adj_matrix_edge_weighted_digraph::Adj_matrix_edge_weighted_digraph(std::size_t num_vertices)
        : _num_vertices{num_vertices},
          _num_edges{0},
          _adjacency_matrix(num_vertices, std::vector<Directed_edge>(num_vertices)) {}

void Adj_matrix_edge_weighted_digraph::add_edge(Directed_edge e)
{
    auto v = e.from();
    auto w = e.to();
    if (_adjacency_matrix[v][w] == _default) {
        _num_edges++;
        _adjacency_matrix[v][w] = e;
    }
}

std::vector<Directed_edge> Adj_matrix_edge_weighted_digraph::adjacent(int v) const
{
    std::vector<Directed_edge> r;
    for (auto& e : _adjacency_matrix[v]) { if (e != _default) { r.push_back(e); }}
    return r;
}