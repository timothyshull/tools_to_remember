#include <vector>
#include <queue>

struct Edge {
    Edge(int src, int dest) : source{src}, destination{dest} {}

    Edge() = default;

    ~Edge() = default;

    int source;
    int destination;
};

// NOTE: this is the best approach for speed -> not graph copying
template<class Graph_type>
class Breadth_first_search {
public:
    Breadth_first_search(const Graph_type& graph)
            : _graph{graph},
              _order(graph.num_vertices(), -1),
              _count{0},
              _search_tree_parent(graph.num_vertices(), -1) { _search(); }

    int search_tree_parent(int v) const { return _search_tree_parent[v]; }

    int operator[](int v) const { return _order[v]; }

private:
    const Graph_type& _graph;
    int _count;
    std::vector<int> _order;
    std::vector<int> _search_tree_parent;

    void _search()
    {
        for (int v{0}; v < _graph.num_vertices(); ++v) {
            if (_order[v] == -1) { _search(Edge{v, v}); }
        }
    }

//    void _search(Edge& e)
//    {
//        std::queue<Edge> queue;
//        queue.push(e);
//
//        Edge tmp;
//        int v;
//        int w;
//        while (!queue.empty()) {
//            tmp = queue.front();
//            queue.pop();
//            if (_order[tmp.destination] == -1) {
//                v = tmp.source;
//                w = tmp.destination;
//                _order[w] = _count++;
//                st[w] = v;
//                for (auto t : _graph.adjacent(w)) {
//                    if (_order[t] == -1) { queue.push(Edge{w, t}); }
//                }
//            }
//        }
//    }

    // optimized
    void _search(Edge e)
    {
        std::queue<Edge> queue;
        queue.push(e);
        _order[e.destination] = _count++;

        Edge tmp;
        while (!queue.empty()) {
            tmp = queue.front();
            queue.pop();
            _search_tree_parent[tmp.destination] = tmp.source;
            for (auto t : _graph.adjacent(tmp.destination)) {
                if (_order[t] == -1) {
                    queue.push(Edge{e.destination, t});
                    _order[t] = _count++;
                }
            }
        }
    }
};