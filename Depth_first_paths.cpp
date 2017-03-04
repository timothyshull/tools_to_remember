#include "Depth_first_paths.h"

Depth_first_paths::Depth_first_paths(const Graph& graph, int s)
        : _marked(graph.num_vertices()),
          _edge_to(graph.num_vertices()),
          _source{s} { _dfs(graph, s); }

std::vector<int> Depth_first_paths::path_to(int v) const
{
    if (!has_path_to(v)) { return {}; }
    std::vector<int> path;
    for (int x = v; x != _source; x = _edge_to[x]) { path.push_back(x); }
    path.push_back(_source);
    return path;
}

void Depth_first_paths::_dfs(const Graph& graph, int v)
{
    _marked[v] = true;
    for (auto w : graph.adjacent(v)) {
        if (!_marked[w]) {
            _edge_to[w] = v;
            _dfs(graph, w);
        }
    }
}
