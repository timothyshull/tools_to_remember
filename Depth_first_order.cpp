#include "Depth_first_order.h"

Depth_first_order::Depth_first_order(const Digraph& digraph)
        : _marked{digraph.num_vertices()},
          _pre_num{digraph.num_vertices()},
          _post_num{digraph.num_vertices()},
          _preorder{},
          _postorder{},
          _pre_count{0},
          _post_count{0}
{
    for (auto v = 0; v < digraph.num_vertices(); ++v) {
        if (!_marked[v]) { _dfs(digraph, v); }
    }
}

void Depth_first_order::_dfs(const Digraph& digraph, int v)
{
    _marked[v] = true;
    _pre_num[v] = _pre_count++;
    _preorder.push_back(v);
    for (auto w : digraph.adjacent(v)) {
        if (!_marked[w]) { _dfs(digraph, w); }
    }
    _postorder.push_back(v);
    _post_num[v] = _post_count++;
}