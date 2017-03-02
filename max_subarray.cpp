#include <cassert>
#include <iostream>
#include <random>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

template<typename Item_type>
int max_subarray_kadane(const std::vector<Item_type>& a)
{
    Item_type max{0};
    Item_type max_here{0};
    for (auto e : a) {
        max_here = std::max<Item_type>(0, max_here + e);
        max = std::max<Item_type>(max, max_here);
    }
    return max;
}

template<typename Item_type>
int max_subarray(const std::vector<Item_type>& a)
{
    auto min_sum = 0;
    auto sum = 0;
    auto max_sum = 0;
    for (auto i = 0; i < a.size(); ++i) {
        sum += a[i];
        if (sum < min_sum) { min_sum = sum; }
        if (sum - min_sum > max_sum) { max_sum = sum - min_sum; }
    }
    return max_sum;
}

template<typename Item_type>
std::vector<Item_type> rand_vector(std::size_t len)
{
    std::vector<Item_type> r(len);
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> dis{-1000, 1000};
    for (auto i = 0; i < len; ++i) { r[i] = dis(gen); }
    return r;
}

template<typename Item_type>
void check_max_sum(const std::vector<Item_type>& a, int max_sum)
{
    Item_type sum;
    for (auto i = 0; i < a.size(); ++i) {
        sum = 0;
        for (auto j = i; j < a.size(); ++j) {
            sum += a[j];
            ASSERT_THAT(sum, Le(max_sum));
        }
    }
}

// begin tests

TEST(max_subarray, one_element_of_one)
{
    std::vector<int> b{1};
    auto max_sum = max_subarray(b);
    ASSERT_THAT(max_sum, Eq(1));
}

TEST(max_subarray, one_neg_element)
{
    std::vector<int> b{-5};
    auto max_sum = max_subarray(b);
    ASSERT_THAT(max_sum, Eq(0));
}

TEST(max_subarray, one_zero)
{
    std::vector<int> b{0};
    auto max_sum = max_subarray(b);
    ASSERT_THAT(max_sum, Eq(0));
}

TEST(max_subarray, two_zeros)
{
    std::vector<int> b{0, 0};
    auto max_sum = max_subarray(b);
    ASSERT_THAT(max_sum, Eq(0));
}

TEST(max_subarray, three_zeros)
{
    std::vector<int> b{0, 0, 0};
    auto max_sum = max_subarray(b);
    ASSERT_THAT(max_sum, Eq(0));
}

TEST(max_subarray, zero_neg_5_zero)
{
    std::vector<int> b{0, -5, 0};
    auto max_sum = max_subarray(b);
    ASSERT_THAT(max_sum, Eq(0));
}

TEST(max_subarray, neg_two_neg_one)
{
    std::vector<int> b{-2, -1};
    auto max_sum = max_subarray(b);
    ASSERT_THAT(max_sum, Eq(0));
}

// long running
//TEST(max_subarray, rand_vector)
//{
//    std::random_device rd;
//    std::default_random_engine gen{rd()};
//    std::uniform_int_distribution<std::size_t> dis{1, 10000};
//    auto b = rand_vector<int>(dis(gen));
//    auto max_sum = max_subarray(b);
//    check_max_sum(b, max_sum);
//}

TEST(max_subarray_kadane, one_element_of_one)
{
    std::vector<int> b{1};
    auto max_sum = max_subarray_kadane(b);
    ASSERT_THAT(max_sum, Eq(1));
}

TEST(max_subarray_kadane, one_neg_element)
{
    std::vector<int> b{-5};
    auto max_sum = max_subarray_kadane(b);
    ASSERT_THAT(max_sum, Eq(0));
}

TEST(max_subarray_kadane, one_zero)
{
    std::vector<int> b{0};
    auto max_sum = max_subarray_kadane(b);
    ASSERT_THAT(max_sum, Eq(0));
}

TEST(max_subarray_kadane, two_zeros)
{
    std::vector<int> b{0, 0};
    auto max_sum = max_subarray_kadane(b);
    ASSERT_THAT(max_sum, Eq(0));
}

TEST(max_subarray_kadane, three_zeros)
{
    std::vector<int> b{0, 0, 0};
    auto max_sum = max_subarray_kadane(b);
    ASSERT_THAT(max_sum, Eq(0));
}

TEST(max_subarray_kadane, zero_neg_5_zero)
{
    std::vector<int> b{0, -5, 0};
    auto max_sum = max_subarray_kadane(b);
    ASSERT_THAT(max_sum, Eq(0));
}

TEST(max_subarray_kadane, neg_two_neg_one)
{
    std::vector<int> b{-2, -1};
    auto max_sum = max_subarray_kadane(b);
    ASSERT_THAT(max_sum, Eq(0));
}

// long running
//TEST(max_subarray_kadane, rand_vector)
//{
//    std::random_device rd;
//    std::default_random_engine gen{rd()};
//    std::uniform_int_distribution<std::size_t> dis{1, 10000};
//    auto b = rand_vector<int>(dis(gen));
//    auto max_sum = max_subarray_kadane(b);
//    check_max_sum(b, max_sum);
//}
