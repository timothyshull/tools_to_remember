#ifndef DIRECTED_EULERIAN_CYCLE_H
#define DIRECTED_EULERIAN_CYCLE_H

#include <deque>
#include <vector>

#include "Digraph.h"

class Directed_eulerian_cycle {
private:
    std::deque<int> _cycle;

public:
    Directed_eulerian_cycle(const Digraph& digraph)
            : _cycle{}
    {
        if (digraph.num_edges() == 0) { return; }

        for (auto v = 0; v < digraph.num_vertices(); ++v) {
            if (digraph.outdegree(v) != digraph.indegree(v)) { return; }
        }

        std::vector<std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator>> adj(digraph.num_vertices());
        for (auto v = 0; v < digraph.num_vertices(); ++v) {
            auto t = digraph.adjacent(v);
            adj[v] = {t.begin(), t.end()};
        }

        auto s = _non_isolated_vertex(digraph);
        std::deque<int> stack;
        stack.push_back(s);

        while (!stack.empty()) {
            auto v = stack.back();
            stack.pop_back();
            while (adj[v].first != adj[v].second) {
                stack.push_back(v);
                v = *(++adj[v].first);
            }
            _cycle.push_back(v);
        }

        if (_cycle.size() != digraph.num_edges() + 1) { _cycle.clear(); }

    }

    inline std::vector<int> cycle() const { return {_cycle.begin(), _cycle.end()}; }

    inline bool has_eulerian_cycle() const noexcept { return !_cycle.empty(); }

private:
    static int _non_isolated_vertex(const Digraph& digraph)
    {
        for (auto v = 0; v < digraph.num_vertices(); ++v) {
            if (digraph.outdegree(v) > 0) { return v; }
        }
        return -1;
    }
};

#endif // DIRECTED_EULERIAN_CYCLE_H
