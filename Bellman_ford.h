#ifndef TOOLS_TO_REMEMBER_BELLMAN_FORD_H
#define TOOLS_TO_REMEMBER_BELLMAN_FORD_H

#include <vector>
#include <deque>
#include "Directed_edge.h"
#include "Edge_weighted_digraph.h"
#include "Edge_weighted_directed_cycle.h"

class Bellman_ford {
private:
    const static double _inf = std::numeric_limits<double>::infinity();
    const static Directed_edge _default = Directed_edge{};
    std::vector<double> _dist_to;
    std::vector<Directed_edge> _edge_to;
    std::deque<bool> _on_queue;
    std::deque<int> _queue; // queue
    int _cost;
    std::vector<Directed_edge> _cycle;

public:
    Bellman_ford(const Edge_weighted_digraph& digraph, int s);

    ~Bellman_ford() = default;

    inline bool has_negative_cycle() const noexcept { return !_cycle.empty(); }

    inline std::vector<Directed_edge> negative_cycle() const { return _cycle; }

    double distance_to(int v);

    inline bool has_path_to(int v) const { return _dist_to[v] < _inf; }

    std::vector<Directed_edge> path_to(int v);

private:
    void _relax(const Edge_weighted_digraph& digraph, int v);

    void _find_negative_cycle();
};

#endif // TOOLS_TO_REMEMBER_BELLMAN_FORD_H
