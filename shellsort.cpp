#include <random>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

template<typename Item_type>
void shellsort(std::vector<Item_type>& a)
{
    auto n = a.size();
    auto h = 1;
    while (h < n / 3) { h = 3 * h + 1; }
    while (h >= 1) {
        for (auto i = h; i < n; ++i) {
            for (auto j = i; j >= h && a[j] < a[j - h]; j -= h) {
                std::swap(a[j], a[j - h]);
            }
        }
        h = h / 3;
    }
}

// begin tests

TEST(shellsort, sort)
{
    std::vector<int> v{2, 1, 3, 5, 6, 4};
    shellsort(v);
    ASSERT_THAT(v, Eq(std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST(shellsort, sort_1000_rand)
{
    std::size_t num_elems = 1000;
    std::vector<int> v(num_elems);

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<> dis{0, std::numeric_limits<int>::max()};

    for (auto i = 0; i < num_elems; ++i) { v[i] = dis(gen); }

    auto tmp = v;
    shellsort(v);
    std::sort(tmp.begin(), tmp.end());
    ASSERT_THAT(v, Eq(tmp));
}

