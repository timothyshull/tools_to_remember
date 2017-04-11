#include <random>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

template<typename Item_type>
void bucket_sort(std::vector<Item_type>& coll, std::size_t bucket_sz = 5)
{
    if (coll.size() <= 10) {
        std::sort(std::begin(coll), std::end(coll));
        return;
    } // prefer std::sort under size of 10

    auto min_max = std::minmax_element(std::begin(coll), std::end(coll));
    auto min = *(min_max.first);
    auto num_buckets = (*(min_max.second) - min) / bucket_sz + 1;

    std::vector<std::vector<Item_type>> buckets(num_buckets, std::vector<Item_type>{});
    for (const auto& e : coll) {
        buckets[(e - min) / bucket_sz].push_back(e);
    }

    auto sz = coll.size();
    coll.clear();
    coll.reserve(sz);

    for (auto& v : buckets) {
        std::sort(std::begin(v), std::end(v));
        coll.insert(coll.end(), std::begin(v), std::end(v));
    }
}

// begin tests

TEST(bucket_sort, sort_fewer_than_10)
{
    std::vector<int> v{2, 1, 3, 5, 6, 4};
    bucket_sort(v);
    ASSERT_THAT(v, Eq(std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST(bucket_sort, sort_more_than_10)
{
    std::vector<int> v{2, 1, 3, 5, 6, 4, 7, 11, 9, 8, 10, 12, 15, 14, 13};
    bucket_sort(v);
    ASSERT_THAT(v, Eq(std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}));
}

TEST(bucket_sort, sort_1000_rand)
{
    auto num_elems = static_cast<std::size_t>(1000);
    std::vector<int> v(num_elems);

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<int> dis{1, 100}; // int max is too large

    for (auto i = 0; i < num_elems; ++i) { v[i] = dis(gen); }

    auto t = v;
    bucket_sort(v);
    std::sort(t.begin(), t.end());
    ASSERT_THAT(v, Eq(t));
}

TEST(bucket_sort, sort_1000_rand_neg)
{
    auto num_elems = static_cast<std::size_t>(1000);
    std::vector<int> v(num_elems);

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<int> dis{-100, 100};

    for (auto i = 0; i < num_elems; ++i) { v[i] = dis(gen); }

    auto t = v;
    bucket_sort(v);
    std::sort(t.begin(), t.end());
    ASSERT_THAT(v, Eq(t));
}

