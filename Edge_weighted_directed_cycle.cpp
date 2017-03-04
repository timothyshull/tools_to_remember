#include "Edge_weighted_directed_cycle.h"

Edge_weighted_directed_cycle::Edge_weighted_directed_cycle(const Edge_weighted_digraph& digraph)
        : _marked(digraph.num_vertices()),
          _edge_to(digraph.num_vertices()),
          _on_stack(digraph.num_vertices())
{
    for (auto v = 0; v < digraph.num_vertices(); ++v) {
        if (!_marked[v]) { _dfs(digraph, v); }
    }
}

void Edge_weighted_directed_cycle::_dfs(const Edge_weighted_digraph& digraph, int v)
{
    _on_stack[v] = true;
    _marked[v] = true;
    for (auto& e : digraph.adjacent(v)) {
        auto w = e.to();
        if (!_cycle.empty()) { return; }
        else if (!_marked[w]) {
            _edge_to[w] = e;
            _dfs(digraph, w);
        } else if (_on_stack[w]) {
            // cycle.clear();
            auto f = e;
            while (f.from() != w) {
                _cycle.push_back(f);
                f = _edge_to[f.from()];
            }
            _cycle.push_back(f);

            return;
        }
    }

    _on_stack[v] = false;
}