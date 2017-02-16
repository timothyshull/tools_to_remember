#include <string>

class String_tokenizer {
public:
    String_tokenizer() = delete;

    String_tokenizer(const String_tokenizer&) = default;

    String_tokenizer(String_tokenizer&&) = default;

    ~String_tokenizer() = default;

    String_tokenizer& operator=(const String_tokenizer&) = default;

    String_tokenizer& operator=(String_tokenizer&&) = default;

    String_tokenizer(const std::string& s, const std::string& delim = " \f\n\r\t\v")
            : _str{s},
              _count{-1},
              _delimiter{delim},
              _begin{_str.find_first_not_of(_delimiter)},
              _end{_str.find_first_of(_delimiter, _begin)} {}

    std::size_t count_tokens()
    {
        if (_count >= 0) {
            return static_cast<std::size_t>(_count);
        }

        std::string::size_type n{0};
        std::string::size_type i{0};

        for (;;) {
            if ((i = _str.find_first_not_of(_delimiter, i)) == std::string::npos) {
                break;
            }
            i = _str.find_first_of(_delimiter, i + 1);
            ++n;
            if (i == std::string::npos) {
                break;
            }
        }
        _count = static_cast<int>(n);
        return n;
    }

    inline bool has_next() const noexcept { return (_begin != _end); }

    void next_token(std::string& s)
    {
        if (_begin != std::string::npos && _end != std::string::npos) {
            s = _str.substr(_begin, _end - _begin);
            _begin = _str.find_first_not_of(_delimiter, _end);
            _end = _str.find_first_of(_delimiter, _begin);
        } else if (_begin != std::string::npos && _end == std::string::npos) {
            s = _str.substr(_begin, _str.length() - _begin);
            _begin = _str.find_first_not_of(_delimiter, _end);
        }
    }

private:
    std::string _delimiter;
    std::string _str;
    int _count;
    std::string::size_type _begin;
    std::string::size_type _end;
};