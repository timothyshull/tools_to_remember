#include <string>

void to_upper(std::basic_string<char>& s)
{
    for (auto p = s.begin(); p != s.end(); ++p) {
        *p = static_cast<char>(std::toupper(*p));
    }
}

void to_upper(std::basic_string<wchar_t>& s)
{
    for (auto p = s.begin(); p != s.end(); ++p) {
        *p = std::towupper(*p);
    }
}

void to_lower(std::basic_string<char>& s)
{
    for (std::basic_string<char>::iterator p = s.begin(); p != s.end(); ++p) {
        *p = static_cast<char>(std::tolower(*p));
    }
}

void to_lower(std::basic_string<wchar_t>& s)
{
    for (std::basic_string<wchar_t>::iterator p = s.begin(); p != s.end(); ++p) {
        *p = std::towlower(*p);
    }
}

inline bool case_insensitive_char_compare(char a, char b) { return std::tolower(a) == std::tolower(b); }

inline bool wcase_insensitive_char_compare(wchar_t a, wchar_t b) { return towlower(a) == towlower(b); }

bool case_insensitive_equals(const std::string& s1, const std::string& s2)
{
    return ((s1.size() == s2.size()) && std::equal(s1.begin(), s1.end(), s2.begin(), case_insensitive_char_compare));
}

bool wcase_insensitive_equals(const std::wstring& s1, const std::wstring& s2)
{
    return ((s1.size() == s2.size()) && std::equal(s1.begin(), s1.end(), s2.begin(), wcase_insensitive_char_compare));
}

inline bool to_upper_lhs_compare(char a, char b) { return toupper(a) == b; }

std::string::const_iterator case_insensitive_find(const std::string& s, const std::string& p)
{
    std::string tmp;
    std::transform(p.begin(), p.end(), std::back_inserter(tmp), std::toupper);
    return std::search(s.begin(), s.end(), tmp.begin(), tmp.end(), to_upper_lhs_compare);
}