#ifndef TOOLS_TO_REMEMBER_DIRECTED_EDGE_H
#define TOOLS_TO_REMEMBER_DIRECTED_EDGE_H

#include <cmath>
#include <stdexcept>
#include <limits>

class Directed_edge {
private:
    const int _v;
    const int _w;
    const double _weight;

public:
    Directed_edge(int v, int w, double weight);

    Directed_edge() = delete;

    ~Directed_edge() = default;

    Directed_edge(const Directed_edge&) = default;

    Directed_edge(Directed_edge&&) = default;

    Directed_edge& operator=(const Directed_edge&) = default;

    Directed_edge& operator=(Directed_edge&&) = default;

    constexpr int from() const noexcept { return _v; }

    constexpr int to() const noexcept { return _w; }

    constexpr double weight() const noexcept { return _weight; }
};

#endif // TOOLS_TO_REMEMBER_DIRECTED_EDGE_H
