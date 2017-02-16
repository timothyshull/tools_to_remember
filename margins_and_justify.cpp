#include <cstdlib>
#include <iosfwd>
#include <string>
#include <fstream>

void add_margins(std::istream& in, std::ostream& out, std::size_t left, std::size_t right, char pad_char)
{

    std::string tmp;
    while (!in.eof()) {
        std::getline(in, tmp, '\n');
        tmp.insert(tmp.begin(), left, pad_char);
        rpad(tmp, right, pad_char);
        out << tmp << '\n';
    }
}

int right_justify(int argc, char** argv)
{

    if (argc < 3) {
        return EXIT_FAILURE;
    }

    std::ifstream in(argv[1]);
    std::ofstream out(argv[2]);

    int w{72};
    if (argc == 4) {
        w = std::stoi(argv[3]);
    }

    std::string tmp;
    out.setf(std::ios_base::right);
    while (!in.eof()) {
        out.width(w);
        std::getline(in, tmp, '\n');
        out << tmp << '\n';
    }
    out.close();
    return EXIT_SUCCESS;
}
