#include <random>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Linear_probing_hash_st.h"

using namespace testing;

std::string rand_string(std::size_t size)
{
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<char> dis{0, std::numeric_limits<char>::max()};
    std::string r;
    for (auto i = 0; i < size; ++i) { r += dis(gen); }
    return r;
}

TEST(linear_probing, put_1_string_int)
{
    Linear_probing_hash_st<std::string, int> st;
    st.put("one", 1);
    ASSERT_THAT(st.get("one"), Eq(1));
}

TEST(linear_probing, put_5_string_int)
{
    Linear_probing_hash_st<std::string, int> st;
    st.put("one", 1);
    st.put("two", 2);
    st.put("three", 3);
    st.put("four", 4);
    st.put("five", 5);
    ASSERT_THAT(st.get("five"), Eq(5));
}

TEST(linear_probing, get_empty)
{
    Linear_probing_hash_st<std::string, int> st;
    ASSERT_THROW(st.get("five"), std::out_of_range);
}


TEST(linear_probing, sort_1000_rand)
{
    std::size_t num_elems{1000};

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<> dis{0, std::numeric_limits<int>::max()};

    Linear_probing_hash_st<int, int> st;

    int tgt_key{0};
    int tgt_val{0};
    for (auto i = 0; i < num_elems; ++i) {
        auto ts = dis(gen);
        auto ti = dis(gen);
        if (i == num_elems / 2) {
            tgt_key = ts;
            tgt_val = ti;
        }
        st.put(ts, ti);
    }

    ASSERT_THAT(st.get(tgt_key), Eq(tgt_val));
}

TEST(linear_probing, sort_1000_rand_string_int)
{
    std::size_t num_elems{1000};

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<> dis{0, std::numeric_limits<int>::max()};

    Linear_probing_hash_st<std::string, int> st;

    std::string tgt_key{""};
    int tgt_val{0};
    for (auto i = 0; i < num_elems; ++i) {
        auto ts = rand_string(10);
        auto ti = dis(gen);
        if (i == num_elems / 2) {
            tgt_key = ts;
            tgt_val = ti;
        }
        st.put(ts, ti);
    }

    ASSERT_THAT(st.get(tgt_key), Eq(tgt_val));
}
