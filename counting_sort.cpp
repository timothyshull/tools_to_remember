#include <random>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

template<typename Item_type>
void counting_sort(std::vector<Item_type>& a)
{
    if (a.size() <= 1) { return; } // prefer insertion sort under size of 10
    auto min_max = std::minmax_element(a.begin(), a.end());
    auto min = *min_max.first;
    auto range = *min_max.second - min + 2;

    std::vector<std::size_t> count(range, 0);
    for (auto e : a) { ++count[e - min + 1]; }
    for (auto i = 1; i < count.size(); ++i) { count[i] += count[i - 1]; }

    std::vector<Item_type> aux(a.size());
    for (auto e : a) { aux[count[e - min]++] = e; }
    a = aux;
}

// begin tests

TEST(counting_sort, sort)
{
    std::vector<int> v{2, 1, 3, 5, 6, 4};
    counting_sort(v);
    ASSERT_THAT(v, Eq(std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST(counting_sort, sort_1000_rand)
{
    std::size_t num_elems = 1000;
    std::vector<int> v(num_elems);

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<int> dis{1, 100}; // int max is too large

    for (auto i = 0; i < num_elems; ++i) { v[i] = dis(gen); }

    auto tmp = v;
    counting_sort(v);
    std::sort(tmp.begin(), tmp.end());
    ASSERT_THAT(v, Eq(tmp));
}

TEST(counting_sort, sort_1000_rand_neg)
{
    std::size_t num_elems = 1000;
    std::vector<int> v(num_elems);

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<int> dis{-100, 100};

    for (auto i = 0; i < num_elems; ++i) { v[i] = dis(gen); }

    auto tmp = v;
    counting_sort(v);
    std::sort(tmp.begin(), tmp.end());
    ASSERT_THAT(v, Eq(tmp));
}

