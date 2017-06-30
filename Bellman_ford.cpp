#include "Bellman_ford.h"

Bellman_ford::Bellman_ford(const Edge_weighted_digraph& digraph, int s)
        : _dist_to(digraph.num_vertices(), _inf),
          _edge_to(digraph.num_vertices()),
          _on_queue(digraph.num_vertices()),
          _queue{}
{
    _dist_to[s] = 0.0;

    // Bellman-Ford algorithm
    _queue.push_back(s);
    _on_queue[s] = true;
    while (!_queue.empty() && !has_negative_cycle()) {
        auto v = _queue.front();
        _queue.pop_front();
        _on_queue[v] = false;
        _relax(digraph, v);
    }

}

double Bellman_ford::distance_to(int v)
{
    if (has_negative_cycle()) { throw std::runtime_error{"Negative cost cycle exists"}; }
    return _dist_to[v];
}

std::vector<Directed_edge> Bellman_ford::path_to(int v)
{
    if (has_negative_cycle()) { throw std::runtime_error{"Negative cost cycle exists"}; }
    if (!has_path_to(v)) { return {}; }
    std::vector<Directed_edge> path;
    for (auto e = _edge_to[v]; e != _default; e = _edge_to[e.from()]) { path.push_back(e); }
    return path;
}

void Bellman_ford::_relax(const Edge_weighted_digraph& digraph, int v)
{
    for (auto& e : digraph.adjacent(v)) {
        auto w = e.to();
        if (_dist_to[w] > _dist_to[v] + e.weight()) {
            _dist_to[w] = _dist_to[v] + e.weight();
            _edge_to[w] = e;
            if (!_on_queue[w]) {
                _queue.push_back(w);
                _on_queue[w] = true;
            }
        }
        if (_cost++ % digraph.num_vertices() == 0) {
            _find_negative_cycle();
            if (has_negative_cycle()) { return; }
        }
    }
}

void Bellman_ford::_find_negative_cycle()
{
    auto num_vertices = _edge_to.size();
    Edge_weighted_digraph spt{num_vertices};
    for (auto v = 0; v < num_vertices; ++v) {
        if (_edge_to[v] != _default) {
            spt.add_edge(_edge_to[v]);
        }
    }

    Edge_weighted_directed_cycle finder{spt};
    _cycle = finder.cycle();
}