#include <limits>

#include "Edge.h"

Edge::Edge(int v, int w, double weight)
        : _v{v},
          _w{w},
          _weight{weight}
{
    if (v < 0) { throw std::out_of_range{"Vertex name must be a nonnegative integer"}; }
    if (w < 0) { throw std::out_of_range{"Vertex name must be a nonnegative integer"}; }
    if (std::isnan(weight)) { throw std::invalid_argument{"Weight is NaN"}; }
}

Edge::Edge() : _v{-1}, _w{-1}, _weight{std::numeric_limits<double>::infinity()} {}

int Edge::other(int vertex)
{
    if (vertex == _v) { return _w; }
    else if (vertex == _w) { return _v; }
    else { throw std::invalid_argument{"Illegal endpoint"}; }
}

bool Edge::operator<(const Edge& rhs) const noexcept
{
    if (_weight < rhs._weight) { return true; }
    if (rhs._weight < _weight) { return false; }
    if (_v < rhs._v) { return true; }
    if (rhs._v < _v) { return false; }
    return _w < rhs._w;
}