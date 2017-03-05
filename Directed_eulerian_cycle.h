#ifndef TOOLS_TO_REMEMBER_DIRECTED_EULERIAN_CYCLE_H
#define TOOLS_TO_REMEMBER_DIRECTED_EULERIAN_CYCLE_H

#include <deque>
#include "Digraph.h"

class Directed_eulerian_cycle {
private:
    std::deque<int> cycle;

public:
    Directed_eulerian_cycle(const Digraph& digraph)
    : cycle{}
    {

        if (digraph.num_edges() == 0) { return; }

        for (auto v = 0; v < digraph.num_vertices(); ++v) {
            if (digraph.outdegree(v) != digraph.indegree(v)) {
                return;
            }
        }

//        Iterator<Integer>[]
//        adj = (Iterator<Integer>[])
//        new Iterator[digraph.V()];
        for (auto v = 0; v < digraph.num_vertices(); ++v) {
            adj[v] = digraph.adjacent(v).iterator();
        }

        auto s = _non_isolated_vertex(digraph);
        std::deque<int> stack;
        stack.push_back(s);

        while (!stack.empty()) {
            auto v = stack.back();
            stack.pop_back();
            while (adj[v].hasNext()) {
                stack.push(v);
                v = adj[v].next();
            }
            cycle.push_back(v);
        }

        if (cycle.size() != digraph.num_edges() + 1) { cycle.clear(); }

    }

    std::vector<int> cycle() { return {cycle.begin(), cycle.end()}; }

    bool has_eulerian_cycle() { return !cycle.empty(); }

private:
    static int _non_isolated_vertex(const Digraph& digraph)
    {
        for (auto v = 0; v < digraph.num_vertices(); ++v) {
            if (digraph.outdegree(v) > 0) {
                return v;
            }
        }
        return -1;
    }
};

#endif // TOOLS_TO_REMEMBER_DIRECTED_EULERIAN_CYCLE_H
