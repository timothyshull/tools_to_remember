#ifndef TOOLS_TO_REMEMBER_DIRECTED_DFS_H
#define TOOLS_TO_REMEMBER_DIRECTED_DFS_H

#include <deque>
#include "Digraph.h"

class Directed_dfs {

private:
    std::deque<bool> _marked;
    std::size_t _count;

public:
    Directed_dfs(const Digraph& digraph, int s);

    inline bool marked(int v) const { return _marked[v]; }

    inline std::size_t count() const { return _count; }

private:
    void _dfs(const Digraph& digraph, int v);
};

#endif // TOOLS_TO_REMEMBER_DIRECTED_DFS_H
