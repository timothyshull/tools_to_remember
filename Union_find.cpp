#include "Union_find.h"

Union_find::Union_find(std::size_t n)
        : _parent(n),
          _rank(n, 0),
          _count{n} { std::iota(_parent.begin(), _parent.end(), 0); }

int Union_find::find(int p)
{
    while (p != _parent[p]) {
        _parent[p] = _parent[_parent[p]];
        p = _parent[p];
    }
    return p;
}

void Union_find::create_union(int p, int q)
{
    auto root_p = find(p);
    auto root_q = find(q);
    if (root_p == root_q) { return; }

    if (_rank[root_p] < _rank[root_q]) { _parent[root_p] = root_q; }
    else if (_rank[root_p] > _rank[root_q]) { _parent[root_q] = root_p; }
    else {
        _parent[root_q] = root_p;
        ++_rank[root_p];
    }
    --_count;
}