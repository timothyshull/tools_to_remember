#include <string>

template<typename Char_type>
void pad(std::basic_string<Char_type>& s, typename std::basic_string<Char_type>::size_type n, Char_type c)
{
    if (n > s.length()) {
        s.append(n - s.length(), c);
    }
}