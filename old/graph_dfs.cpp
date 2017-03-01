#include <vector>
#include <iostream>

struct Edge {
    Edge(int src, int dest) : source{src}, destination{dest} {}

    Edge() = default;

    ~Edge() = default;

    int source;
    int destination;
};

// Program 19.2 - Digraph DFS trace
template<class Graph>
class Depth_first_search {
public:
    Depth_first_search(const Graph& graph)
            : _graph{graph},
              _count{0},
              _count_p{0},
              _preorder(graph.num_vertices(), -1),
              _postorder(graph.num_vertices(), -1)
    {
        for (int v = 0; v < graph.num_vertices(); ++v) {
            if (_preorder[v] == -1) {
                Edge e{v, v};
                _recursive_dfs(e);
            }
        }
    }

private:
    const Graph& _graph;
    int _depth;
    int _count;
    int _count_p;
    std::vector<int> _preorder;
    std::vector<int> _postorder;

    void _show(std::string& s, Edge& e)
    {
        for (int i = 0; i < _depth; ++i) {
            std::cout << "  ";
        }
        std::cout << e.source << "-" << e.source << s << "\n";
    }

    void _show(std::string&& s, Edge& e) { _show(s, e); }

    void _recursive_dfs(Edge& e)
    {
        int w{e.destination};
        _show(" tree", e);
        _preorder[w] = _count++;
        ++_depth;
        for (auto t : _graph.adjacent(w)) {
            Edge x{w, t};
            if (_preorder[t] == -1) { _recursive_dfs(x); }
            else if (_postorder[t] == -1) { _show(" back", x); }
            else if (_preorder[t] > _preorder[w]) { _show(" down", x); }
            else { _show(" cross", x); }
        }
        _postorder[w] = _count_p++;
        --_depth;
    }
};

// 18.3
template<class Graph>
class DFS {
public:
    DFS(const Graph& graph)
            : _graph{graph},
              _order(graph.num_vertices(), -1),
              _count{0},
              _search_tree_parent(graph.num_vertices(), -1) { _search(); }

    int search_tree_parent(int v) const { return _search_tree_parent[v]; }

    int operator[](int v) const { return _order[v]; }

private:
    const Graph& _graph;
    int _count;
    std::vector<int> _order;
    std::vector<int> _search_tree_parent;

    void _search()
    {
        for (int v{0}; v < _graph.num_vertices(); ++v) {
            if (_order[v] == -1) { _search(Edge(v, v)); }
        }
    }

    void _search(Edge e)
    {
        int w{e.destination};
        _order[w] = _count++;
        _search_tree_parent[e.destination] = e.source;
        // typename Graph::adjIterator A(_graph, w);
        for (int t : _graph.adjacent(w)) {
            if (_order[t] == -1) { _search(Edge{w, t}); }
        }
    }
};