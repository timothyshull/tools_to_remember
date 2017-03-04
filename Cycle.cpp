#include "Cycle.h"

Cycle::Cycle(const Graph& graph) :
        _marked(graph.num_vertices()),
        _has_cycle{false}
{
    for (auto v = 0; v < graph.num_vertices(); ++v) {
        if (!_marked[v]) { dfs(graph, -1, v); }
    }
}

void Cycle::dfs(const Graph& graph, int u, int v)
{
    _marked[v] = true;
    for (auto w : graph.adjacent(v)) {
        if (!_marked[w]) { dfs(graph, v, w); }
        else if (w != u) { _has_cycle = true; }
    }
}
