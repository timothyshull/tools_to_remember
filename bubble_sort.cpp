#include <random>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

template<typename Item_type>
void bubble_sort(std::vector<Item_type>& a)
{
    auto n = a.size();
    for (auto i = 0; i < n; ++i) {
        auto exch = 0;
        for (auto j = n - 1; j > i; --j) {
            if (a[j] < a[j - 1]) {
                std::swap(a[j], a[j - 1]);
                ++exch;
            }
        }
        if (exch == 0) { break; }
    }
}

// begin tests

TEST(bubble_sort, sort)
{
    std::vector<int> v{2, 1, 3, 5, 6, 4};
    bubble_sort(v);
    ASSERT_THAT(v, Eq(std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST(bubble_sort, sort_1000_rand)
{
    std::size_t num_elems = 1000;
    std::vector<int> v(num_elems);

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<> dis{0, std::numeric_limits<int>::max()};

    for (auto i = 0; i < num_elems; ++i) { v[i] = dis(gen); }

    auto tmp = v;
    bubble_sort(v);
    std::sort(tmp.begin(), tmp.end());
    ASSERT_THAT(v, Eq(tmp));
}