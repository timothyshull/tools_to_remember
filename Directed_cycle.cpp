#include "Directed_cycle.h"

Directed_cycle::Directed_cycle(const Digraph& digraph)
        : _marked(digraph.num_vertices(), false),
          _edge_to(digraph.num_vertices()),
          _on_stack(digraph.num_vertices(), false),
          _cycle{}
{
    for (auto v = 0; v < digraph.num_vertices(); ++v) {
        if (!_marked[v] && _cycle.empty()) { _dfs(digraph, v); }
    }
}

void Directed_cycle::_dfs(const Digraph& digraph, int v)
{
    _on_stack[v] = true;
    _marked[v] = true;
    for (auto w : digraph.adjacent(v)) {
        if (!_cycle.empty()) { return; }
        else if (!_marked[w]) {
            _edge_to[w] = v;
            _dfs(digraph, w);
        } else if (_on_stack[w]) {
            for (auto x = v; x != w; x = _edge_to[x]) { _cycle.push_back(x); }
            _cycle.push_back(w);
            _cycle.push_back(v);
        }
    }
    _on_stack[v] = false;
}