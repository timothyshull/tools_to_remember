#include <vector>
#include <random>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

template<typename Item_type>
int binary_search(const std::vector<Item_type>& a, const Item_type& i)
{
    auto l = 0;
    auto h = static_cast<int>(a.size() - 1);

    while (l <= h) {
        auto m = (h + l) / 2;
        if (i < a[m]) { h = m - 1; }
        else if (a[m] < i) { l = m + 1; }
        else { return m; }
    }
    return -1;
}

TEST(binary_search, test_5_elems_in_order)
{
    std::vector<int> v{1, 2, 3, 4, 5};
    ASSERT_THAT(binary_search(v, 3), Eq(2));
}

TEST(binary_search, test_5_elems_out_of_order)
{
    std::vector<int> v{2, 1, 3, 5, 4};
    ASSERT_THAT(binary_search(v, 3), Eq(2));
}

TEST(binary_search, test_empty)
{
    std::vector<int> v{};
    ASSERT_THAT(binary_search(v, 3), Eq(-1));
}

TEST(binary_search, find_from_1000_rand)
{
    std::size_t num_elems = 500;
    std::vector<int> v(num_elems);

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<> dis{0, std::numeric_limits<int>::max()};

    for (auto i = 0; i < num_elems; ++i) { v[i] = dis(gen); }
    std::sort(v.begin(), v.end());

    auto j = std::uniform_int_distribution<std::size_t>{0, num_elems - 1}(gen);
    ASSERT_THAT(binary_search(v, v[j]), Eq(j));
}
