#include "Flow_edge.h"

Flow_edge::Flow_edge(int v, int w, double capacity)
        : _v{v},
          _w{w},
          _capacity{capacity},
          _flow{0.0}
{
    if (v < 0) { throw std::invalid_argument{"Vertex name must be a non-negative integer"}; }
    if (w < 0) { throw std::invalid_argument{"Vertex name must be a non-negative integer"}; }
    if (capacity < 0.0) { throw std::invalid_argument{"Edge capacity must be non-negative"}; }
}

Flow_edge::Flow_edge(int v, int w, double capacity, double flow)
        : _v{v},
          _w{w},
          _capacity{capacity},
          _flow{flow}
{
    if (v < 0) { throw std::invalid_argument{"Vertex name must be a non-negative integer"}; }
    if (w < 0) { throw std::invalid_argument{"Vertex name must be a non-negative integer"}; }
    if (capacity < 0.0) { throw std::invalid_argument{"Edge capacity must be non-negative"}; }
    if (flow > capacity) { throw std::invalid_argument{"Flow exceeds capacity"}; }
    if (flow < 0.0) { throw std::invalid_argument{"Flow must be non-negative"}; }
}

int Flow_edge::other(int vertex) const
{
    if (vertex == _v) { return _w; }
    else if (vertex == _w) { return _v; }
    else { throw std::invalid_argument{"Illegal endpoint"}; }
}

double Flow_edge::residual_capacity_to(int vertex) const
{
    if (vertex == _v) {
        return _flow;
    } else if (vertex == _w) {
        return _capacity - _flow;
    } else { throw std::invalid_argument{"Illegal endpoint"}; }
}

void Flow_edge::add_residual_flow_to(int vertex, double delta)
{
    if (vertex == _v) { _flow -= delta; }
    else if (vertex == _w) { _flow += delta; }
    else { throw std::invalid_argument{"Illegal endpoint"}; }

    if (std::isnan(delta)) { throw std::invalid_argument("Change in flow = NaN"); }
    if (_flow < 0.0) { throw std::invalid_argument("Flow is negative"); }
    if (_flow > _capacity) { throw std::invalid_argument{"Flow exceeds capacity"}; }
}