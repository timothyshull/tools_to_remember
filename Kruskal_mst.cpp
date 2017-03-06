#include "Kruskal_mst.h"

Kruskal_mst::Kruskal_mst(const Edge_weighted_graph& graph)
{
    std::priority_queue<Edge, std::greater<Edge>> pq;
    for (auto& e : graph.edges()) { pq.push(e); }

    Union_find uf{graph.num_vertices()};
    while (!pq.empty() && _mst.size() < graph.num_vertices() - 1) {
        auto e = pq.top();
        pq.pop();
        auto v = e.either();
        auto w = e.other(v);
        if (!uf.connected(v, w)) {
            uf.create_union(v, w);
            _mst.push_back(e);
            _weight += e.weight();
        }
    }
}
