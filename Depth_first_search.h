#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H

#include <deque>

#include "Graph.h"

class Depth_first_search {
private:
    std::deque<bool> _visited;
    std::size_t _count;

public:
    Depth_first_search(Graph& graph, int s);

    ~Depth_first_search() = default;

    Depth_first_search() = delete;

    Depth_first_search(const Depth_first_search&) = delete;

    Depth_first_search(Depth_first_search&&) = delete;

    Depth_first_search& operator=(const Depth_first_search&) = delete;

    Depth_first_search& operator=(Depth_first_search&&) = delete;

    inline bool visited(int w) const { return _visited[w]; }

    inline std::size_t count() const { return _count; };

private:
    void _dfs(Graph& graph, int v);
};

#endif // DEPTH_FIRST_SEARCH_H
