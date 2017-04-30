#ifndef BREADTH_FIRST_PATHS_H
#define BREADTH_FIRST_PATHS_H

#include <limits>
#include <deque>
#include <queue>

#include "Graph.h"

class Breadth_first_paths {
private:
    const static int _inf{std::numeric_limits<int>::max()};
    std::deque<bool> _marked;
    std::vector<int> _edge_to;
    std::vector<int> _dist_to;

public:
    Breadth_first_paths(const Graph& graph, int s);

    ~Breadth_first_paths() = default;

    bool has_path_to(int v) const { return _marked[v]; }

    int dist_to(int v) const { return _dist_to[v]; }

private:
    void _bfs(const Graph &graph, int s);
};

#endif // BREADTH_FIRST_PATHS_H
