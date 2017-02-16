#include <string>
#include <istream>
#include <vector>
#include <fstream>
#include <regex>
#include <map>

// don't forget -> algorithms versions and study erase/remove
// also chapter 10 from cookbook

// boost/algorithm/string.hpp
// trim_left, trim_left_copy, trim_copy_if, trim_if, etc.

// find rfind find_first_of find_first_not_of find_last_of find_last_not_of

int main(int argc, char** argv)
{

    if (argc < 3) {
        return (EXIT_FAILURE);
    }

    std::ifstream in(argv[1]);
    std::ofstream out(argv[2]);

    if (!in || !out) {
        return (EXIT_FAILURE);
    }

    std::string tmp;

    in >> tmp;          // Grab the first word
    out << tmp;         // Dump it to the output stream

    while (in >> tmp) { // operator>> ignores whitespace, so all I have
        out << ' ';      // to do is add a space and each chunk of non-
        out << tmp;      // whitespace
    }

    out.close();
}

using Str_to_str_map = std::map<std::string, std::string>;

// Class for holding text fields
class Text_auto_field {

public:
    Text_auto_field() = delete;

    ~Text_auto_field() = default;

    Text_auto_field(Str_to_str_map* const p) : _p_dict{p}
    {
        if (!p) {
            throw std::invalid_argument{"The string-to-string map pointer must not be null"};
        }
    }

    void append(char c);

    inline std::string get_text() const { return _buf; }

private:
    std::string _buf;
    const std::unique_ptr<Str_to_str_map> _p_dict;
    // Str_to_str_map* const _p_dict;
};

// Append with autocorrect
void Text_auto_field::append(char c)
{
    if ((std::isspace(c) || std::ispunct(c)) && _buf.length() > 0 && !std::isspace(_buf[_buf.length() - 1])) {
        auto i = _buf.find_last_of(" \f\n\r\t\v");
        i = (i == std::string::npos) ? 0 : ++i;

        std::string tmp{_buf.substr(i, _buf.length() - i)};
        auto p = _p_dict->find(tmp);
        if (p != _p_dict->end()) {
            _buf.erase(i, _buf.length() - i);
            _buf += p->second;
        }
    }
    _buf += c;
}


//void split(const std::string& s, char c, std::vector<std::string>& v)
//{
//    int i = 0;
//    int j = s.find(c);
//
//    while (j >= 0) {
//        v.push_back(s.substr(i, j - i));
//        i = ++j;
//        j = s.find(c, j);
//
//        if (j < 0) {
//            v.push_back(s.substr(i, s.length()));
//        }
//    }
//}

//void loadCSV(std::istream& in, std::vector<std::vector<std::string>*>& data)
//{
//
//std::vector<std::string>* p = nullptr;
//std::string tmp;
//
//while (!in.eof()) {
//getline(in, tmp, '\n');                     // Grab the next line
//
//p = new std::vector<std::string>();
//split(tmp, ',', *p);                        // Use split from
//// <link linkend="cplusplusckbk-CHP-4-SECT-7">Recipe 4.7</link>
//data.push_back(p);
//
//cout << tmp << '\n';
//tmp.clear();
//}
//}

void split_with_regex()
{
    std::string s = "who,lives:in-a,pineapple    under the sea?";
    std::regex re(",|:|-|\\s+");
    std::sregex_token_iterator p(s.begin(), s.end(), re, -1);
    std::sregex_token_iterator end;
}