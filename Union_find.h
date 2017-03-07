#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <vector>
#include <numeric>

class Union_find {
private:
    std::vector<int> _parent;
    std::vector<short> _rank;
    std::size_t _count;

public:
    Union_find(std::size_t n);

    ~Union_find() = default;

    int find(int p);

    inline std::size_t count() const noexcept { return _count; }

    inline bool connected(int p, int q) { return find(p) == find(q); }

    void create_union(int p, int q);
};

#endif // UNION_FIND_H
