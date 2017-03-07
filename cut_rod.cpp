#include <limits>
#include <vector>

// TODO: check on p
// top-down
std::size_t cut_rod(std::size_t size, std::size_t n, std::vector<std::size_t>& r)
{
    if (r[n] != std::numeric_limits<std::size_t>::max()) { return r[n]; }
    std::size_t q;
    if (n == 0) { q = 0; }
    else { q = std::numeric_limits<std::size_t>::max(); }
    for (auto i = 1; i < n + 1; ++i) { q = std::max(q, p[i] + cut_rod(p, n - 1, r)); }
    r[n] = q;
    return q;
}

std::size_t cut_rod(std::size_t size, std::size_t n)
{
    std::vector<std::size_t> r(n + 1, std::numeric_limits<std::size_t>::max());
    return cut_rod(size, n, r);
}

std::size_t cut_rod_bu(std::size_t size, std::size_t n)
{
    std::vector<std::size_t> r(n + 1, std::numeric_limits<std::size_t>::max());
    r[0] = 0;
    for (auto j = 1; j < n + 1; ++j) {
        auto q = std::numeric_limits<std::size_t>::max();
        for (auto i = 1; i < j; ++i) {
            q = std::max(q, p[i] + r[j - 1]);
        }
        r[j] = q;
    }
    return r[n];
}