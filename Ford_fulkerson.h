#ifndef FORD_FULKERSON_H
#define FORD_FULKERSON_H

#include <deque>
#include <vector>
#include <iostream>
#include <cmath>

#include "Flow_network.h"
#include "Flow_edge.h"

class Ford_fulkerson {
private:
    static const double _epsilon = std::numeric_limits<double>::epsilon();
    static const double _inf = std::numeric_limits<double>::infinity();
    std::deque<bool> _marked;
    std::vector<Flow_edge> _edge_to;
    double _value;

public:
    Ford_fulkerson(const Flow_network& network, int s, int t);

    ~Ford_fulkerson() = default;

    inline double value() const noexcept { return _value; }

    // validate vertex
    inline bool in_cut(int v) const { return _marked[v]; }

private:
    bool _has_augmenting_path(const Flow_network& network, int s, int t);

    double _excess(const Flow_network& network, int v);

    bool _is_feasible(const Flow_network& network, int s, int t);
};

#endif // FORD_FULKERSON_H
