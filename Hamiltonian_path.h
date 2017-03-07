// Program 17.17 - Hamilton path
#ifndef HAMILTONIAN_PATH_H
#define HAMILTONIAN_PATH_H

#include <vector>

template<typename Graph_type>
class Hamiltonian_path {
private:
    const Graph_type& _graph;
    std::vector<bool> _visited;
    bool _found;

public:
    Hamiltonian_path(const Graph_type& graph, int v, int w, int dist)
            : _graph{graph},
              _visited(graph.num_vertices(), false) { _found = _dfs(v, w, dist); }

    ~Hamiltonian_path() = default;

    inline bool exists() const noexcept { return _found; }

private:

    bool _dfs(int v, int w, int dist)
    {
        if (v == w) { return (dist == 0); }
        _visited[v] = true;
        for (auto t : _graph.adjacent(v)) {
            if (!_visited[t]) { if (_dfs(t, w, dist - 1)) { return true; }}
        }
        _visited[v] = false;
        return false;
    }
};

#endif // HAMILTONIAN_PATH_H
