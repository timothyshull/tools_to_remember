#include <vector>
#include <numeric>
#include <iostream>
#include <random>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

// Knuth Vol. 4, algorithm L
// lexicographic combinations
// generates combinations of the form c1 ... ct for numbers 0 ... n-1
// TODO: has bugs, not lexicographical
std::vector<std::vector<int>> knuth_combinations(int n, int t)
{
    if (t > n || t < 0) { throw std::invalid_argument{""};}
    std::vector<std::vector<int>> combinations;
    std::vector<int> c(static_cast<std::vector<int>::size_type>(t + 3), 0);
    for (auto j = 1; j < t + 1; ++j) {
        c[j] = j - 1;
    }
    c[t + 1] = n;
    c[t + 2] = 0;
    while (true) {
        combinations.emplace_back(c.begin() + 1, c.begin() + t + 1);
        auto j = 1;
        while (c[j] + 1 == c[j + 1]) {
            c[j] = j - 1;
            ++j;
        }
        if (j > t) { break; }
        else { ++c[j]; }
    }
    return combinations;
}


//std::vector<std::vector<int>> knuth_combinations_t(int n, int t)
//{
//    if (t >= n) { throw std::invalid_argument{"The value t must be less than n"}; }
//    std::vector<std::vector<int>> combinations;
//    std::vector<int> c(static_cast<std::vector<int>::size_type>(t + 2));
//    std::iota(c.begin(), c.end() - 2, 1);
//    c[t] = n;
//    c[t + 1] = 0;
//    auto j = t;
//    while (true) {
//        combinations.emplace_back(c.begin(), c.begin() + t + 1);
//        if (j > 0) {
//            auto x = j;
//            c[j] = x;
//            --j;
//            continue;
//        }
//
//        if (c[0] + 1 < c[1]) {
//            ++c[0];
//            continue;
//        } else {
//            j = 2;
//        }
//
//        c[j - 1] = j - 2;
//        auto x = c[j] + 1;
//        while (x == c[j + 1]) {
//            ++j;
//        }
//
//        if (j > t) { break; }
//    }
//    return combinations;
//}

void combinations(
        int n,
        int k,
        int offset,
        std::vector<int>& partial,
        std::vector<std::vector<int>>& result
)
{
    if (partial.size() == k) {
        result.emplace_back(partial);
        return;
    }

    const auto num_remaining = k - partial.size();
    for (auto i = offset; i <= n && num_remaining <= n - i + 1; ++i) {
        partial.emplace_back(i);
        combinations(n, k, i + 1, partial, result);
        partial.pop_back();
    }
}

std::vector<std::vector<int>> combinations(int n, int k)
{
    std::vector<std::vector<int>> result;
    std::vector<int> t;
    combinations(n, k, 1, t, result);
    return result;
}

TEST(combinations, epi_combos_simple)
{
    auto result = combinations(4, 2);
    std::vector<std::vector<int>> expected{
            {1, 2},
            {1, 3},
            {1, 4},
            {2, 3},
            {2, 4},
            {3, 4}
    };
    ASSERT_THAT(result, ContainerEq(expected));
}

TEST(combinations, alg_l_simple)
{
    auto result = knuth_combinations(5, 3);
    std::vector<std::vector<int>> expected{
            {0, 1, 2},
            {0, 1, 3},
            {0, 2, 3},
            {1, 2, 3},
            {0, 1, 4},
            {0, 2, 4},
            {1, 2, 4},
            {0, 3, 4},
            {1, 3, 4},
            {2, 3, 4}
    };
    ASSERT_THAT(result, ContainerEq(expected));
}
