#ifndef TOOLS_TO_REMEMBER_STRING_TOKENIZER_H
#define TOOLS_TO_REMEMBER_STRING_TOKENIZER_H

#include <string>
#include <unordered_set>

template<typename Char_type>
class String_tokenizer {
public:
    using String_type = typename std::basic_string<Char_type>;
    using Size_type = typename std::basic_string<Char_type>::size_type;
    using Iterator_type = typename std::basic_string<Char_type>::const_iterator;
private:
    std::unordered_set<Char_type> _delimiters;
    String_type _str;
    std::size_t _count;
    Iterator_type _begin;
    Iterator_type _end;

public:
    String_tokenizer() = delete;

    String_tokenizer(const String_tokenizer&) = default;

    String_tokenizer(String_tokenizer&&) = default;

    ~String_tokenizer() = default;

    String_tokenizer& operator=(const String_tokenizer&) = default;

    String_tokenizer& operator=(String_tokenizer&&) = default;

    String_tokenizer(const String_type& s, const String_type& delims = " \f\n\r\t\v\b")
            : _str{s},
              _count{std::numeric_limits<std::size_t>::max()},
              _delimiters{delims.begin(), delims.end()}
    {
        _begin = std::find_if(_str.cbegin(), _str.cend(), [this](const Char_type& a) { return this->_delimiters.find(a) == _delimiters.end(); });
        _end = std::find_if(_begin, _str.cend(), [this](const Char_type& a) { return this->_delimiters.find(a) != _delimiters.end(); });
    }

    std::size_t count_tokens()
    {
        if (_count != std::numeric_limits<std::size_t>::max()) { return _count; }

        _count = 0;

        Iterator_type begin = _str.cbegin();
        // while (begin != _str.cend()) {
        while (true) {
            begin = std::find_if(begin, _str.cend(), [this](const Char_type& a) { return this->_delimiters.find(a) == _delimiters.end(); });
            if (begin == _str.cend()) { break; }
            ++_count;
            begin = std::find_if(begin, _str.cend(), [this](const Char_type& a) { return this->_delimiters.find(a) != _delimiters.end(); });
        }
        return _count;
    }

    inline bool has_next() const noexcept { return _begin != _end; }

    std::basic_string<Char_type> next_token()
    {
        std::basic_string<Char_type> s;
        if (_begin != _str.cend()) { s = {_begin, _end}; }
        if (_end == _str.cend()) { _begin = _end; } // no more tokens
        else {
            _begin = std::find_if(_end, _str.cend(), [this](const Char_type& a) { return this->_delimiters.find(a) == _delimiters.end(); });
            _end = std::find_if(_begin, _str.cend(), [this](const Char_type& a) { return this->_delimiters.find(a) != _delimiters.end(); });
        }
        return s;
    }
};

#endif // TOOLS_TO_REMEMBER_STRING_TOKENIZER_H
