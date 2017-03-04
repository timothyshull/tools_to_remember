#ifndef TOOLS_TO_REMEMBER_CONNECTED_COMPONENT_H
#define TOOLS_TO_REMEMBER_CONNECTED_COMPONENT_H

#include <deque>
#include <vector>
#include "Graph.h"

class Connected_component {
private:
    std::deque<bool> _marked;
    std::vector<int> _id;
    std::size_t _count;

public:
    Connected_component(const Graph& graph);

    inline int id(int v) const { return _id[v]; }

    inline std::size_t count() const noexcept { return _count; }

    inline bool connected(int v, int w) const { return _id[v] == _id[w]; }

private:
    void _dfs(const Graph& graph, int v);
};

#endif // TOOLS_TO_REMEMBER_CONNECTED_COMPONENT_H
