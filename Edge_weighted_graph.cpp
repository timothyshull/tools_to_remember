#include "Edge_weighted_graph.h"

Edge_weighted_graph::Edge_weighted_graph(std::size_t V)
        : _num_vertices{V},
          _num_edges{0},
          _adjacency_lists(V, std::vector<Edge>{}) {}

void Edge_weighted_graph::add_edge(Edge e)
{
    auto v = e.either();
    auto w = e.other(v);
    _adjacency_lists[v].push_back(e);
    _adjacency_lists[w].push_back(e);
    ++_num_edges;
}

std::vector<Edge> Edge_weighted_graph::edges() const
{
    std::vector<Edge> list;
    for (auto v = 0; v < _num_vertices; ++v) {
        auto self_loops = 0;
        for (auto& e : _adjacency_lists[v]) {
            if (e.other(v) > v) { list.push_back(e); }
            else if (e.other(v) == v) {
                if (self_loops % 2 == 0) { list.push_back(e); }
                ++self_loops;
            }
        }
    }
    return list;
}