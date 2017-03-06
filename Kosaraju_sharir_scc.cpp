#include "Kosaraju_sharir_scc.h"

Kosaraju_sharir_scc::Kosaraju_sharir_scc(const Digraph& digraph)
        : _marked(digraph.num_vertices()),
          _id(digraph.num_vertices())
{
    auto reversed = digraph.reverse();
    Depth_first_order dfs{reversed};

    for (auto v : dfs.reverse_post()) {
        if (!_marked[v]) {
            _dfs(digraph, v);
            ++_count;
        }
    }
}

void Kosaraju_sharir_scc::_dfs(const Digraph& digraph, int v)
{
    _marked[v] = true;
    _id[v] = static_cast<int>(_count);
    for (auto w : digraph.adjacent(v)) {
        if (!_marked[w]) { _dfs(digraph, w); }
    }
}