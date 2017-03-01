#include <ios>
#include <istream>

std::streamoff stream_size(std::istream& is)
{
    std::istream::pos_type current_pos{is.tellg()};
    if (-1 == current_pos) {
        return -1;
    }
    is.seekg(0, std::istream::end);
    std::istream::pos_type end_pos{is.tellg()};
    is.seekg(current_pos);
    return end_pos - current_pos;
}

bool stream_read_string(std::istream& f, std::string& result)
{
    std::streamoff len{stream_size(f)};
    if (len == -1) {
        return false;
    }
    result.resize(static_cast<std::string::size_type>(len));
    f.read(&result[0], result.length());
    return true;
}