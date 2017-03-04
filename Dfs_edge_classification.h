#ifndef TOOLS_TO_REMEMBER_DFS_EDGE_CLASSIFICATION_H
#define TOOLS_TO_REMEMBER_DFS_EDGE_CLASSIFICATION_H

#include <vector>
#include <iostream>

template<typename Graph_type>
class Dfs_edge_classification {
private:
    const Graph_type& _graph;
    int _depth;
    int _count_pre;
    int _count_post;
    std::vector<int> _preorder;
    std::vector<int> _postorder;

public:
    Dfs_edge_classification(const Graph_type& graph)
            : _graph{graph},
              _count_pre{0},
              _count_post{0},
              _preorder(graph.num_vertices(), -1),
              _postorder(graph.num_vertices(), -1)
    {
        for (auto v = 0; v < graph.num_vertices(); ++v) {
            if (_preorder[v] == -1) { _dfs(v, v); }
        }
    }

private:
    void _show(std::string&& s, int source, int dest)
    {
        for (auto i = 0; i < _depth; ++i) { std::cout << "  "; }
        std::cout << s << "(" << source << ", " << dest << ")" << "\n";
    }

    void _dfs(int v, int w)
    {
        _show("Tree edge", v, w);
        _preorder[w] = _count_pre++;
        ++_depth;
        for (auto t : _graph.adjacent(w)) {
            if (_preorder[t] == -1) { _dfs(w, t); }
            else if (_postorder[t] == -1) { _show("Back edge", w, t); }
            else if (_preorder[t] > _preorder[w]) { _show("Down edge", w, t); }
            else { _show(" cross", w, t); }
        }
        _postorder[w] = _count_post++;
        --_depth;
    }
};

#endif // TOOLS_TO_REMEMBER_DFS_EDGE_CLASSIFICATION_H
