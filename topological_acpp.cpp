#include <queue>

// for cycle finding -> Cycle, Directed_cycle, Directed_cycle_x, Directed_eulerian_cycle,
// Edge_weighted_directed_cycle, Eulerian_cycle
// chapter 19 - 6 7 8
template<typename Dag_type>
class Dag_topological_sort {
public:
    Dag_topological_sort(const Dag_type& digraph)
            : _digraph{digraph},
              _t_count{0},
              _count{0},
              _preorder(digraph.num_vertices(), -1),
              _postorder(digraph.num_vertices(), -1),
              _postorder_i(digraph.num_vertices(), -1)
    {
        for (int v = 0; v < digraph.num_vertices(); ++v) {
            if (_preorder[v] == -1) { _reverse_topological_sort(v); }
        }
    }

    int operator[](int v) const { return _postorder_i[v]; }

    int relabel(int v) const { return _postorder[v]; }

private:
    const Dag_type& _digraph;
    int _count;
    int _t_count;
    std::vector<int> _preorder;
    std::vector<int> _postorder;
    std::vector<int> _postorder_i;

    void _reverse_topological_sort(int v)
    {
        _preorder[v] = _count++;
        for (auto t : _digraph.adjacent(v)) {
            if (_preorder[t] == -1) { _reverse_topological_sort(t); }
        }
        _postorder[v] = _t_count;
        _postorder_i[_t_count++] = v;
    }

    // TODO: review differences here
    void _topological_sort(int v)
    {
        _preorder[v] = _count++;
        for (int w = 0; w < _digraph.num_vertices(); ++w) {
            if (_digraph.has_edge(w, v)) {
                if (_preorder[w] == -1) { _topological_sort(w); }
            }
        }
        _postorder[v] = _t_count;
        _postorder_i[_t_count++] = v;
    }
};

template<typename Dag_type>
class Dag_ts2 {
public:
    Dag_ts2(const Dag_type& digraph)
            : _digraph{digraph},
              _inorder{digraph.num_vertices(), 0},
              _topological_sort{digraph.num_vertices(), -1},
              _topological_sort_i{digraph.num_vertices(), -1}
    {
        std::queue<int> queue;

        for (int v{0}; v < digraph.num_vertices(); ++v) {
            for (auto t : _digraph.adjacent(v)) {
                _inorder[t]++;
            }
        }

        for (int v{0}; v < digraph.num_vertices(); ++v) {
            if (_inorder[v] == 0) { queue.push(v); }
        }

        for (int j{0}; !queue.empty(); ++j) {
            _topological_sort[j] = queue.front();
            queue.pop();
            _topological_sort_i[_topological_sort[j]] = j;
            for (auto t : digraph.adjacent(_topological_sort[j])) {
                if (--_inorder[t] == 0) { queue.push(t); }
            }
        }
    }

    int operator[](int v) const { return _topological_sort[v]; }

    int relabel(int v) const { return _topological_sort_i[v]; }

private:
    const Dag_type& _digraph;
    std::vector<int> _inorder;
    std::vector<int> _topological_sort;
    std::vector<int> _topological_sort_i;
};