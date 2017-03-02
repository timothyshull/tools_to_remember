#include <string>
#include <unordered_set>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

template<typename Char_type>
std::size_t count_unique_old(const std::basic_string<Char_type>& s)
{
    std::basic_string<Char_type> chars;
    for (auto e : s) {
        if (chars.find(e) == std::basic_string<Char_type>::npos) { chars += e; }
    }
    return chars.size();
}

template<typename Char_type>
std::size_t count_unique(const std::basic_string<Char_type>& s)
{
    std::unordered_set<Char_type> chars;
    for (auto c : s) { chars.insert(c); }
    return chars.size();
}

TEST(count_unique, count_5_elems)
{
    std::string s{"abcde"};
    ASSERT_THAT(count_unique(s), Eq(5));
}

//TEST(count_unique, sort_1000_rand)
//{
//    std::size_t num_elems = 1000;
//    std::vector<int> v(num_elems);
//
//    std::random_device rd;
//    std::default_random_engine gen{rd()};
//    std::uniform_int_distribution<> dis{0, std::numeric_limits<int>::max()};
//
//    for (auto i = 0; i < num_elems; ++i) { v[i] = dis(gen); }
//
//    auto tmp = v;
//    shellsort(v);
//    std::sort(tmp.begin(), tmp.end());
//    ASSERT_THAT(v, Eq(tmp));
//}