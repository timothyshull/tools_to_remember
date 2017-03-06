#include "Flow_network.h"

Flow_network::Flow_network(std::size_t num_vertices)
        : _num_vertices{num_vertices},
          _num_edges{0},
          _adjacency_lists(num_vertices, std::vector<Flow_edge>(num_vertices)) {}

void Flow_network::add_edge(Flow_edge e)
{
    auto v = e.from();
    auto w = e.to();
    // validate vertices
    _adjacency_lists[v].push_back(e);
    _adjacency_lists[w].push_back(e);
    ++_num_edges;
}

std::vector<Flow_edge> Flow_network::edges()
{
    std::vector<Flow_edge> list;
    for (auto v = 0; v < _num_vertices; ++v) {
        for (auto& e : _adjacency_lists[v]) {
            if (e.to() != v) { list.push_back(e); }
        }
    }
    return list;
}