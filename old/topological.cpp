#include <vector>
#include <string>
#include <queue>

class Digraph {
public:
    int num_vertices() const { return 0; }

    std::vector<int> adjacent(int v) const { return {}; }
};

class Topological {
public:
    Topological(const Digraph& digraph)
    {
        Directed_cycle finder{digraph};
        if (!finder.has_cycle()) {
            Depth_first_order dfs{digraph};
            _order = dfs.reverse_postorder();
            _rank = std::vector<int>(static_cast<std::vector<int>::size_type>(digraph.num_vertices()));
            int i{0};
            for (int v : _order) {
                _rank[v] = i++;
            }
        }
    }

    inline std::vector<int> order() const { return _order; }

    inline bool has_order() { return !_order.empty(); }

    // The the rank of vertex <tt>v</tt> in the topological order, -1 if the digraph is not a DAG
    int rank(int vertex)
    {
        validate_vertex(vertex);
        if (has_order()) { return _rank[vertex]; }
        else { return -1; }
    }

private:
    std::vector<int> _order;  // topological order
    std::vector<int> _rank;               // rank[v] = position of vertex v in topological order

    void validate_vertex(int v)
    {
        auto num_vertices = _rank.size();
        if (v < 0 || v >= num_vertices) {
            throw std::out_of_range{"vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(num_vertices - 1)};
        }
    }
};

std::vector<int> topological_sort(const Digraph& digraph)
{
    std::vector<int> count{static_cast<std::vector<int>::size_type>(digraph.num_vertices()), 0};
    int i;
    for (i = 0; i < digraph.num_vertices(); ++i) {
        for (auto v : digraph.adjacent(i)) { ++count[v]; }
    }

    std::queue<int> queue;
    for (i = 0; i < digraph.num_vertices(); ++i) {
        if (count[i] == 0) {
            queue.push(i);
        }
    }

    int v;
    std::vector<int> sorted;
    while (!queue.empty()) {
        v = queue.front();
        queue.pop();
        sorted.emplace_back(v);
        for (auto w : digraph.adjacent(v)) {
            --count[w];
            if (count[w] == 0) {
                queue.push(w);
            }
        }
    }
    return sorted;
}

// Sedgewick Topological x
std::vector<int> topological_sort(Digraph& digraph)
{
    std::vector<int> indegree(static_cast<std::vector<int>::size_type>(digraph.num_vertices()), 0);
    std::queue<int> queue;
    for (int i{0}; i < digraph.num_vertices(); ++i) {
        indegree[i] = digraph.indegree(i);
        if (indegree[i] == 0) { queue.push(i); }
    }

    std::vector<int> order;
    int count{0};

    while (!queue.empty()) {
        int v{queue.front()};
        queue.pop();
        order.emplace_back(v);
        ++count;
        for (auto w : digraph.adjacent(v)) {
            --indegree[w];
            if (indegree[w] == 0) queue.push(w);
        }
    }

    // directed cycle
    if (count != digraph.num_vertices()) { order.clear(); }
    return order;
}

// Python implementation
//std::vector<int> topological_sort(Digraph& digraph)
//{
//    std::vector<int> topological_order;
//    std::vector<int> ready;
//    std::vector<int> incount(static_cast<std::vector<int>::size_type>(digraph.num_vertices()), 0);
//    for (int i{0}; i < digraph.num_vertices(); ++i) {
//        incount[i] = digraph.indegree(i);
//        if (incount[i] == 0) { ready.emplace_back(i); }
//    }
//    while (!ready.empty()) {
//        int u{ready.back()};
//        ready.pop_back();
//        topological_order.emplace_back(u);
//        for (auto v : digraph.adjacent(u)) {
//            incount[v] -= 1;
//            if (incount[v] == 0) { ready.emplace_back(v); }
//        }
//    }
//    return topological_order;
//}
