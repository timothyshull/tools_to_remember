#include <random>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

template<typename Item_type>
int partition(std::vector<Item_type>& a, int lo, int hi)
{
    auto i = lo;
    auto j = hi + 1;

    Item_type v{a[lo]};
    while (true) {
        while (a[++i] < v) { if (i == hi) { break; }}
        while (v < a[--j]) { if (j == lo) { break; }}
        if (i >= j) { break; }
        std::swap(a[i], a[j]);
    }
    std::swap(a[lo], a[j]);
    return j;
}

template<typename Item_type>
void quicksort(std::vector<Item_type>& a, int lo, int hi)
{
    if (hi <= lo) { return; }
    auto j = partition(a, lo, hi);
    quicksort(a, lo, j - 1);
    quicksort(a, j + 1, hi);
}

template<typename Item_type>
void quicksort(std::vector<Item_type>& a)
{
    // std::shuffle(a.begin(), a.end()); -> eliminate dependence on input per Sedgeweick
    quicksort<Item_type>(a, 0, static_cast<int>(a.size() - 1)); // narrow_cast
}

template<typename Item_type>
void quicksort_3_way(std::vector<Item_type>& a, int lo, int hi)
{
    if (hi <= lo) { return; }
    auto lt = lo;
    auto i = lo + 1;
    auto gt = hi;

    Item_type v{a[lo]};
    while (i <= gt) {
        if (a[i] < v) { std::swap(a[lt++], a[i++]); }
        else if (v < a[i]) { std::swap(a[i], a[gt--]); }
        else { ++i; }
    }
    quicksort_3_way<Item_type>(a, lo, lt - 1);
    quicksort_3_way<Item_type>(a, gt + 1, hi);
}

template<typename Item_type>
void quicksort_3_way(std::vector<Item_type>& a)
{
    quicksort_3_way<Item_type>(a, 0, static_cast<int>(a.size() - 1)); // narrow_cast
}

// begin tests

TEST(quicksort, sort)
{
    std::vector<int> v{2, 1, 3, 5, 6, 4};
    quicksort(v);
    ASSERT_THAT(v, Eq(std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST(quicksort, sort_3_way)
{
    std::vector<int> v{2, 1, 3, 5, 6, 4};
    quicksort_3_way(v);
    ASSERT_THAT(v, Eq(std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST(quicksort, sort_1000_rand)
{
    std::size_t num_elems = 1000;
    std::vector<int> v(num_elems);

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<> dis{0, std::numeric_limits<int>::max()};

    for (auto i = 0; i < num_elems; ++i) { v.emplace_back(dis(gen)); }

    auto tmp = v;
    quicksort(v);
    std::sort(tmp.begin(), tmp.end());
    ASSERT_THAT(v, Eq(tmp));
}

TEST(quicksort, sort_1000_rand_3_way)
{
    std::size_t num_elems = 1000;
    std::vector<int> v(num_elems);

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<> dis{0, std::numeric_limits<int>::max()};

    for (auto i = 0; i < num_elems; ++i) { v[i] = dis(gen); }

    auto tmp = v;
    quicksort_3_way(v);
    std::sort(tmp.begin(), tmp.end());
    ASSERT_THAT(v, Eq(tmp));
}

