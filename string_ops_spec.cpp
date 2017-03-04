#include <random>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "string_ops.h"
#include "String_tokenizer.h"


using namespace testing;

// START count unique tests

TEST(count_unique, count_5_elems)
{
    std::string s{"abcde"};
    ASSERT_THAT(count_unique(s), Eq(5));
}

TEST(count_unique, count_1000_rand)
{
    std::size_t num_elems{1000};
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<> dis{0, std::numeric_limits<char>::max()};

    std::string s{""};
    for (auto i = 0; i < num_elems; ++i) { s += dis(gen); }

    ASSERT_THAT(count_unique(s), Eq(count_unique_manual(s)));
}

// END count unique tests

// START case ops tests

TEST(str_case_ops, to_upper_string)
{
    std::string s{"abcde"};
    to_upper(s);
    ASSERT_THAT(s, Eq("ABCDE"));
}

TEST(str_case_ops, to_upper_wstring)
{
    std::wstring s{L"abcde"};
    to_upper(s);
    ASSERT_THAT(s, Eq(L"ABCDE"));
}

TEST(str_case_ops, to_lower_string)
{
    std::string s{"ABCDE"};
    to_lower(s);
    ASSERT_THAT(s, Eq("abcde"));
}

TEST(str_case_ops, to_lower_wstring)
{
    std::wstring s{L"ABCDE"};
    to_lower(s);
    ASSERT_THAT(s, Eq(L"abcde"));
}

TEST(str_case_ops, ci_eq_string_true)
{
    std::string s1{"aBcDe"};
    std::string s2{"AbCdE"};
    ASSERT_TRUE(ci_eq(s1, s2));
}

TEST(str_case_ops, ci_eq_string_false)
{
    std::string s1{"aBcDe"};
    std::string s2{"AbCdF"};
    ASSERT_FALSE(ci_eq(s1, s2));
}

TEST(str_case_ops, ci_eq_wstring_true)
{
    std::wstring s1{L"aBcDe"};
    std::wstring s2{L"AbCdE"};
    ASSERT_TRUE(ci_eq(s1, s2));
}

TEST(str_case_ops, ci_eq_wstring_false)
{
    std::wstring s1{L"aBcDe"};
    std::wstring s2{L"AbCdF"};
    ASSERT_FALSE(ci_eq(s1, s2));
}

TEST(str_case_ops, ci_find_string_contains)
{
    std::string s{"Lorem ipsum dolor sit amet, consectetur adipiscing elit,"
                          " sed do eiusmod tempor incididunt ut labore et dolore magna aliqua"};
    std::string t{"pisci"};
    ASSERT_THAT(ci_find(s, t), Eq(s.begin() + 43));
}

TEST(str_case_ops, ci_find_wstring_contains)
{
    std::wstring s{L"Lorem ipsum dolor sit amet, consectetur adipiscing elit,"
                           " sed do eiusmod tempor incididunt ut labore et dolore magna aliqua"};
    std::wstring t{L"pisci"};
    ASSERT_THAT(ci_find(s, t), Eq(s.begin() + 43));
}

TEST(str_case_ops, ci_find_string_does_not_contain)
{
    std::string s{"Lorem ipsum dolor sit amet, consectetur adipiscing elit,"
                          " sed do eiusmod tempor incididunt ut labore et dolore magna aliqua"};
    std::string t{"blah"};
    ASSERT_THAT(ci_find(s, t), Eq(s.end()));
}

TEST(str_case_ops, ci_find_wstring_does_not_contain)
{
    std::wstring s{L"Lorem ipsum dolor sit amet, consectetur adipiscing elit,"
                           " sed do eiusmod tempor incididunt ut labore et dolore magna aliqua"};
    std::wstring t{L"blah"};
    ASSERT_THAT(ci_find(s, t), Eq(s.end()));
}

// END case ops tests

// START join tests

TEST(string_join, random_strings_no_sep)
{
    std::size_t str_size{10};
    std::size_t num_strings{10};
    std::vector<std::string> v(num_strings);
    std::string s;
    s.reserve(str_size * num_strings);
    for (auto i = 0; i < num_strings; ++i) {
        auto t = rand_string(str_size);
        v[i] = t;
        s += t;
    }
    ASSERT_THAT(join(v), Eq(s));
}

TEST(string_join, random_strings_space_sep)
{
    std::size_t str_size{10};
    std::size_t num_strings{10};
    std::vector<std::string> v(num_strings);
    std::string s;
    std::string sep{" "};
    s.reserve(str_size * num_strings);
    for (auto i = 0; i < num_strings; ++i) {
        auto t = rand_string(str_size);
        v[i] = t;
        s += t;
        if (i < num_strings - 1) { s += sep; }
    }
    ASSERT_THAT(join(v, sep), Eq(s));
}

// END join tests

// START nth substring tests

TEST(nth_substr, basic_test_2nd_occurrence)
{
    std::string s{"Lorem ipsum dolor sit amet, consectetur adipiscing elit,"
                          " sed do eiusmod tempor incididunt ut labore et dolore magna aliqua"};
    std::string t{"it"};
    ASSERT_THAT(nth_substr(s, t, 2), Eq(53));
}

TEST(nth_substr, basic_test_fail)
{
    std::string s{"Lorem ipsum dolor sit amet, consectetur adipiscing elit,"
                          " sed do eiusmod tempor incididunt ut labore et dolore magna aliqua"};
    std::string t{"it"};
    ASSERT_THAT(nth_substr(s, t, 3), Eq(std::string::npos));
}

// END nth substring tests

// START pad string tests

TEST(pad_string, empty_to_5_as)
{
    std::string s{""};
    pad(s, 5, 'a');
    ASSERT_THAT(s, Eq("aaaaa"));
}

TEST(pad_string, five_as_plus_5_bs)
{
    std::string s{"aaaaa"};
    pad(s, 10, 'b');
    ASSERT_THAT(s, Eq("aaaaabbbbb"));
}

TEST(pad_string, smaller_size)
{
    std::string s{"aaaaa"};
    pad(s, 4, 'b');
    ASSERT_THAT(s, Eq("aaaaa"));
}

// END pad string tests

// START remove substring tests

TEST(remove_substr, simple_test)
{
    std::string s{"aa bb aa bb aa bb"};
    std::string p{"bb"};
    remove_substr(s, p);
    ASSERT_THAT(s, Eq("aa  aa  aa "));
}

// END remove substring tests

// START split string tests

TEST(split_string, simple_test)
{
    std::string s{"aa aa aa aa"};
    auto v = split(s, ' ');
    ASSERT_THAT(v, Eq(std::vector<std::string>{"aa", "aa", "aa", "aa"}));
}

TEST(split_string, simple_test_no_char)
{
    std::string s{"aa \b\t\naa\n\b\t aa\t\n\b aa"};
    auto v = split(s);
    ASSERT_THAT(v, Eq(std::vector<std::string>{"aa", "aa", "aa", "aa"}));
}

// END split string tests

// START string tokenizer tests

TEST(string_tokenizer, count_with_default_delims)
{
    std::string s{"aa \b\t\naa\n\b\t aa\t\n\b aa"};
    String_tokenizer<char> st{s};
    ASSERT_THAT(st.count_tokens(), Eq(4));
}

TEST(string_tokenizer, five_distinct_tokens)
{
    std::string s{"ab \b\t\nac\n\b\t ad\t\n\b ae"};
    String_tokenizer<char> st{s};
    std::vector<std::string> v;

    while (st.has_next()) { v.push_back(st.next_token()); }

    ASSERT_THAT(v, Eq(std::vector<std::string>{"ab", "ac", "ad", "ae"}));
}

// END string tokenizer tests

// START trim tests

TEST(string_rtrim, basic_test)
{
    std::string s{"abcde     "};
    rtrim(s);
    ASSERT_THAT(s, Eq("abcde"));
}

TEST(string_ltrim, basic_test)
{
    std::string s{"     abcde"};
    ltrim(s);
    ASSERT_THAT(s, Eq("abcde"));
}

TEST(string_trim, basic_test)
{
    std::string s{"     abcde     "};
    trim(s);
    ASSERT_THAT(s, Eq("abcde"));
}

// END trim tests