#include <istream>

void textWrap(std::istream& in, std::ostream& out, std::size_t width)
{

    std::string tmp;
    char cur = '\0';
    char last = '\0';
    size_t i = 0;

    while (in.get(cur)) {
        if (++i == width) {
            ltrimws(tmp);                  // ltrim as in Recipe
            out << '\n' << tmp;            // 4.1
            i = tmp.length();
            tmp.clear();
        } else if (isspace(cur) &&   // This is the end of
                   !isspace(last)) { // a word
            out << tmp;
            tmp.clear();
        }
        tmp += cur;
        last = cur;
    }
}