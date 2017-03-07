#ifndef EULERIAN_CYCLE_H
#define EULERIAN_CYCLE_H

#include <deque>
#include "Graph.h"

class Eulerian_cycle {
private:
    std::deque<int> _cycle; // stack

    struct Edge {
        const int v;
        const int w;
        bool is_used;

        Edge(int v, int w);

        int other(int vertex);
    };

public:
    Eulerian_cycle(const Graph& graph)
            : _cycle{}
    {
        if (graph.num_edges() == 0) { return; }

        for (auto v = 0; v < graph.num_vertices(); ++v) {
            if (graph.degree(v) % 2 != 0) { return; }
        }

        std::vector<std::deque<Edge>> adj(graph.num_vertices(), std::deque<Edge>{}); // deque as queue

        for (auto v = 0; v < graph.num_vertices(); ++v) {
            auto self_loops = 0;
            for (auto w : graph.adjacent(v)) {
                // careful with self loops
                if (v == w) {
                    if (self_loops % 2 == 0) {
                        Edge e{v, w};
                        adj[v].push_back(e);
                        adj[w].push_back(e);
                    }
                    ++self_loops;
                } else if (v < w) {
                    Edge e{v, w};
                    adj[v].push_back(e);
                    adj[w].push_back(e);
                }
            }
        }

        auto s = _non_isolated_vertex(graph);
        std::deque<int> stack; //
        stack.push_back(s);

        // dfs
        while (!stack.empty()) {
            auto v = stack.back();
            stack.pop_back();
            while (!adj[v].empty()) {
                auto edge = adj[v].front();
                adj[v].pop_front();
                if (edge.is_used) { continue; }
                edge.is_used = true;
                stack.push_back(v);
                v = edge.other(v);
            }
            _cycle.push_back(v);
        }

        if (_cycle.size() != graph.num_edges() + 1) { _cycle.clear(); }
    }

    inline std::vector<int> cycle() const { return {_cycle.begin(), _cycle.end()}; }

    inline bool hash_eulerian_cycle() const noexcept { return !_cycle.empty(); }

private:
    static int _non_isolated_vertex(const Graph& graph)
    {
        for (auto v = 0; v < graph.num_vertices(); ++v) {
            if (graph.degree(v) > 0) { return v; }
        }
        return -1;
    }
};

#endif // EULERIAN_CYCLE_H
