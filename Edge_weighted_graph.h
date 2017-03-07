#ifndef EDGE_WEIGHTED_GRAPH_H
#define EDGE_WEIGHTED_GRAPH_H

#include <vector>

#include "Edge.h"

class Edge_weighted_graph {
private:
    const std::size_t _num_vertices;
    std::size_t _num_edges;
    std::vector<std::vector<Edge>> _adjacency_lists;

public:
    Edge_weighted_graph(std::size_t V);

    inline std::size_t num_vertices() const noexcept { return _num_vertices; }

    inline std::size_t num_edges() const noexcept { return _num_edges; }

    void add_edge(Edge e);

    inline std::vector<Edge> adjacent(int v) const { return _adjacency_lists[v]; }

    inline std::size_t degree(int v) { return _adjacency_lists[v].size(); }

    std::vector<Edge> edges() const;
};

#endif // EDGE_WEIGHTED_GRAPH_H
