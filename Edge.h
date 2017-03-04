#ifndef TOOLS_TO_REMEMBER_EDGE_H
#define TOOLS_TO_REMEMBER_EDGE_H

#include <stdexcept>
#include <cmath>

class Edge {
private:
    const int _v;
    const int _w;
    const double _weight;

public:
    Edge(int v, int w, double weight);

    Edge();

    ~Edge() = default;

    constexpr double weight() const noexcept { return _weight; }

    constexpr int from() const noexcept { return _v; }

    constexpr int to() const noexcept { return _w; }

    constexpr int either() const noexcept { return _v; }

    int other(int vertex);

    inline bool operator==(const Edge& rhs) const noexcept { return _v == rhs._v && _w == rhs._w && _weight == rhs._weight; }

    inline bool operator!=(const Edge& rhs) const noexcept { return !(rhs == *this); }

    bool operator<(const Edge& rhs) const noexcept;

    inline bool operator>(const Edge& rhs) const noexcept { return rhs < *this; }

    inline bool operator<=(const Edge& rhs) const noexcept { return !(rhs < *this); }

    inline bool operator>=(const Edge& rhs) const noexcept { return !(*this < rhs); }
};

#endif // TOOLS_TO_REMEMBER_EDGE_H
