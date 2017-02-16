#include <istream>
#include <map>

std::tuple<int, int, int> count_chars_words_lines(std::istream& in)
{
    char cur{'\0'};
    char last{'\0'};
    int chars{0};
    int words{0};
    int lines{0};

    while (in.get(cur)) {
        if (cur == '\n' ||
            (cur == '\f' && last == '\r')) {
            lines++;
        } else {
            chars++;
        }
        if (!std::isalnum(cur) && std::isalnum(last)) {
            words++;
        }
        last = cur;
    }
    if (chars > 0) {
        if (std::isalnum(last)) {
            words++;
        }
        lines++;
    }

    return {chars, words, lines};
}

using Str_to_int_map = std::map<std::string, int>;

void count_words(std::istream& in, Str_to_int_map& words)
{
    std::string s;
    while (in >> s) {
        ++words[s];
    }
}