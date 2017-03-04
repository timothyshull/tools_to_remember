#include "Connected_component.h"

Connected_component::Connected_component(const Graph& graph)
        : _marked(graph.num_vertices()),
          _id(graph.num_vertices()),
          _count{0}
{
    for (auto v = 0; v < graph.num_vertices(); ++v) {
        if (!_marked[v]) {
            _dfs(graph, v);
            ++_count;
        }
    }
}

void Connected_component::_dfs(const Graph& graph, int v)
{
    _marked[v] = true;
    _id[v] = static_cast<int>(_count);
    for (auto w : graph.adjacent(v)) {
        if (!_marked[w]) { _dfs(graph, w); }
    }
}