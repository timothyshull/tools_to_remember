#ifndef DIJKSTRA_SP_H
#define DIJKSTRA_SP_H

#include <queue>
#include <vector>
#include <string>
#include "Directed_edge.h"
#include "Edge_weighted_digraph.h"
#include "Index_min_pq.h"

// TODO: check on and fix priority queue usage here -> also usage of double for pq type could just be int with static casts of edge weights
class Dijkstra_sp {
private:
    const static double _inf = std::numeric_limits<double>::infinity();
    const static Directed_edge _default = Directed_edge{};
    std::vector<double> _dist_to;
    std::vector<Directed_edge> _edge_to;
    Index_min_pq<double> _pq;

public:
    Dijkstra_sp(const Edge_weighted_digraph& digraph, int s);

    inline double dist_to(int v) const { return _dist_to[v]; }

    inline bool has_path_to(int v) const { return _dist_to[v] < _inf; }

    std::vector<Directed_edge> path_to(int v);

private:
    void _relax(Directed_edge e);
};

#endif // DIJKSTRA_SP_H
