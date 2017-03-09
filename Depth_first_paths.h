#ifndef DEPTH_FIRST_PATHS_H
#define DEPTH_FIRST_PATHS_H

#include <deque>
#include "Graph.h"

class Depth_first_paths {
private:
    std::deque<bool> _marked;
    std::vector<int> _edge_to;
    int _source;
public:
    Depth_first_paths(const Graph& graph, int s);

    ~Depth_first_paths() = default;

    inline bool has_path_to(int v) const { return _marked[v]; }

    std::vector<int> path_to(int v) const;

private:
    void _dfs(const Graph& graph, int v);
};

#endif // DEPTH_FIRST_PATHS_H
