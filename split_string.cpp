#include <string>
#include <vector>
#include <iostream>

//template<typename Char_type>
//void split(const std::basic_string<Char_type>& s, char c, std::vector<std::basic_string<Char_type>>& v)
//{
//    std::basic_string<Char_type>::size_type i{0};
//    std::basic_string<Char_type>::size_type j{s.find(c)};
//
//    while (j != std::string::npos) {
//        v.emplace_back(s.substr(i, j - i));
//        i = ++j;
//        j = s.find(c, j);
//
//        if (j == std::string::npos) {
//            v.emplace_back(s.substr(i, s.length()));
//        }
//    }
//}
//
//template<typename Char_type>
//std::vector<std::basic_string<Char_type>> split(const std::basic_string<Char_type>& s, const char c)
//{
//    std::vector<std::basic_string<Char_type>> result;
//
//    auto begin = s.begin();
//    while (begin != s.end()) {
//        auto tmp = std::find(begin, s.end(), c);
//        if (begin != s.end()) { result.emplace_back(begin, tmp); }
//        begin = tmp;
//        for (; begin != s.end() && *begin == c; ++begin) {}
//    }
//
//    return result;
//}

template<typename Char_type>
std::vector<std::basic_string<Char_type>> split(const std::basic_string<Char_type>& s)
{
    std::vector<std::basic_string<Char_type>> result;
    std::basic_string<Char_type> split_chars{" \n\t\b"};

    auto begin = s.begin();
    while (begin != s.end()) {
        auto tmp = std::find_first_of(begin, s.end(), split_chars.begin(), split_chars.end());
        if (begin != s.end()) { result.emplace_back(begin, tmp); }
        for (begin = tmp; begin != s.end() && std::any_of(split_chars.begin(), split_chars.end(), [begin](char c) { return c == *begin; }); ++begin) {}
    }

    return result;
}

template<typename Char_type>
std::vector<std::basic_string<Char_type>> split(const std::basic_string<Char_type>& s, const char c)
{
    using Find_type = typename std::basic_string<Char_type>::size_type;
    Find_type i{0};
    Find_type j{s.find(c)};
    std::vector<std::basic_string<Char_type>> v;

    if (j == std::basic_string<Char_type>::npos) { v.emplace_back(s); }

    for (; j != std::basic_string<Char_type>::npos; i = ++j, j = s.find(c, j)) {
        auto size = (j == std::basic_string<Char_type>::npos) ? s.size() - i : j - i;
        if (size) { v.emplace_back(s.substr(i, size)); }
    }

    return v;
}

int main()
{
    // std::string test{"test \n \tone    two\t\t\t\t three\b four five"};
    // std::string test{"test   one    two three   four five"};
    std::string test{"onetwothreefour"};


//    for (auto s : split(test)) {
//        std::cout << s << " ... ";
//    }
    for (auto s : split(test, ' ')) {
        std::cout << s << " ... ";
    }
    return 0;
}