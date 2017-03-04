#include "Breadth_first_paths.h"

Breadth_first_paths::Breadth_first_paths(const Graph& graph, int s) :
        _marked(graph.num_vertices(), false),
        _dist_to(graph.num_vertices(), _inf),
        _edge_to(graph.num_vertices()) { bfs(graph, s); }

void Breadth_first_paths::bfs(const Graph& graph, int s)
{
    std::queue<int> q;
    _dist_to[s] = 0;
    _marked[s] = true;
    q.push(s);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        for (auto w : graph.adjacent(v)) {
            if (!_marked[w]) {
                _edge_to[w] = v;
                _dist_to[w] = _dist_to[v] + 1;
                _marked[w] = true;
                q.push(w);
            }
        }
    }
}
