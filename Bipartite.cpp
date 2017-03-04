#include "Bipartite.h"

Bipartite::Bipartite(const Graph& graph) :
        _is_bipartite{true},
        _color(graph.num_vertices(), false),
        _marked(graph.num_vertices(), false),
        _edge_to(graph.num_vertices()),
        _cycle{}
{
    for (auto v = 0; v < graph.num_vertices(); ++v) {
        if (!_marked[v]) { _dfs(graph, v); }
    }
}

bool Bipartite::color(int v) const
{
    if (!_is_bipartite) { throw std::runtime_error{"not bipartite"}; }
    return _color[v];
}

void Bipartite::_dfs(const Graph& graph, int v)
{
    _marked[v] = true;
    for (int w : graph.adjacent(v)) {
        if (!_cycle.empty()) { return; }
        if (!_marked[w]) {
            _edge_to[w] = v;
            _color[w] = !_color[v];
            _dfs(graph, w);
        } else if (_color[w] == _color[v]) {
            _is_bipartite = false;
            _cycle.push_back(w);
            for (auto x = v; x != w; x = _edge_to[x]) { _cycle.push_back(x); }
            _cycle.push_back(w);
        }
    }
}