#ifndef FLOW_EDGE_H
#define FLOW_EDGE_H

#include <stdexcept>
#include <cmath>

class Flow_edge {
private:
    const int _v;
    const int _w;
    const double _capacity;
    double _flow;

public:
    Flow_edge(int v, int w, double capacity);

    Flow_edge(int v, int w, double capacity, double flow);

    Flow_edge(const Flow_edge& e) = default;

    Flow_edge(Flow_edge&&) = default;

    ~Flow_edge() = default;

    Flow_edge& operator=(const Flow_edge&) = default;

    Flow_edge& operator=(Flow_edge&&) = default;

    inline int from() const noexcept { return _v; }

    inline int to() const noexcept { return _w; }

    inline double capacity() const noexcept { return _capacity; }

    inline double flow() const noexcept { return _flow; }

    int other(int vertex) const;

    double residual_capacity_to(int vertex) const;

    void add_residual_flow_to(int vertex, double delta);
};

#endif // FLOW_EDGE_H
