#ifndef TOOLS_TO_REMEMBER_TOPOLOGICAL_H
#define TOOLS_TO_REMEMBER_TOPOLOGICAL_H

#include <vector>
#include "Digraph.h"
#include "Directed_cycle.h"
#include "Depth_first_order.h"

class Topological {
private:
    std::vector<int> _order;
    std::vector<int> _rank;

public:
    Topological(const Digraph& digraph);

    inline std::vector<int> order() const { return _order; }

    inline bool has_topological_ordering() const { return !_order.empty(); }
};

#endif // TOOLS_TO_REMEMBER_TOPOLOGICAL_H
