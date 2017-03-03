#include <string>
#include <iostream>
#include <vector>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

void string_permutations(std::string s) { string_permutations("", s); }

void string_permutations(std::string prefix, std::string s)
{
    auto n = s.size();
    if (n == 0) {
        std::cout << prefix << "\n";
    } else {
        for (std::size_t i = 0; i < n; ++i) {
            string_permutations(prefix + s[i], s.substr(0, i) + s.substr(i + 1, n));
        }
    }
}

≠// n! permutations of the elements of vector a -> not in order
template<typename Item_type, typename Visitor_type>
void permutations(std::vector<Item_type>& v, std::size_t n, Visitor_type& visit)
{
    if (n == 1) {
        visit(v);
        return;
    }
    // Heap's algorithm
    for (auto i = 0; i < n; ++i) {
        permutations(v, n - 1, visit);
        auto k = n % 2 ? 1 : i;
        std::swap(v[k], v[n - 1]);
    }

    // alternate
    // for (auto i = 0; i < n; ++i) {
    //     std::swap(v[i], v[n - 1]);
    //     heaps_algorithm(v, n - 1);
    //     std::swap(v[i], v[n - 1]);
    // }
}

// begin tests

template<typename Item_type>
struct Heap_visitor {
    std::vector<std::vector<Item_type>> permutations;

    void operator()(std::vector<Item_type>& a) { permutations.push_back(a); }
};

TEST(permutations, sort)
{
    std::vector<int> v{1, 2, 3};
    Heap_visitor<int> tv;
    permutations<int, Heap_visitor<int>>(v, v.size(), tv);
    ASSERT_THAT(tv.permutations, UnorderedElementsAre(
            std::vector<int>{1, 2, 3},
            std::vector<int>{2, 1, 3},
            std::vector<int>{2, 3, 1},
            std::vector<int>{3, 2, 1},
            std::vector<int>{3, 1, 2},
            std::vector<int>{1, 3, 2}
    ));
}