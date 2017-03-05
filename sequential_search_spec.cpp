#include <random>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Sequential_search_st.h"
#include "testing_utility.h"

using namespace testing;

TEST(sequential_search, put_1_string_int)
{
    Sequential_search_st<std::string, int> st;
    st.put("one", 1);
    ASSERT_THAT(st.get("one"), Eq(1));
}

TEST(sequential_search, put_5_string_int)
{
    Sequential_search_st<std::string, int> st;
    st.put("one", 1);
    st.put("two", 2);
    st.put("three", 3);
    st.put("four", 4);
    st.put("five", 5);
    ASSERT_THAT(st.get("five"), Eq(5));
}

TEST(sequential_search, get_empty)
{
    Sequential_search_st<std::string, int> st;
    ASSERT_THROW(st.get("five"), std::out_of_range);
}

TEST(sequential_search, sort_1000_rand)
{
    std::size_t num_elems{1000};
    std::size_t string_size{10};

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<> dis{0, std::numeric_limits<int>::max()};

    Sequential_search_st<std::string, int> st;

    std::string tgt_key{};
    int tgt_val{};
    for (auto i = 0; i < num_elems; ++i) {
        auto ts = testing_utility::rand_string(string_size);
        auto ti = dis(gen);
        if (i == num_elems / 2) {
            tgt_key = ts;
            tgt_val = ti;
        }
        st.put(ts, ti);
    }

    ASSERT_THAT(st.get(tgt_key), Eq(tgt_val));
}