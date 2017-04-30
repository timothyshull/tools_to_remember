#ifndef DFS_EDGE_CLASSIFICATION_H
#define DFS_EDGE_CLASSIFICATION_H

#include <vector>
#include <iostream>

template<typename Graph_type>
class Dfs_edge_classification {
private:
    const Graph_type &_graph;
    std::vector<int> _preorder;
    std::vector<int> _postorder;
    int _depth{0};
    int _pre_count{0};
    int _post_count{0};

public:
    Dfs_edge_classification(const Graph_type &graph)
            : _graph{graph},
              _preorder(graph.num_vertices(), -1),
              _postorder(graph.num_vertices(), -1)
    {
        for (auto v = 0; v < graph.num_vertices(); ++v) {
            if (_preorder[v] == -1) {
                _dfs(v, v);
            }
        }
    }

    ~Dfs_edge_classification() = default;

private:
    void _show(std::string &&edge_type, int v, int w)
    {
        for (auto i = 0; i < _depth; ++i) {
            std::cout << "  ";
        }
        std::cout << edge_type << "(" << v << ", " << w << ")\n";
    }

    void _dfs(int v, int w)
    {
        _show("Tree_edge", v, w);
        _preorder[w] = _pre_count++;
        ++_depth;
        for (const auto x : _graph.adjacent(w)) {
            if (_preorder[x] == -1) {
                _dfs(w, x);
            } else if (_postorder[x] == -1) {
                _show("Back_edge", w, x);
            } else if (_preorder[w] < _preorder[x]) {
                _show("Down_edge", w, x);
            } else {
                _show("Cross_edge", w, x);
            }
        }
        _postorder[w] = _post_count++;
        --_depth;
    }
};

#endif // DFS_EDGE_CLASSIFICATION_H
