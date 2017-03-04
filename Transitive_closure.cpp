#include "Transitive_closure.h"
Transitive_closure::Transitive_closure(const Digraph& digraph)
        : _tc(digraph.num_vertices())
{
    for (auto v = 0; v < digraph.num_vertices(); ++v) {
        _tc[v] = Directed_dfs(digraph, v);
    }
}