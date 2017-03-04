#ifndef TOOLS_TO_REMEMBER_EDGE_WEIGHTED_DIGRAPH_H
#define TOOLS_TO_REMEMBER_EDGE_WEIGHTED_DIGRAPH_H

#include <vector>

#include "Directed_edge.h"

class Edge_weighted_digraph {
private:
    const std::size_t _num_vertices;
    std::size_t _num_edges;
    std::vector<std::vector<Directed_edge>> _adjacency_lists;
    std::vector<int> _indegree;

public:
    Edge_weighted_digraph(std::size_t num_vertices);

    constexpr std::size_t num_vertices() const noexcept { return _num_vertices; }

    inline std::size_t num_edges() const noexcept { return _num_edges; }

    void add_edge(Directed_edge e);

    inline std::vector<Directed_edge> adjacent(int v) const { return _adjacency_lists[v]; }

    std::size_t outdegree(int v) const { return _adjacency_lists[v].size(); }

    inline int indegree(int v) const { return _indegree[v]; }

    std::vector<Directed_edge> edges();
};

#endif // TOOLS_TO_REMEMBER_EDGE_WEIGHTED_DIGRAPH_H
