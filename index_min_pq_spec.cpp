#include <vector>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Index_min_pq.h"

using namespace testing;

TEST(index_min_pq, default_size)
{
    Index_min_pq<int> a;
    ASSERT_THAT(a.size(), Eq(0));
}

TEST(index_min_pq, test_10_max_empty)
{
    Index_min_pq<int> a{10};
    ASSERT_TRUE(a.empty());
}

TEST(index_min_pq, test_non_empty)
{
    Index_min_pq<int> a{1};
    a.insert(1, 1);
    ASSERT_FALSE(a.empty());
}

//TEST(index_min_pq, test_3_elems)
//{
//    Index_min_pq<int> a{3};
//    a.push(1);
//    a.push(2);
//    a.push(3);
//    ASSERT_THAT(a.pop(), Eq(3));
//}
//
//TEST(index_min_pq, test_10_max_3_size)
//{
//    Index_min_pq<int> a{10};
//    a.push(1);
//    a.push(2);
//    a.push(3);
//    ASSERT_THAT(a.size(), Eq(3));
//}
//
//TEST(index_min_pq, test_3_lvalue)
//{
//    Index_min_pq<int> a{10};
//    auto b = 1;
//    auto c = 2;
//    auto d = 3;
//    a.push(b);
//    a.push(c);
//    a.push(d);
//    ASSERT_THAT(a.pop(), Eq(3));
//}
//
//TEST(index_min_pq, test_3_then_empty)
//{
//    Index_min_pq<int> a{10};
//    a.push(1);
//    a.push(2);
//    a.push(3);
//    a.pop();
//    a.pop();
//    a.pop();
//    ASSERT_TRUE(a.empty());
//}
//
//TEST(index_min_pq, test_comparator)
//{
//    Index_min_pq<int, std::greater<int>> a{3};
//    a.push(3);
//    a.push(2);
//    a.push(1);
//    ASSERT_THAT(a.pop(), Eq(1));
//}
