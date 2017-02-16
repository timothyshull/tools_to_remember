#include <deque>
#include <stack>
#include <vector>

class Graph {
public:
    int num_vertices() const { return 0; };

    std::vector<int> adjacent(int vertex) const { return {}; };
};

class Cycle {
public:
    Cycle(const Graph& graph)
            : _marked(static_cast<std::deque<bool>::size_type>(graph.num_vertices()), false),
              _edge_to(static_cast<std::vector<int>::size_type>(graph.num_vertices()))
    {
        if (_has_self_loop(graph)) { return; }
        if (_has_parallel_edges(graph)) { return; }
        for (int v = 0; v < graph.num_vertices(); ++v) {
            if (!_marked[v]) {
                _dfs(graph, -1, v);
            }
        }
    }

    inline bool has_cycle() const { return !_cycle.empty(); }

    inline std::deque<int> cycle() const { return _cycle; }

private:
    std::deque<bool> _marked;
    std::vector<int> _edge_to;
    std::deque<int> _cycle; // used as a stack

    bool _has_self_loop(const Graph& graph)
    {
        for (int v = 0; v < graph.num_vertices(); ++v) {
            for (int w : graph.adjacent(v)) {
                if (v == w) {
                    _cycle.clear();
                    _cycle.push_front(v);
                    _cycle.push_front(v);
                    return true;
                }
            }
        }
        return false;
    }

    bool _has_parallel_edges(const Graph& graph)
    {
        _marked = std::deque<bool>(static_cast<std::deque<bool>::size_type>(graph.num_vertices()), false);

        for (int v = 0; v < graph.num_vertices(); ++v) {

            for (int w : graph.adjacent(v)) {
                if (_marked[w]) {
                    _cycle.clear();
                    _cycle.push_front(v);
                    _cycle.push_front(w);
                    _cycle.push_front(v);
                    return true;
                }
                _marked[w] = true;
            }

            for (int w : graph.adjacent(v)) {
                _marked[w] = false;
            }
        }
        return false;
    }

    void _dfs(const Graph& graph, int u, int v)
    {
        _marked[v] = true;
        for (int w : graph.adjacent(v)) {
            if (!_cycle.empty()) { return; }

            if (!_marked[w]) {
                _edge_to[w] = v;
                _dfs(graph, v, w);
            } else if (w != u) {
                _cycle.clear();
                for (int x{v}; x != w; x = _edge_to[x]) {
                    _cycle.push_front(x);
                }
                _cycle.push_front(w);
                _cycle.push_front(v);
            }
        }
    }
};