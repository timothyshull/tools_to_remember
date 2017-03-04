#ifndef TOOLS_TO_REMEMBER_CYCLE_H
#define TOOLS_TO_REMEMBER_CYCLE_H

#include <deque>
#include "Graph.h"

class Cycle {
private:
    std::deque<bool> _marked;
    bool _has_cycle;

public:
    Cycle(const Graph& graph);

    inline bool has_cycle() const noexcept { return _has_cycle; }

private:
    void dfs(const Graph& graph, int u, int v);
};

#endif // TOOLS_TO_REMEMBER_CYCLE_H
