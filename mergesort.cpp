#include <random>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

// top-down
template<typename Item_type>
void merge(std::vector<Item_type>& a, std::vector<Item_type>& aux, int lo, int mid, int hi)
{
    auto i = lo;
    auto j = mid + 1;
    for (auto k = lo; k <= hi; ++k) { aux[k] = a[k]; }
    for (auto k = lo; k <= hi; ++k) {
        if (mid < i) { a[k] = aux[j++]; }
        else if (hi < j) { a[k] = aux[i++]; }
        else if (aux[j] < aux[i]) { a[k] = aux[j++]; }
        else { a[k] = aux[i++]; }
    }
}

template<typename Item_type>
void mergesort(std::vector<Item_type>& a, std::vector<Item_type>& aux, int lo, int hi)
{
    if (hi <= lo) { return; }
    auto mid = (hi + lo) / 2;
    mergesort<Item_type>(a, aux, lo, mid);
    mergesort<Item_type>(a, aux, mid + 1, hi);
    merge<Item_type>(a, aux, lo, mid, hi);
}

template<typename Item_type>
void mergesort_top_down(std::vector<Item_type>& a)
{
    std::vector<Item_type> aux(a.size());
    mergesort(a, aux, 0, static_cast<int>(a.size() - 1)); // narrow_cast
}

template<typename Item_type>
void mergesort_bottom_up(std::vector<Item_type>& a)
{
    auto n = a.size();
    std::vector<Item_type> aux(n);

    for (auto sz = 1; sz < n; sz = sz + sz) {
        for (auto lo = 0; lo < n - sz; lo += sz + sz) {
            merge(a, aux, lo, lo + sz - 1, std::min(lo + sz + sz - 1, static_cast<int>(n - 1))); // narrow_cast
        }
    }
}

// begin tests

TEST(mergesort, sort_top_down)
{
    std::vector<int> v{2, 1, 3, 5, 6, 4};
    mergesort_top_down(v);
    ASSERT_THAT(v, Eq(std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST(mergesort, sort_bottom_up)
{
    std::vector<int> v{2, 1, 3, 5, 6, 4};
    mergesort_bottom_up(v);
    ASSERT_THAT(v, Eq(std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST(mergesort, sort_1000_top_down)
{
    std::size_t num_elems = 1000;
    std::vector<int> v(num_elems);

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<> dis{0, std::numeric_limits<int>::max()};

    for (auto i = 0; i < num_elems; ++i) { v[i] = dis(gen); }

    auto tmp = v;
    mergesort_top_down(v);
    std::sort(tmp.begin(), tmp.end());
    ASSERT_THAT(v, Eq(tmp));
}

TEST(mergesort, sort_1000_bottom_up)
{
    std::size_t num_elems = 1000;
    std::vector<int> v(num_elems);

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<> dis{0, std::numeric_limits<int>::max()};

    for (auto i = 0; i < num_elems; ++i) { v[i] = dis(gen); }

    auto tmp = v;
    mergesort_bottom_up(v);
    std::sort(tmp.begin(), tmp.end());
    ASSERT_THAT(v, Eq(tmp));
}

