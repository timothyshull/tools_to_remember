#ifndef CYCLE_H
#define CYCLE_H

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

#endif // CYCLE_H
