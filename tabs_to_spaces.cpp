#include <fstream>

constexpr int exit_failure() { return EXIT_FAILURE; }

constexpr int exit_success() { return EXIT_SUCCESS; }

int tabs_to_spaces(std::string& infile, std::string& outfile)
{
    std::ifstream in{infile};
    std::ofstream out(outfile);

    if (!in || !out) { return exit_failure(); }

    char c;
    while (in.get(c)) {
        if (c == '\t') {
            out << "   ";
        } else {
            out << c;
        }
    }

    in.close();
    out.close();
    return out ? exit_success() : exit_failure();
}

void spaces_to_tabs(std::istream& in, std::ostream& out, std::size_t limit)
{
    std::size_t consecutive_spaces{0};
    char c;
    while (in.get(c)) {
        if (c != ' ') {
            if (consecutive_spaces > 0) {
                for (int i = 0; i < consecutive_spaces; i++) {
                    out.put(' ');
                }
                consecutive_spaces = 0;
            }
            out.put(c);
        } else {
            if (++consecutive_spaces == limit) {
                out.put('\t');
                consecutive_spaces = 0;
            }
        }
    }
}