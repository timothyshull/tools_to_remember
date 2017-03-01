#include <string>
#include <functional>

template<typename Char_type>
void rtrim(std::basic_string<Char_type>& s, Char_type c)
{
    if (s.empty()) {
        return;
    }
    typename std::basic_string<Char_type>::iterator p;
    for (p = s.end(); p != s.begin() && *--p == c;) {}
    if (*p != c) {
        ++p;
    }
    s.erase(p, s.end());
}

template<typename Char_type, typename Predicate_type>
void rtrimws(std::basic_string<Char_type>& s, Predicate_type predicate)
{
    if (s.empty()) {
        return;
    }
    typename std::basic_string<Char_type>::iterator p;
    for (p = s.end(); p != s.begin() && predicate(*--p);) {}
    if (!predicate(*p)) {
        ++p;
    }
    s.erase(p, s.end());
}

inline void rtrimws(std::string& s) { rtrimws(s, std::isspace); }

inline void rtrimws(std::wstring& s) { rtrimws(s, std::iswspace); }

// TODO: fix and check
template<typename Char_type, typename Predicate_type>
void ltrimws(std::basic_string<Char_type>& s, Predicate_type predicate)
{
    if (s.empty()) {
        return;
    }
    typename std::basic_string<Char_type>::iterator p;
    for (p = s.end(); p != s.begin() && predicate(*--p);) {}
    if (!predicate(*p)) {
        ++p;
    }
    s.erase(p, s.end());
}

inline void ltrimws(std::string& s) { ltrimws(s, std::isspace); }

inline void ltrimws(std::wstring& s) { ltrimws(s, std::iswspace); }

// additional options
// trim from start (in place)
static inline void ltrim(std::string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s)
{
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
static inline std::string ltrimmed(std::string s)
{
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrimmed(std::string s)
{
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trimmed(std::string s)
{
    trim(s);
    return s;
}

// boost::trim_right(str);