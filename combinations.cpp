#include <string>
#include <vector>
#include <iostream>

template<typename Item_type>
void combinations1(
        std::vector<Item_type> &&prefix,
        std::vector<Item_type> &&items,
        std::vector<std::vector<Item_type>> &out
)
{
    if (items.empty()) { return; }
    auto t = prefix;
    t.push_back(items[0]);
    out.push_back(t);
    combinations1(std::move(t), {items.begin() + 1, items.end()}, out);
    combinations1(std::move(prefix), {items.begin() + 1, items.end()}, out);
}

template<typename Item_type>
std::vector<std::vector<Item_type>> combinations1(std::vector<Item_type> items)
{
    std::vector<std::vector<Item_type>> out;
    combinations1<Item_type>({}, std::move(items), out);
    return out;
}

void combinations1(std::string &&prefix, std::string &&in_string, std::vector<std::string> &out)
{
    if (in_string.empty()) { return; }
    auto t = prefix + in_string[0];
    out.push_back(t);
    combinations1(std::move(t), in_string.substr(1, std::string::npos), out);
    combinations1(std::move(prefix), in_string.substr(1, std::string::npos), out);
}

std::vector<std::string> combinations1(std::string in_string)
{
    std::vector<std::string> out;
    combinations1("", std::move(in_string), out);
    return out;
}

template<typename Item_type>
void combinations2(
        std::vector<Item_type> &&prefix,
        std::vector<Item_type> &&items,
        std::vector<std::vector<Item_type>> &out
)
{
    out.push_back(prefix); // add check for empty
    for (auto i = 0; i < items.size(); ++i) {
        auto t = prefix;
        t.push_back(items[i]);
        combinations2(std::move(t), {items.begin() + i + 1, items.end()}, out);
    }
}

template<typename Item_type>
std::vector<std::vector<Item_type>> combinations2(std::vector<Item_type> items)
{
    std::vector<std::vector<Item_type>> out;
    combinations2<Item_type>({}, std::move(items), out);
    return out;
}

void combinations2(std::string &&prefix, std::string &&in_string, std::vector<std::string> &out)
{
    out.push_back(prefix);
    for (std::size_t i{0}; i < in_string.size(); ++i) {
        combinations2(prefix + in_string[i], in_string.substr(i + 1, std::string::npos), out);
    }
}

std::vector<std::string> combinations2(std::string in_string)
{
    std::vector<std::string> out;
    combinations2("", std::move(in_string), out);
    return out;
}

int main()
{
    auto out = combinations1("abc");
    for (const auto &s : out) {
        std::cout << s << "\n";
    }

    std::cout << "\n";

    auto out2 = combinations2("abcd");
    for (const auto &s : out2) {
        std::cout << s << "\n";
    }

    std::cout << "\n";

    auto t = std::vector<int>({1, 2, 3});
    auto out3 = combinations1(t);
    for (const auto &v : out3) {
        for (const auto &i : v) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n";

    auto out4 = combinations2(t);
    for (const auto &v : out4) {
        for (const auto &i : v) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
    return 0;
}