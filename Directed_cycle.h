#ifndef DIRECTED_CYCLE_H
#define DIRECTED_CYCLE_H

#include <deque>
#include "Digraph.h"

class Directed_cycle {
private:
    std::deque<bool> _marked;
    std::vector<int> _edge_to;
    std::deque<bool> _on_stack;
    std::vector<int> _cycle;

public:
    Directed_cycle(const Digraph& digraph);

    inline bool has_cycle() const noexcept { return !_cycle.empty(); }

    inline std::vector<int> cycle() const { return _cycle; }

private:
    void _dfs(const Digraph& digraph, int v);
};

#endif // DIRECTED_CYCLE_H
