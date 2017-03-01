#include <stack>
#include <vector>
#include <cassert>
#include <iostream>

class Digraph {
public:
    int num_vertices() const { return 0; }

    std::vector<int> adjacent(int v) const { return {}; }
};

class Directed_cycle {
public:
    Directed_cycle(const Digraph& digraph)
            : _marked(static_cast<std::deque<bool>::size_type>(digraph.num_vertices()), false),
              _on_stack(static_cast<std::deque<bool>::size_type>(digraph.num_vertices()), false),
              _marked(static_cast<std::vector<int>::size_type>(digraph.num_vertices()))
    {
        for (int v = 0; v < digraph.num_vertices(); ++v) {
            if (!_marked[v] && _cycle.empty()) { _dfs(digraph, v); }
        }
    }

    inline bool has_cycle() const { return !_cycle.empty(); }

    inline std::deque<int> cycle() const { return _cycle; }

private:
    std::deque<bool> _marked;
    std::vector<int> _edge_to;
    std::deque<bool> _on_stack;
    std::deque<int> _cycle; // used as a stack

    void _dfs(const Digraph& digraph, int vertex)
    {
        _on_stack[vertex] = true;
        _marked[vertex] = true;
        for (int w : digraph.adjacent(vertex)) {
            if (!_cycle.empty()) {
                return;
            } else if (!_marked[w]) {
                _edge_to[w] = vertex;
                _dfs(digraph, w);
            } else if (_on_stack[w]) {
                _cycle.clear();
                for (int x = vertex; x != w; x = _edge_to[x]) {
                    _cycle.push_front(x);
                }
                _cycle.push_front(w);
                _cycle.push_front(vertex);
                assert(this->_check());
            }
        }
        _on_stack[vertex] = false;
    }

    bool _check()
    {
        if (has_cycle()) {
            int first{-1};
            int last{-1};
            for (int v : _cycle) {
                if (first == -1) { first = v; }
                last = v;
            }
            if (first != last) {
                std::cerr << "cycle begins with " << first << " and ends with " << last << "\n";
                return false;
            }
        }

        return true;
    }
};