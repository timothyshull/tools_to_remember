#ifndef TOOLS_TO_REMEMBER_DIGRAPH_H
#define TOOLS_TO_REMEMBER_DIGRAPH_H

#include <unordered_set>
#include <vector>

class Digraph {

private:
    const std::size_t _num_vertices;
    std::size_t _num_edges;
    std::vector<std::unordered_set<int>> _adjacency_lists;

public:
    Digraph(std::size_t num_vertices);

    inline std::size_t num_vertices() const noexcept { return _num_vertices; }

    inline std::size_t num_edges() const noexcept { return _num_edges; }

    void add_edge(int v, int w);

    inline std::vector<int> adjacent(int v) const { return {_adjacency_lists[v].begin(), _adjacency_lists[v].end()}; }

    Digraph reverse();
};

#endif // TOOLS_TO_REMEMBER_DIGRAPH_H