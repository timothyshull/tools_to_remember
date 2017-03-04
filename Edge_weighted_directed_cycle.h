#ifndef TOOLS_TO_REMEMBER_EDGE_WEIGHTED_DIRECTED_CYCLE_H
#define TOOLS_TO_REMEMBER_EDGE_WEIGHTED_DIRECTED_CYCLE_H

#include <deque>
#include <vector>
#include "Directed_edge.h"
#include "Edge_weighted_digraph.h"

class Edge_weighted_directed_cycle {
private:
    std::deque<bool> _marked;
    std::vector<Directed_edge> _edge_to;
    std::deque<bool> _on_stack;
    std::vector<Directed_edge> _cycle; // vector as stack -> push_back & pop_back

public:
    Edge_weighted_directed_cycle(const Edge_weighted_digraph& digraph);

    inline bool has_cycle() const noexcept { return !_cycle.empty(); }

    inline std::vector<Directed_edge> cycle() const { return _cycle; }

private:
    void _dfs(const Edge_weighted_digraph& digraph, int v);
};

#endif // TOOLS_TO_REMEMBER_EDGE_WEIGHTED_DIRECTED_CYCLE_H
