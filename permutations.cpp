#include <string>
#include <iostream>
#include <vector>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

void string_permutations(std::string prefix, std::string s, std::vector<std::string>& v)
{
    auto n = s.size();
    if (n == 0) {
        v.push_back(prefix);
        return;
    }
    for (std::size_t i = 0; i < n; ++i) { string_permutations(prefix + s[i], s.substr(0, i) + s.substr(i + 1, n), v); }
}

std::vector<std::string> string_permutations(std::string& s)
{
    std::vector<std::string> v;
    string_permutations("", s, v);
    return v;
}

// n! permutations of the elements of vector a -> not in order
template<typename Item_type>
void permutations(std::vector<Item_type>& v, std::size_t n, std::vector<std::vector<Item_type>>& a)
{
    if (n == 1) {
        a.push_back(v);
        return;
    }
    // Heap's algorithm
    for (auto i = 0; i < n; ++i) {
        permutations(v, n - 1, a);
        auto k = n % 2 ? 1 : i;
        std::swap(v[k], v[n - 1]);
    }
}

template<typename Item_type>
std::vector<std::vector<Item_type>> permutations(std::vector<Item_type> v) // purposefully copied in
{
    std::vector<std::vector<Item_type>> p;
    auto t = v;
    permutations(t, v.size(), p);
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
    }));
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
    }));
}