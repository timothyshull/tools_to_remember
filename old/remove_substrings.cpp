#include <string>

template<typename Char_type>
void remove_substrings(std::basic_string<Char_type>& s, const std::basic_string<Char_type>& p)
{
    std::basic_string<Char_type>::size_type n{p.length()};
    for (auto i = s.find(p); i != std::basic_string<Char_type>::npos; i = s.find(p)) {
        s.erase(i, n);
    }
}