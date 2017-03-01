#include <string>

template<typename Char_type>
int nth_substr(int n, const std::basic_string<Char_type>& s, const std::basic_string<Char_type>& p)
{
    std::string::size_type i = s.find(p);

    int j;
    for (j = 1; j < n && i != std::string::npos; ++j) {
        i = s.find(p, i + 1);
    }

    if (j == n) {
        return static_cast<int>(i);
    } else {
        return -1;
    }
}

template<typename Char_type>
int nth_substr(int n, const std::basic_string<Char_type>& s, const std::basic_string<Char_type>& p, bool repeats = false)
{
    typename std::basic_string<Char_type>::size_type i{s.find(p)};
    typename std::basic_string<Char_type>::size_type adv{repeats ? 1 : p.length()};

    int j;
    for (j = 1; j < n && i != std::basic_string<Char_type>::npos; ++j) {
        i = s.find(p, i + adv);
    }

    if (j == n) {
        return static_cast<int>(i);
    } else {
        return -1;
    }
}