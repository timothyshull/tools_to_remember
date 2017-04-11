#include <string>
#include <iostream>
#include <vector>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

void string_permutations(std::string prefix, std::string s, std::vector<std::string> &v)
{
    auto n = s.size();
    if (n == 0) {
        v.push_back(prefix);
        return;
    }
    for (std::size_t i = 0; i < n; ++i) {
        string_permutations(prefix + s[i], s.substr(0, i) + s.substr(i + 1, n), v);
    }
}

std::vector<std::string> string_permutations(std::string &s)
{
    std::vector<std::string> v;
    string_permutations("", s, v);
    return v;
}

// n! permutations of the elements of vector a -> not in order
template<typename Item_type>
void permutations(std::vector<Item_type> &v, std::size_t n, std::vector<std::vector<Item_type>> &a)
{
    if (n == 1) {
        a.push_back(v);
        return;
    }
    // Heap's algorithm
    for (auto i = 0; i < n; ++i) {
        permutations(v, n - 1, a);
        // auto k = n % 2 ? 1 : i;
        auto k = n % 2 ? 0 : i;
        std::swap(v[k], v[n - 1]);
    }
}

template<typename Item_type>
std::vector<std::vector<Item_type>> permutations(std::vector<Item_type> v) // purposefully copied in
{
    std::vector<std::vector<Item_type>> p;
    permutations(v, v.size(), p);
    return p;
}

void johnson_trotter(int n, std::vector<int> &p, std::vector<int> &pi, std::vector<int> &dir)
{
    // base case - print out permutation
    if (n >= p.size()) {
        for (auto e : p) { std::cout << e << " "; }
        return;
    }

    johnson_trotter(n + 1, p, pi, dir);
    for (auto i = 0; i <= n - 1; ++i) {
        // swap
        std::cout << "    (" << pi[n] << " " << pi[n] + dir[n];
        auto z = p[pi[n] + dir[n]];
        p[pi[n]] = z;
        p[pi[n] + dir[n]] = n;
        pi[z] = pi[n];
        pi[n] = pi[n] + dir[n];

        johnson_trotter(n + 1, p, pi, dir);
    }
    dir[n] = -dir[n];
}

void johnson_trotter(std::size_t n)
{
    std::vector<int> p(n); // permutation
    std::vector<int> pi(n); // inverse permutation
    std::vector<int> dir(n); // direction = +1 or -1
    for (auto i = 0; i < n; ++i) {
        dir[i] = -1;
        p[i] = i;
        pi[i] = i;
    }
    johnson_trotter(0, p, pi, dir);
    std::cout << "    (0 1)\n";
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

template<typename Item_type>
bool next_permutation(std::vector<Item_type> &v)
{
    auto first = v.begin();
    auto last = v.end();

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

template<typename Item_type>
bool prev_permutation(std::vector<Item_type> &v)
{
    auto first = v.begin();
    auto last = v.end();

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

// permutations by backtracking
template<typename Item_type>
void permutations_b(std::vector<Item_type> &v, std::size_t n, std::vector<std::vector<Item_type>> &a)
{
    if (n == 1) {
        a.push_back(v);
        return;
    }
    for (auto i = 0; i < n; ++i) {
        std::swap(v[i], v[n - 1]);
        permutations_b(v, n - 1, a);
        std::swap(v[i], v[n - 1]);
    }
}

template<typename Item_type>
std::vector<std::vector<Item_type>> permutations_b(std::vector<Item_type> v)
{
    std::vector<std::vector<Item_type>> p;
    permutations_b(v, v.size(), p);
    return p;
}

// begin tests

TEST(permutations, simple_3_elems)
{
    std::vector<int> v{1, 2, 3};
    ASSERT_THAT(permutations(v), ContainerEq(std::vector<std::vector<int>> {
                                                     {1, 2, 3},
                                                     {2, 1, 3},
                                                     {2, 3, 1},
                                                     {3, 2, 1},
                                                     {3, 1, 2},
                                                     {1, 3, 2}
                                             }
    ));
}

TEST(permutations, simple_3_char_string)
{
    std::string s{"abc"};
    ASSERT_THAT(string_permutations(s), ContainerEq(std::vector<std::string> {
                                                            "abc",
                                                            "acb",
                                                            "bac",
                                                            "bca",
                                                            "cab",
                                                            "cba"
                                                    }
    ));
}

TEST(permutations_b, simple_3_elems)
{
    std::vector<int> v{1, 2, 3};
    ASSERT_THAT(permutations_b(v), ContainerEq(std::vector<std::vector<int>> {
                                                     {2, 3, 1},
                                                     {3, 2, 1},
                                                     {3, 1, 2},
                                                     {1, 3, 2},
                                                     {2, 1, 3},
                                                     {1, 2, 3}
                                             }
    ));
}
