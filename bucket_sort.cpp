#include <random>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

template<typename Item_type>
void bucket_sort(std::vector<Item_type>& a, std::size_t sz = 5)
{
    if (a.size() <= 1) { return; } // prefer insertion sort under size of 10
    auto min_max = std::minmax_element(a.begin(), a.end());
    auto min = *min_max.first;
    auto max = *min_max.second;
    auto num_buckets = (max - min) / sz + 1;
    std::vector<std::vector<Item_type>> buckets(num_buckets, std::vector<Item_type>{});
    for (auto e : a) { buckets[(e - min) / sz].push_back(e); }
    a.clear();
    for (auto& v : buckets) {
        std::sort(v.begin(), v.end());
        a.insert(a.end(), v.begin(), v.end());
    }
}

// begin tests

TEST(bucket_sort, sort)
{
    std::vector<int> v{2, 1, 3, 5, 6, 4};
    bucket_sort(v);
    ASSERT_THAT(v, Eq(std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST(bucket_sort, sort_1000_rand)
{
    std::size_t num_elems = 1000;
    std::vector<int> v(num_elems);

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<int> dis{1, 100}; // int max is too large

    for (auto i = 0; i < num_elems; ++i) { v[i] = dis(gen); }

    auto tmp = v;
    bucket_sort(v);
    std::sort(tmp.begin(), tmp.end());
    ASSERT_THAT(v, Eq(tmp));
}

TEST(bucket_sort, sort_1000_rand_neg)
{
    std::size_t num_elems = 1000;
    std::vector<int> v(num_elems);

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<int> dis{-100, 100};

    for (auto i = 0; i < num_elems; ++i) { v[i] = dis(gen); }

    auto tmp = v;
    bucket_sort(v);
    std::sort(tmp.begin(), tmp.end());
    ASSERT_THAT(v, Eq(tmp));
}

