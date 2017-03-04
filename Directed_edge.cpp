#include "Directed_edge.h"

Directed_edge::Directed_edge(int v, int w, double weight)
        : _v{v},
          _w{w},
          _weight{weight}
{
    if (v < 0) { throw std::out_of_range{"Vertex names must be nonnegative integers"}; }
    if (w < 0) { throw std::out_of_range{"Vertex names must be nonnegative integers"}; }
    if (std::isnan(weight)) { throw std::invalid_argument{"Weight is NaN"}; }
}