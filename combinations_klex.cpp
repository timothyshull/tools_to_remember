#include <string>
#include <vector>
#include <iostream>

template<typename Item_type>
void combinations_klex1(
        std::vector<Item_type> &&prefix,
        std::vector<Item_type> &&items,
        std::size_t combo_size,
        std::vector<std::vector<Item_type>> &out
)
{
    if (items.size() < combo_size) { return; }
    else if (combo_size == 0) {
        out.push_back(prefix);
    } else {
        auto t = prefix;
        t.push_back(items[0]);
        combinations_klex1(std::move(t), {items.begin() + 1, items.end()}, combo_size - 1, out);
        combinations_klex1(std::move(prefix), {items.begin() + 1, items.end()}, combo_size, out);
    }
}

template<typename Item_type>
std::vector<std::vector<Item_type>> combinations_klex1(std::vector<Item_type> items, std::size_t combo_size)
{
    std::vector<std::vector<Item_type>> out;
    combinations_klex1({}, std::move(items), combo_size, out);
    return out;
}

void combinations_klex1(
        std::string &&prefix,
        std::string &&in_string,
        std::size_t combo_size,
        std::vector<std::string> &out
)
{
    if (in_string.size() < combo_size) { return; }
    else if (combo_size == 0) {
        out.push_back(prefix);
    } else {
        combinations_klex1(prefix + in_string[0], in_string.substr(1, std::string::npos), combo_size - 1, out);
        combinations_klex1(std::move(prefix), in_string.substr(1, std::string::npos), combo_size, out);
    }
}

std::vector<std::string> combinations_klex1(std::string in_string, std::size_t combo_size)
{
    std::vector<std::string> out;
    combinations_klex1("", std::move(in_string), combo_size, out);
    return out;
}

template<typename Item_type>
void combinations_klex2(
        std::vector<Item_type> &&prefix,
        std::vector<Item_type> &&items,
        std::size_t combo_size,
        std::vector<std::vector<Item_type>> &out
)
{
    if (combo_size == 0) {
        out.push_back(prefix);
    } else {
        for (auto i = 0; i < items.size(); ++i) {
            auto t = prefix;
            t.push_back(items[i]);
            combinations_klex2(
                    std::move(t),
                    {items.begin() + i + 1, items.end()},
                    combo_size - 1,
                    out
            );
        }
    }
}

template<typename Item_type>
std::vector<std::vector<Item_type>> combinations_klex2(std::vector<Item_type> items, std::size_t combo_size)
{
    std::vector<std::vector<Item_type>> out;
    combinations_klex1({}, std::move(items), combo_size, out);
    return out;
}

void combinations_klex2(
        std::string &&prefix,
        std::string &&in_string,
        std::size_t combo_size,
        std::vector<std::string> &out
)
{
    if (combo_size == 0) {
        out.push_back(prefix);
    } else {
        for (std::size_t i{0}; i < in_string.size(); ++i) {
            combinations_klex2(
                    prefix + in_string[i],
                    in_string.substr(i + 1, std::string::npos),
                    combo_size - 1,
                    out
            );
        }
    }
}

std::vector<std::string> combinations_klex2(std::string in_string, std::size_t combo_size)
{
    std::vector<std::string> out;
    combinations_klex2("", std::move(in_string), combo_size, out);
    return out;
}

int main()
{
    auto out = combinations_klex1("abcde", 3);
    for (const auto &s : out) {
        std::cout << s << "\n";
    }

    std::cout << "\n";

    auto out2 = combinations_klex2("abcde", 3);
    for (const auto &s : out2) {
        std::cout << s << "\n";
    }

    auto t = std::vector<int>{1, 2, 3, 4, 5};
    auto out3 = combinations_klex1(t, 3);
    for (const auto &v : out3) {
        for (const auto &e : v) {
            std::cout << e << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n";

    auto out4 = combinations_klex2(t, 3);
    for (const auto &v : out4) {
        for (const auto &e : v) {
            std::cout << e << " ";
        }
        std::cout << "\n";
    }
    return 0;
}