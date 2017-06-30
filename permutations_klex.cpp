#include <vector>
#include <numeric>
#include <iostream>

template<typename Item_type>
bool has_next_perm(std::vector<Item_type> &a)
{
    auto n = static_cast<int>(a.size());

    auto k = 0;
    for (k = n - 2; k >= 0; --k) {
        if (a[k] < a[k + 1]) { break; }
    }
    if (k == -1) { return false; }

    auto j = n - 1;
    while (a[k] > a[j]) {
        --j;
    }
    std::swap(a[j], a[k]);

    for (auto r = n - 1, s = k + 1; r > s; --r, (void) ++s) {
        std::swap(a[r], a[s]);
    }

    return true;
}

template<typename Item_type>
std::vector<std::vector<Item_type>> permutations_klex(const Item_type &n)
{
    auto a = std::vector<Item_type>(static_cast<typename std::vector<Item_type>::size_type>(n));
    std::iota(a.begin(), a.end(), 0);

    std::vector<std::vector<Item_type>> out;
    out.push_back(a);
    while (has_next_perm(a)) {
        out.push_back(a);
    }
    return out;
}

template<typename Bidir_it>
bool next_permutation(Bidir_it first, Bidir_it last)
{
    if (first == last) { return false; }
    auto i = last;
    if (first == --i) { return false; }

    while (true) {
        auto i1 = i;
        if (*--i < *i1) {
            auto i2 = last;
            while (!(*i < *--i2)) {}
            std::iter_swap(i, i2);
            std::reverse(i1, last);
            return true;
        }
        if (i == first) {
            std::reverse(first, last);
            return false;
        }
    }
}

template<typename Bidir_it>
bool prev_permutation(Bidir_it first, Bidir_it last)
{
    if (first == last) { return false; }
    auto i = last;
    if (first == --i) { return false; }

    while (true) {
        auto i1 = i;
        if (*i1 < *--i) {
            auto i2 = last;
            while (!(*--i2 < *i)) {}
            std::iter_swap(i, i2);
            std::reverse(i1, last);
            return true;
        }
        if (i == first) {
            std::reverse(first, last);
            return false;
        }
    }
}

int main()
{
    auto out = permutations_klex(4);
    for (const auto &v : out) {
        for (const auto &e : v) {
            std::cout << e << " ";
        }
        std::cout << "\n";
    }
    return 0;
}