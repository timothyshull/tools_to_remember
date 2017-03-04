#ifndef TOOLS_TO_REMEMBER_BIPARTITE_H
#define TOOLS_TO_REMEMBER_BIPARTITE_H

#include <deque>
#include "Graph.h"

class Bipartite {
private:
    bool _is_bipartite;
    std::deque<bool> _color;
    std::deque<bool> _marked;
    std::vector<int> _edge_to;
    std::vector<int> _cycle;

public:
    Bipartite(const Graph& graph);

    inline bool is_bipartite() const noexcept { return _is_bipartite; }

    bool color(int v) const;

    inline std::vector<int> odd_cycle() const { return _cycle; }

private:
    void _dfs(const Graph& graph, int v);
};

#endif // TOOLS_TO_REMEMBER_BIPARTITE_H
