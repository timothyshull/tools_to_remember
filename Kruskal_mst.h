#ifndef TOOLS_TO_REMEMBER_KRUSKAL_MST_H
#define TOOLS_TO_REMEMBER_KRUSKAL_MST_H

#include <limits>
#include <deque>
#include <functional>
#include <queue>

#include "Edge.h"
#include "Edge_weighted_graph.h"
#include "Union_find.h"

class Kruskal_mst {
private:
    const static double _epsilon = std::numeric_limits<double>::epsilon();
    double _weight;
    std::deque<Edge> _mst;

public:
    Kruskal_mst(const Edge_weighted_graph& graph);

    ~Kruskal_mst() = default;

    inline std::vector<Edge> edges() const { return {_mst.begin(), _mst.end()}; }

    inline double weight() const noexcept { return _weight; }
};

#endif // TOOLS_TO_REMEMBER_KRUSKAL_MST_H
