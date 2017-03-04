#include "Directed_dfs.h"

Directed_dfs::Directed_dfs(const Digraph& digraph, int s)
        : _marked(digraph.num_vertices()) { _dfs(digraph, s); }

void Directed_dfs::_dfs(const Digraph& digraph, int v)
{
    ++_count;
    _marked[v] = true;
    for (auto w : digraph.adjacent(v)) {
        if (!_marked[w]) { _dfs(digraph, w); }
    }
}