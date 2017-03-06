#include "Boruvka_mst.h"
Boruvka_mst::Boruvka_mst(const Edge_weighted_graph& graph)
{
    Union_find uf{graph.num_vertices()};

    for (auto t = 1; t < graph.num_vertices() && _mst.size() < graph.num_vertices() - 1; t = t + t) {

        std::vector<Edge> closest(graph.num_vertices());
        for (auto& e : graph.edges()) {
            auto v = e.either();
            auto w = e.other(v);
            auto i = uf.find(v);
            auto j = uf.find(w);
            if (i == j) { continue; }
            if (closest[i] == _default || e < closest[i]) { closest[i] = e; }
            if (closest[j] == _default || e < closest[j]) { closest[j] = e; }
        }

        for (auto i = 0; i < graph.num_vertices(); ++i) {
            auto e = closest[i];
            if (e != _default) {
                auto v = e.either();
                auto w = e.other(v);
                if (!uf.connected(v, w)) {
                    _mst.push_back(e);
                    _weight += e.weight();
                    uf.create_union(v, w);
                }
            }
        }
    }
}
