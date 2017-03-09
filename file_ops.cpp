#include <string>
#include <istream>
#include <vector>
#include <fstream>
#include <map>
#include <unordered_map>

#include "string_ops.h"

void convert_whitespace(std::ifstream& in, std::ofstream& out)
{
    if (!in || !out) { throw std::system_error{std::make_error_code(std::errc::bad_file_descriptor), "Bad file args"}; }

    std::string tmp;
    if (in >> tmp) { out << tmp; }
    while (in >> tmp) {
        out << ' ';
        out << tmp;
    }
    out.close();
}

// text autocorrect
class Text_auto_field {

public:
    Text_auto_field() = delete;

    ~Text_auto_field() = default;

    Text_auto_field(std::unordered_map<std::string, std::string>& const m) : _map{m} {}

    void append(char c)
    {
        if ((std::isspace(c) || std::ispunct(c)) && _buf.length() > 0 && !std::isspace(_buf[_buf.length() - 1])) {
            auto i = _buf.find_last_of(" \f\n\r\t\v");
            i = (i == std::string::npos) ? 0 : ++i;

            std::string tmp{_buf.substr(i, _buf.length() - i)};
            auto p = _map.find(tmp);
            if (p != _map.end()) {
                _buf.erase(i, _buf.length() - i);
                _buf += p->second;
            }
        }
        _buf += c;
    }

    inline std::string get_text() const { return _buf; }

private:
    std::string _buf;
    const std::unordered_map<std::string, std::string>& _map;
};

void load_csv(std::istream& in, std::vector<std::vector<std::string>>& data)
{
    std::string tmp;
    while (!in.eof()) {
        std::getline(in, tmp);
        data.push_back(split(tmp, ','));
        tmp.clear();
    }
}

std::tuple<int, int, int> count_chars_words_lines(std::istream& in)
{
    char cur{'\0'};
    char last{'\0'};
    auto c = 0;
    auto w = 0;
    auto l = 0;

    while (in.get(cur)) {
        if (cur == '\n' || (cur == '\f' && last == '\r')) { ++l; }
        else { ++c; }
        if (!std::isalnum(cur) && std::isalnum(last)) { ++w; }
        last = cur;
    }
    if (c > 0) {
        if (std::isalnum(last)) { ++w; }
        ++l;
    }

    return {c, w, l};
}

void count_words(std::istream& in, std::unordered_map<std::string, std::size_t>& words)
{
    std::string s;
    while (in >> s) { ++words[s]; }
}

void add_margins(std::istream& in, std::ostream& out, std::size_t left, std::size_t right, char pad_char)
{
    std::string tmp;
    while (!in.eof()) {
        std::getline(in, tmp);
        tmp.insert(tmp.begin(), left, pad_char);
        tmp.insert(tmp.end(), right, pad_char);
        out << tmp << '\n';
    }
}

void right_justify(std::ifstream& in, std::ofstream& out, std::size_t width = 72)
{
    std::string tmp;
    out.setf(std::ios_base::right);
    while (!in.eof()) {
        out.width(width);
        std::getline(in, tmp, '\n');
        out << tmp << '\n';
    }
    out.close();
}

std::streamoff stream_size(std::istream& is)
{
    std::istream::pos_type current_pos{is.tellg()};
    if (-1 == current_pos) { return -1; }
    is.seekg(0, std::istream::end);
    std::istream::pos_type end_pos{is.tellg()};
    is.seekg(current_pos);
    return end_pos - current_pos;
}

bool stream_read_string(std::istream& f, std::string& result)
{
    std::streamoff len{stream_size(f)};
    if (len == -1) { return false; }
    result.resize(static_cast<std::string::size_type>(len));
    f.read(&result[0], result.length());
    return true;
}

void tabs_to_spaces(std::ifstream& in, std::ofstream& out, std::size_t tab_size = 4)
{
    if (!in || !out) { throw std::system_error{std::make_error_code(std::errc::bad_file_descriptor), "Bad file args"}; }
    std::string tab{""};
    tab.insert(tab.begin(), tab_size, ' ');

    char c;
    while (in.get(c)) {
        if (c == '\t') { out << tab; }
        else { out << c; }
    }

    in.close();
    out.close();
}

void spaces_to_tabs(std::istream& in, std::ostream& out, std::size_t limit)
{
    auto spaces = 0;
    char c;
    while (in.get(c)) {
        if (c != ' ') {
            if (spaces > 0) {
                for (int i = 0; i < spaces; i++) { out.put(' '); }
                spaces = 0;
            }
            out.put(c);
        } else {
            if (++spaces == limit) {
                out.put('\t');
                spaces = 0;
            }
        }
    }
}

void wrap_text(std::istream& in, std::ostream& out, std::size_t width)
{
    std::string tmp;
    char cur{'\0'};
    char last{'\0'};
    std::size_t i{0};

    while (in.get(cur)) {
        if (++i == width) {
            ltrim(tmp);
            out << '\n' << tmp;
            i = tmp.length();
            tmp.clear();
        } else if (isspace(cur) && !isspace(last)) {
            out << tmp;
            tmp.clear();
        }
        tmp += cur;
        last = cur;
    }
}