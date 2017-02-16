#include <string>

template<typename Char_type>
std::size_t count_unique(const std::basic_string<Char_type>& s)
{
    std::basic_string<Char_type> chars;
    for (auto p = s.begin(); p != s.end(); ++p) {
        if (chars.find(*p) == std::basic_string<Char_type>::npos) { chars += *p; }
    }
    return chars.size();
}