#include <deque>

template<typename Graph_type>
class Simple_path {
public:
    Simple_path(const Graph_type& graph, int source, int destination)
            : _graph{graph},
              _visited{graph.num_vertices(), false}
    {
        _found = _search(source, destination);
    }

    inline bool exists() const { return _found; }

private:
    const Graph_type& _graph;
    std::deque<bool> _visited;
    bool _found;

    bool _search(int v, int w)
    {
        if (v == w) { return true; }
        _visited[v] = true;
        for (auto t : _graph.adjacent(v)) {
            if (!_visited[t]) {
                if (_search(t, w)) { return true; }
            }
        }
        return false;
    }
};
