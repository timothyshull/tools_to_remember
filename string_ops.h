#ifndef STRING_OPS_H
#define STRING_OPS_H

#include <string>
#include <unordered_set>
#include <vector>
#include <regex>

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
    for (const auto c : s) { chars.insert(c); }
    return chars.size();
}

template<typename Char_type>
std::size_t count_unique_manual(const std::basic_string<Char_type>& s)
{
    auto min_val = std::numeric_limits<Char_type>::min();
    std::vector<std::size_t> counts(static_cast<std::vector<std::size_t>::size_type>(std::numeric_limits<Char_type>::max() - min_val + 1), 0);
    for (const auto e : s) { ++counts[e - min_val]; }
    std::size_t count{0};
    for (const auto e : counts) { if (e) { ++count; }}
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
void remove_substr(std::basic_string<Char_type>& s, const std::basic_string<Char_type>& p)
{
    auto n = p.length();
    for (auto i = s.find(p); i != std::basic_string<Char_type>::npos; i = s.find(p)) { s.erase(i, n); }
}

// END remove substring code

// START split string code

template<typename Char_type>
std::vector<std::basic_string<Char_type>> split(const std::basic_string<Char_type>& s, const char c)
{
    // previously used str.find -> could potentially use
    std::vector<std::basic_string<Char_type>> r;

    auto begin = s.begin();
    while (begin != s.end()) {
        // while (begin != s.end() && *begin == c) { ++begin; }
        begin = std::find_if(begin, s.end(), [&c](const Char_type& a) { return a != c; });
        auto t = std::find(begin, s.end(), c);
        if (begin != s.end()) { r.emplace_back(begin, t); }
        begin = t;
    }

    return r;
}

template<typename Char_type>
std::vector<std::basic_string<Char_type>> split(const std::basic_string<Char_type>& s)
{
    std::vector<std::basic_string<Char_type>> r;
    std::unordered_set<Char_type> chars{' ', '\n', '\t', '\b'};

    // TODO: fix this
    auto i = std::size_t{0};
    while (i < s.size()) {
        i = s.find_first_of(" \n\t\b", i);
        auto t = s.find_first_not_of(" \n\t\b", i);
        if (i != std::basic_string<Char_type>::npos) {
            r.emplace_back(s.substr(i, t - t));
        }
        i = t;
    }

    return r;
}

// END split string code

// START trim code

// ALSO: boost/algorithm/string.hpp -> trim_left, trim_left_copy, trim_copy_if, trim_if, etc.

// NOTE: can also provide overloads that copy and trim string
template<typename Char_type, typename Predicate_type>
void rtrim(std::basic_string<Char_type>& s, Predicate_type pred)
{
    if (s.empty()) { return; }
    auto it = s.rbegin();
    while (it != s.rend() && pred(*it)) { ++it; }
    s.erase(it.base(), s.end());
}

template<typename Char_type>
inline void rtrim(std::basic_string<Char_type>& s) { rtrim(s, [](const Char_type& c) { return std::isspace(c); }); }

template<>
inline void rtrim<wchar_t>(std::basic_string<wchar_t>& s) { rtrim(s, [](const wchar_t& c) { return std::iswspace(c); }); }


template<typename Char_type, typename Predicate_type>
void ltrim(std::basic_string<Char_type>& s, Predicate_type pred)
{
    if (s.empty()) { return; }
    auto it = s.begin();
    while (it != s.end() && pred(*it)) { ++it; }
    s.erase(s.begin(), it);
}

template<typename Char_type>
inline void ltrim(std::basic_string<Char_type>& s) { ltrim(s, [](const Char_type& c) { return std::isspace(c); }); }

template<>
inline void ltrim<wchar_t>(std::basic_string<wchar_t>& s) { ltrim(s, [](const wchar_t& c) { return std::iswspace(c); }); }

template<typename Char_type>
inline void trim(std::basic_string<Char_type>& s) {
    ltrim(s);
    rtrim(s);
}

// END trim code

// START regex split

std::vector<std::string> re_split(std::string& s, std::regex& re)
{
    std::sregex_token_iterator it{s.begin(), s.end(), re, -1};
    std::sregex_token_iterator end;
    std::vector<std::string> v;
    while (it != end) {
        v.emplace_back(*it);
        ++it;
    }
    return v;
}


//int main()
//{
//    string data = "<person>\n"
//            " <first>Nico</first>\n"
//            " <last>Josuttis</last>\n"
//            "</person>\n";
//
//    regex reg("<(.*)>(.*)</(\\1)>");
//
//    // iterate over all matches (using a regex_token_iterator):
//    sregex_token_iterator pos(data.cbegin(),data.cend(), // sequence
//                              reg,                       // token separator
//                              {0,2});      // 0: full match, 2: second substring
//    sregex_token_iterator end;
//    for ( ; pos!=end ; ++pos ) {
//        cout << "match:  " << pos->str() << endl;
//    }
//    cout << endl;
//
//    string names = "nico, jim, helmut, paul, tim, john paul, rita";
//    regex sep("[ \t\n]*[,;.][ \t\n]*");  // separated by , ; or . and spaces
//    sregex_token_iterator p(names.cbegin(),names.cend(),  // sequence
//                            sep,                          // separator
//                            -1);        // -1: values between separators
//    sregex_token_iterator e;
//    for ( ; p!=e ; ++p ) {
//        cout << "name:  " << *p << endl;
//    }
//}
//
//int main()
//{
//    string data = "<person>\n"
//            " <first>Nico</first>\n"
//            " <last>Josuttis</last>\n"
//            "</person>\n";
//
//    regex reg("<(.*)>(.*)</(\\1)>");
//
//    // iterate over all matches (using a regex_iterator):
//    sregex_iterator pos(data.cbegin(),data.cend(),reg);
//    sregex_iterator end;
//    for ( ; pos!=end ; ++pos ) {
//        cout << "match:  " << pos->str() << endl;
//        cout << " tag:   " << pos->str(1) << endl;
//        cout << " value: " << pos->str(2) << endl;
//    }
//
//    // use a regex_iterator to process each matched substring as element in an algorithm:
//    sregex_iterator beg(data.cbegin(),data.cend(),reg);
//    for_each (beg,end,[](const smatch& m) {
//        cout << "match:  " << m.str() << endl;
//        cout << " tag:   " << m.str(1) << endl;
//        cout << " value: " << m.str(2) << endl;
//    });
//}

// END regex split


#endif // STRING_OPS_H
