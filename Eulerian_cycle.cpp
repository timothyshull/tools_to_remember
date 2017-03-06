#include "Eulerian_cycle.h"

Eulerian_cycle::Edge::Edge(int v, int w)
        : v{v},
          w{w},
          is_used{false} {}

int Eulerian_cycle::Edge::other(int vertex)
{
    if (vertex == v) { return w; }
    else if (vertex == w) { return v; }
    else { throw std::invalid_argument{"Illegal endpoint"}; }
}

Eulerian_cycle::Eulerian_cycle(const Graph& graph)
        : _cycle{}
{
    if (graph.num_edges() == 0) { return; }

    for (auto v = 0; v < graph.num_vertices(); ++v) {
        if (graph.degree(v) % 2 != 0) { return; }
    }

    std::vector<std::deque<Edge>> adj(graph.num_vertices(), std::deque<Edge>{}); // deque as queue

    for (auto v = 0; v < graph.num_vertices(); ++v) {
        auto self_loops = 0;
        for (auto w : graph.adjacent(v)) {
            // careful with self loops
            if (v == w) {
                if (self_loops % 2 == 0) {
                    Edge e{v, w};
                    adj[v].push_back(e);
                    adj[w].push_back(e);
                }
                ++self_loops;
            } else if (v < w) {
                Edge e{v, w};
                adj[v].push_back(e);
                adj[w].push_back(e);
            }
        }
    }

    auto s = _non_isolated_vertex(graph);
    std::deque<int> stack; //
    stack.push_back(s);

    // dfs
    while (!stack.empty()) {
        auto v = stack.back();
        stack.pop_back();
        while (!adj[v].empty()) {
            auto edge = adj[v].front();
            adj[v].pop_front();
            if (edge.is_used) { continue; }
            edge.is_used = true;
            stack.push_back(v);
            v = edge.other(v);
        }
        _cycle.push_back(v);
    }

    if (_cycle.size() != graph.num_edges() + 1) { _cycle.clear(); }
}

static int Eulerian_cycle::_non_isolated_vertex(const Graph& graph)
{
    for (auto v = 0; v < graph.num_vertices(); ++v) {
        if (graph.degree(v) > 0) { return v; }
    }
    return -1;
}