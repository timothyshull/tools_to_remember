#include "Dijkstra_sp.h"

Dijkstra_sp::Dijkstra_sp(const Edge_weighted_digraph& digraph, int s)
        : _dist_to(digraph.num_vertices(), _inf),
          _edge_to(digraph.num_vertices()),
          _pq(digraph.num_vertices())
{
    for (auto& e : digraph.edges()) {
        if (e.weight() < 0) {
            throw std::invalid_argument{"edge " + std::to_string(e.from()) + "-" + std::to_string(e.to()) + " has negative weight"};
        }
    }

    _dist_to[s] = 0.0;

    _pq.insert(static_cast<std::size_t>(s), _dist_to[s]);
    while (!_pq.empty()) {
        auto v = _pq.delete_min();
        for (auto& e : digraph.adjacent(static_cast<int>(v))) {
            _relax(e);
        }
    }
}

std::vector<Directed_edge> Dijkstra_sp::path_to(int v)
{
    if (!has_path_to(v)) { return {}; }
    std::vector<Directed_edge> path;
    for (auto& e = _edge_to[v]; e != _default; e = _edge_to[e.from()]) {
        path.push_back(e);
    }
    return path;
}

void Dijkstra_sp::_relax(Directed_edge e)
{
    auto v = e.from();
    auto w = e.to();
    if (_dist_to[w] > _dist_to[v] + e.weight()) {
        _dist_to[w] = _dist_to[v] + e.weight();
        _edge_to[w] = e;
        if (_pq.contains(w)) { _pq.decrease_key(w, _dist_to[w]); }
        else { _pq.insert(w, _dist_to[w]); }
    }
}