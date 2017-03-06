#ifndef TOOLS_TO_REMEMBER_FLOW_NETWORK_H
#define TOOLS_TO_REMEMBER_FLOW_NETWORK_H

#include <vector>
#include "Flow_edge.h"

class Flow_network {
private:
    const std::size_t _num_vertices;
    std::size_t _num_edges;
    std::vector<std::vector<Flow_edge>> _adjacency_lists;

public:
    Flow_network(std::size_t num_vertices);

    inline std::size_t num_vertices() const noexcept { return _num_vertices; }

    inline std::size_t num_edges() const noexcept { return _num_edges; }

    void add_edge(Flow_edge e);

    // validate vertex
    inline std::vector<Flow_edge> adjacent(int v) const { return _adjacency_lists[v]; }

    std::vector<Flow_edge> edges();
};

#endif // TOOLS_TO_REMEMBER_FLOW_NETWORK_H
