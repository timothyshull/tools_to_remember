#include <string>
#include <vector>

template<typename Char_type>
void join(const std::vector<std::basic_string<Char_type>>& v, char c, std::basic_string<Char_type>& s)
{
    s.clear();
    for (auto p = v.begin(); p != v.end(); ++p) {
        s += *p;
        if (p != v.end() - 1) {
            s += c;
        }
    }
}

template<typename Char_type>
void join(const Char_type* arr[], std::size_t n, Char_type c, std::basic_string<Char_type>& s)
{
    s.clear();
    for (int i{0}; i < n; ++i) {
        if (arr[i] != nullptr) {
            s += arr[i];
        }
        if (i < n - 1) {
            s += c;
        }
    }
}