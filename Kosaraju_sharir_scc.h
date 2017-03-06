#ifndef TOOLS_TO_REMEMBER_KOSARAJU_SHARIR_SCC_H
#define TOOLS_TO_REMEMBER_KOSARAJU_SHARIR_SCC_H

#include <deque>
#include <vector>
#include "Digraph.h"
#include "Depth_first_order.h"

class Kosaraju_sharir_scc {
private:
    std::deque<bool> _marked;
    std::vector<int> _id;
    std::size_t _count;

public:
    Kosaraju_sharir_scc(const Digraph& digraph);

    ~Kosaraju_sharir_scc() = default;

    inline std::size_t count() const noexcept { return _count; }

    inline bool strongly_connected(int v, int w) const { return _id[v] == _id[w]; }

    inline int id(int v) const { return _id[v]; }

private:
    void _dfs(const Digraph& digraph, int v);
};

#endif // TOOLS_TO_REMEMBER_KOSARAJU_SHARIR_SCC_H
