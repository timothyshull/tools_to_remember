#include <iostream>
#include <vector>

void subsequence(
        std::string &&prefix,
        std::string &&remaining,
        std::size_t n,
        std::vector<std::string> &out
)
{
    if (n == 0) {
        out.emplace_back(prefix);
        return;
    }
    if (remaining.empty()) { return; }
    subsequence(prefix + remaining[0], remaining.substr(1, std::string::npos), n - 1, out);
    subsequence(std::move(prefix), remaining.substr(1, std::string::npos), n, out);
}

std::vector<std::string> subsequence(std::string s, std::size_t n)
{
    std::vector<std::string> out;
    subsequence("", std::move(s), n, out);
    return out;
}

template<typename Item_type>
void subsequence(
        std::vector<Item_type> &&prefix,
        std::vector<Item_type> &&remaining,
        std::size_t n,
        std::vector<std::vector<Item_type>> &out
)
{
    if (n == 0) {
        out.emplace_back(prefix);
        return;
    }
    if (remaining.empty()) { return; }
    auto t1 = prefix;
    t1.push_back(remaining[0]);
    subsequence(std::move(t1), {remaining.begin() + 1, remaining.end()}, n - 1, out);
    subsequence(std::move(prefix), {remaining.begin() + 1, remaining.end()}, n, out);
}

template<typename Item_type>
std::vector<std::vector<Item_type>> subsequence(std::vector<Item_type> a, std::size_t n)
{
    std::vector<std::vector<Item_type>> out;
    subsequence({}, std::move(a), n, out);
    return out;
}

int main()
{
    auto out1 = subsequence("abcd", 3);
    for (const auto &s : out1) {
        std::cout << s << "\n";
    }

    std::cout << "\n";

    auto out2 = subsequence("abcc", 3);
    for (const auto &s : out2) {
        std::cout << s << "\n";
    }

    std::cout << "\n";

    auto t = std::vector<int>{1, 2, 3, 4};
    auto out3 = subsequence(t, 3);
    for (const auto &v : out3) {
        for (const auto &e : v) {
            std::cout << e << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n";

    auto t2 = std::vector<int>{1, 2, 3, 5};
    auto out4 = subsequence(t, 3);
    for (const auto &v : out4) {
        for (const auto &e : v) {
            std::cout << e << " ";
        }
        std::cout << "\n";
    }
    return 0;
}