#include <random>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

template<typename Item_type>
void insertion_sort(std::vector<Item_type>& a)
{
    auto n = a.size();
    for (auto i = 1; i < n; ++i) {
        for (auto j = i; j > 0 && a[j] < a[j - 1]; --j) {
            std::swap(a[j], a[j - 1]);
        }
    }
}

// begin tests

TEST(insertion_sort, sort)
{
    std::vector<int> v{2, 1, 3, 5, 6, 4};
    insertion_sort(v);
    ASSERT_THAT(v, Eq(std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST(insertion_sort, sort_1000_rand)
{
    std::size_t num_elems = 1000;
    std::vector<int> v(num_elems);

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<> dis{0, std::numeric_limits<int>::max()};

    for (auto i = 0; i < num_elems; ++i) { v[i] = dis(gen); }

    auto tmp = v;
    insertion_sort(v);
    std::sort(tmp.begin(), tmp.end());
    ASSERT_THAT(v, Eq(tmp));
}