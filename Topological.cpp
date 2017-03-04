#include "Topological.h"

Topological::Topological(const Digraph& digraph) : _rank{digraph.num_vertices()}
{
    Directed_cycle finder{digraph};
    if (!finder.has_cycle()) {
        Depth_first_order dfs{digraph};
        _order = dfs.reverse_post();
        int i = 0;
        for (auto v : _order) { _rank[v] = i++; }
    }
}
