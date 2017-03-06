#ifndef TOOLS_TO_REMEMBER_ADJ_MATRIX_EDGE_WEIGHTED_DIGRAPH_H
#define TOOLS_TO_REMEMBER_ADJ_MATRIX_EDGE_WEIGHTED_DIGRAPH_H

#include <vector>

#include "Directed_edge.h"

class Adj_matrix_edge_weighted_digraph {
private:
    const static Directed_edge _default = Directed_edge{};
    std::size_t _num_vertices;
    std::size_t _num_edges;
    std::vector<std::vector<Directed_edge>> _adjacency_matrix;

public:
    Adj_matrix_edge_weighted_digraph(std::size_t num_vertices);

    ~Adj_matrix_edge_weighted_digraph() = default;

    inline std::size_t num_vertices() const noexcept { return _num_vertices; }

    inline std::size_t num_edges() const noexcept { return _num_edges; }

    void add_edge(Directed_edge e);

    std::vector<Directed_edge> adjacent(int v) const;
};

#endif // TOOLS_TO_REMEMBER_ADJ_MATRIX_EDGE_WEIGHTED_DIGRAPH_H
