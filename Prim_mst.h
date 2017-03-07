#ifndef PRIM_MST_H
#define PRIM_MST_H

#include <limits>
#include <vector>
#include <deque>
#include <queue>

#include "Edge.h"
#include "Edge_weighted_graph.h"
#include "Index_min_pq.h"

class Prim_mst {
private:
    const static double _epsilon = std::numeric_limits<double>::epsilon();
    const static Edge _default = Edge{};
    const static double _inf = std::numeric_limits<double>::infinity();
    std::vector<Edge> _edge_to;
    std::vector<double> _dist_to;
    std::deque<bool> _marked;
    Index_min_pq<double, std::greater<double>> _pq;

public:
    Prim_mst(const Edge_weighted_graph& graph)
            : _edge_to(graph.num_vertices()),
              _dist_to(graph.num_vertices(), _inf),
              _marked(graph.num_vertices()),
              _pq(graph.num_vertices())
    {
        for (auto v = 0; v < graph.num_vertices(); ++v) {
            if (!_marked[v]) { _prim(graph, v); }
        }
    }

    std::vector<Edge> edges()
    {
        std::vector<Edge> mst(_edge_to.size());
        for (auto v = 0; v < _edge_to.size(); ++v) {
            auto e = _edge_to[v];
            if (e != _default) { mst.push_back(e); }
        }
        return mst;
    }

    double weight()
    {
        auto weight = 0.0;
        for (auto& e : edges()) { weight += e.weight(); }
        return weight;
    }

private:
    void _prim(const Edge_weighted_graph& graph, int s)
    {
        _dist_to[s] = 0.0;
        _pq.insert(static_cast<std::size_t>(s), _dist_to[s]);
        while (!_pq.empty()) {
            auto v = _pq.delete_min();
            _scan(graph, static_cast<int>(v));
        }
    }

    void _scan(const Edge_weighted_graph& graph, int v)
    {
        _marked[v] = true;
        for (auto& e : graph.adjacent(v)) {
            std::size_t w = static_cast<std::size_t>(e.other(v));
            if (_marked[w]) { continue; }
            if (e.weight() < _dist_to[w]) {
                _dist_to[w] = e.weight();
                _edge_to[w] = e;
                if (_pq.contains(w)) { _pq.decrease_key(w, _dist_to[w]); }
                else { _pq.insert(w, _dist_to[w]); }
            }
        }
    }

};

#endif // PRIM_MST_H
