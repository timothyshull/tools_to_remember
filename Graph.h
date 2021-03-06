#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_set>

class Graph {
private:
    std::size_t _num_vertices{0};
    std::size_t _num_edges{0};
    std::vector<std::unordered_set<int>> _adjacency_lists;

public:
    explicit Graph(std::size_t num_vertices);

    Graph() = default;

    Graph(const Graph&) = default;

    Graph(Graph&&) = default;

    ~Graph() = default;

    Graph& operator=(const Graph&) = default;

    Graph& operator=(Graph&&) = default;

    inline std::size_t num_vertices() const noexcept { return _num_vertices; }

    inline std::size_t num_edges() const noexcept { return _num_edges; }

    void add_edge(int v, int w);

    inline std::vector<int> const adjacent(int v) const { return {_adjacency_lists[v].begin(), _adjacency_lists[v].end()}; }

    inline std::size_t degree(int v) const noexcept { return _adjacency_lists[v].size(); }
};

#endif // GRAPH_H
