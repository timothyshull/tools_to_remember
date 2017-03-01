#include <random>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

// NOTE: this implementation

template<typename Item_type>
void sink(std::vector<Item_type>& a, int k, int n)
{
    while (2 * k <= n) {
        auto j = 2 * k;
        if (j < n && a[j - 1] < a[j]) { ++j; }
        if (a[j - 1] <= a[k - 1]) { break; }
        std::swap(a[k - 1], a[j - 1]);
        k = j;
    }
}

template<typename Item_type>
void heapsort(std::vector<Item_type>& a)
{
    auto n = a.size();
    for (auto k = n / 2; k >= 1; --k) { sink(a, static_cast<int>(k), static_cast<int>(n)); }
    while (n > 1) {
        std::swap(a[0], a[--n]); // std::swap(a[1], a[n--]);
        sink(a, 1, static_cast<int>(n));
    }
}

// begin tests

TEST(heapsort, sort)
{
    std::vector<int> v{2, 1, 3, 5, 6, 4};
    heapsort(v);
    ASSERT_THAT(v, Eq(std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST(heapsort, sort_1000_rand)
{
    std::size_t num_elems = 1000;
    std::vector<int> v(num_elems);

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<> dis{0, std::numeric_limits<int>::max()};

    for (auto i = 0; i < num_elems; ++i) { v[i] = dis(gen); }

    auto tmp = v;
    heapsort(v);
    std::sort(tmp.begin(), tmp.end());
    ASSERT_THAT(v, Eq(tmp));
}

