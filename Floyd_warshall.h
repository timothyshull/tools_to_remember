#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include <vector>
#include "Directed_edge.h"
#include "Edge_weighted_digraph.h"
#include "Edge_weighted_directed_cycle.h"
#include "Adj_matrix_edge_weighted_digraph.h"

class Floyd_warshall {
private:
    const static double _inf = std::numeric_limits<double>::infinity();
    const static Directed_edge _default = Directed_edge{};
    bool _has_negative_cycle;
    std::vector<std::vector<double>> _dist_to;
    std::vector<std::vector<Directed_edge>> _edge_to;

public:
    Floyd_warshall(const Adj_matrix_edge_weighted_digraph& digraph);

    ~Floyd_warshall() = default;

    inline bool has_negative_cycle() const noexcept { return _has_negative_cycle; }

    std::vector<Directed_edge> negative_cycle();

    inline bool has_path(int s, int t) const noexcept { return _dist_to[s][t] < _inf; }

    double dist(int s, int t);

    std::vector<Directed_edge> path(int s, int t);
};

#endif // FLOYD_WARSHALL_H
