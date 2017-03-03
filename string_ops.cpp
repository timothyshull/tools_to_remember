#include <string>
#include <unordered_set>
#include <random>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

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

// START count unique code

//template<typename Char_type>
//std::size_t count_unique_old(const std::basic_string<Char_type>& s)
//{
//    std::basic_string<Char_type> chars;
//    for (auto e : s) {
//        if (chars.find(e) == std::basic_string<Char_type>::npos) { chars += e; }
//    }
//    return chars.size();
//}

template<typename Char_type>
std::size_t count_unique(const std::basic_string<Char_type>& s)
{
    std::unordered_set<Char_type> chars;
    for (auto c : s) { chars.insert(c); }
    return chars.size();
}

template<typename Char_type>
std::size_t count_unique_manual(const std::basic_string<Char_type>& s)
{
    auto min_val = std::numeric_limits<Char_type>::min();
    std::vector<std::size_t> counts(static_cast<std::vector<std::size_t>::size_type>(std::numeric_limits<Char_type>::max() - min_val + 1), 0);
    for (auto e : s) { ++counts[e - min_val]; }
    std::size_t count{0};
    for (auto e : counts) { if (e) { ++count; }}
    return count;
}

// END count unique code


// START case ops code

// old version:
// {
//    for (auto p = s.begin(); p != s.end(); ++p) {
//        *p = static_cast<char>(std::toupper(*p));
//    }
// }

template<typename Char_type>
inline void to_upper(std::basic_string<Char_type>& s) { for (auto& c : s) { c = std::toupper(c); }}

template<>
inline void to_upper<wchar_t>(std::basic_string<wchar_t>& s) { for (auto& c : s) { c = std::towupper(c); }}

template<typename Char_type>
inline void to_lower(std::basic_string<Char_type>& s) { for (auto& c : s) { c = std::tolower(c); }}

template<>
inline void to_lower<wchar_t>(std::basic_string<wchar_t>& s) { for (auto& c : s) { c = std::tolower(c); }}

// previously had separate functions for case insensitive char compare rather than lambda
template<typename Char_type>
inline bool ci_eq(const std::basic_string<Char_type>& s1, const std::basic_string<Char_type>& s2)
{
    return s1.size() == s2.size() &&
           std::equal(s1.begin(), s1.end(), s2.begin(),
                      [](const Char_type& a, const Char_type& b) { return std::tolower(a) == std::tolower(b); });
}

template<>
inline bool ci_eq<wchar_t>(const std::basic_string<wchar_t>& s1, const std::basic_string<wchar_t>& s2)
{
    return s1.size() == s2.size() &&
           std::equal(s1.begin(), s1.end(), s2.begin(),
                      [](const wchar_t& a, const wchar_t& b) { return std::towlower(a) == std::towlower(b); });
}

//inline bool to_upper_lhs_compare(char a, char b) { return toupper(a) == b; }
//

template<typename Char_type>
inline typename std::basic_string<Char_type>::const_iterator ci_find(
        const std::basic_string<Char_type>& s,
        const std::basic_string<Char_type>& p
)
{
    return std::search(s.begin(), s.end(), p.begin(), p.end(),
                       [](const Char_type& a, const Char_type& b) { return std::tolower(a) == std::tolower(b); });
}

template<>
inline std::basic_string<wchar_t>::const_iterator ci_find<wchar_t>(
        const std::basic_string<wchar_t>& s,
        const std::basic_string<wchar_t>& p
)
{
    return std::search(s.begin(), s.end(), p.begin(), p.end(),
                       [](const wchar_t& a, const wchar_t& b) { return std::towlower(a) == std::towlower(b); });
}

// END case ops code

// START join code

template<typename Char_type>
std::basic_string<Char_type> join(const std::vector<std::basic_string<Char_type>>& v, std::basic_string<Char_type> c = "")
{
    std::basic_string<Char_type> s{""};
    for (auto p = v.begin(); p != v.end(); ++p) {
        s += *p;
        if (p != v.end() - 1) { s += c; }
    }
    return s;
}

// C string array join
//template<typename Char_type>
//void join(const Char_type* arr[], std::size_t n, Char_type c, std::basic_string<Char_type>& s)
//{
//    s.clear();
//    for (int i{0}; i < n; ++i) {
//        if (arr[i] != nullptr) {
//            s += arr[i];
//        }
//        if (i < n - 1) {
//            s += c;
//        }
//    }
//}

// END join code

// START nth substring code

template<typename Char_type>
std::size_t nth_substr(const std::basic_string<Char_type>& s, const std::basic_string<Char_type>& p, std::size_t n)
{
    auto i = s.find(p);
    auto j = 1;
    for (; j < n && i != std::basic_string<Char_type>::npos; ++j) { i = s.find(p, i + 1); }
    return j == n ? i : std::basic_string<Char_type>::npos;
}
// removed alternate with repetitions

// END nth substring code

// START pad string code

template<typename Char_type>
inline void pad(
        std::basic_string<Char_type>& s,
        typename std::basic_string<Char_type>::size_type n,
        Char_type c
) { s.append((s.length() < n ? n : s.length()) - s.length(), c); }

// END pad string code

// START remove substring code

template<typename Char_type>
void remove_substrings(std::basic_string<Char_type>& s, const std::basic_string<Char_type>& p)
{
    auto n = p.length();
    for (auto i = s.find(p); i != std::basic_string<Char_type>::npos; i = s.find(p)) { s.erase(i, n); }
}

// END remove substring code


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