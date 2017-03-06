#include "Floyd_warshall.h"

Floyd_warshall::Floyd_warshall(const Adj_matrix_edge_weighted_digraph& digraph)
        : _dist_to(digraph.num_vertices(), std::vector<double>(digraph.num_vertices())),
          _edge_to(digraph.num_vertices(), std::vector<Directed_edge>(digraph.num_vertices()))
{
    auto num_vertices = digraph.num_vertices();

    for (auto v = 0; v < num_vertices; ++v) {
        for (auto w = 0; w < num_vertices; ++w) { _dist_to[v][w] = _inf; }
    }

    for (int v = 0; v < digraph.num_vertices(); v++) {
        for (auto& e : digraph.adjacent(v)) {
            _dist_to[e.from()][e.to()] = e.weight();
            _edge_to[e.from()][e.to()] = e;
        }
        // handle self loops
        if (_dist_to[v][v] >= 0.0) {
            _dist_to[v][v] = 0.0;
            _edge_to[v][v] = _default;
        }
    }

    for (int i = 0; i < num_vertices; i++) {
        for (int v = 0; v < num_vertices; v++) {
            if (_edge_to[v][i] == _default) { continue; }
            for (int w = 0; w < num_vertices; w++) {
                if (_dist_to[v][w] > _dist_to[v][i] + _dist_to[i][w]) {
                    _dist_to[v][w] = _dist_to[v][i] + _dist_to[i][w];
                    _edge_to[v][w] = _edge_to[i][w];
                }
            }
            if (_dist_to[v][v] < 0.0) {
                _has_negative_cycle = true;
                return;
            }
        }
    }
}

std::vector<Directed_edge> Floyd_warshall::negative_cycle()
{
    for (auto v = 0; v < _dist_to.size(); ++v) {
        if (_dist_to[v][v] < 0.0) {
            auto num_vertices = _edge_to.size();
            Edge_weighted_digraph spt(num_vertices);
            for (int w = 0; w < num_vertices; w++) {
                if (_edge_to[v][w] != _default) {
                    spt.add_edge(_edge_to[v][w]);
                }
            }
            Edge_weighted_directed_cycle finder{spt};
            if (!finder.has_cycle()) { throw std::runtime_error{"The graph must have a cycle to generate a negative cycle"}; }
            return finder.cycle();
        }
    }
    return {};
}

double Floyd_warshall::dist(int s, int t)
{
    if (has_negative_cycle()) { throw std::runtime_error{"Negative cost cycle exists"}; }
    return _dist_to[s][t];
}

std::vector<Directed_edge> Floyd_warshall::path(int s, int t)
{
    if (has_negative_cycle()) {
        throw std::runtime_error{"Negative cost cycle exists"};
    }
    if (!has_path(s, t)) { return {}; }
    std::vector<Directed_edge> path;
    for (auto e = _edge_to[s][t]; e != _default; e = _edge_to[s][e.from()]) { path.push_back(e); }
    return path;
}