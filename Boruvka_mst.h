#ifndef TOOLS_TO_REMEMBER_BORUVKA_MST_H
#define TOOLS_TO_REMEMBER_BORUVKA_MST_H

#include <limits>
#include <vector>
#include "Edge_weighted_graph.h"
#include "Union_find.h"
#include "Edge.h"

class Boruvka_mst {
private:
    const static double _epsilon = std::numeric_limits<double>::epsilon();
    const static Edge _default = Edge{};

    std::vector<Edge> _mst;
    double _weight;

public:
    Boruvka_mst(const Edge_weighted_graph& graph);

    ~Boruvka_mst() = default;

    inline std::vector<Edge> edges() const noexcept { return _mst; }

    inline double weight() const noexcept { return _weight; }
};

#endif // TOOLS_TO_REMEMBER_BORUVKA_MST_H
