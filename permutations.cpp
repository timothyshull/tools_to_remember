#include <string>
#include <vector>
#include <iostream>

void permutations1(std::string &&prefix, std::string &&in_string, std::vector<std::string> &out)
{
    auto n = in_string.size();
    if (n == 0) {
        out.emplace_back(prefix);
    } else {
        for (auto i = std::size_t{0}; i < n; ++i) {
            permutations1(
                    prefix + in_string[i],
                    in_string.substr(0, i) + in_string.substr(i + 1, std::string::npos),
                    out
            );
        }
    }
}

std::vector<std::string> permutations1(std::string s)
{
    std::vector<std::string> out;
    permutations1("", std::move(s), out);
    return out;
}

template<typename Item_type>
void permutations1(
        std::vector<Item_type> &&prefix,
        std::vector<Item_type> &&items,
        std::vector<std::vector<Item_type>> &out
)
{
    auto n = items.size();
    if (n == 0) {
        out.emplace_back(prefix);
    } else {
        for (auto i = 0; i < n; ++i) {
            auto t1 = prefix;
            t1.push_back(items[i]);
            auto t2 = std::vector<Item_type>{items.begin(), items.begin() + i};
            t2.insert(t2.end(), items.begin() + i + 1, items.end());
            permutations1(std::move(t1), std::move(t2), out);
        }
    }
}

template<typename Item_type>
std::vector<std::vector<Item_type>> permutations1(std::vector<Item_type> items)
{
    std::vector<std::vector<Item_type>> out;
    permutations1({}, std::move(items), out);
    return out;
}

void permutations2(std::string &&a, std::size_t n, std::vector<std::string>& out)
{
    if (n == 1) {
        out.emplace_back(a);
        return;
    }
    for (auto i = 0; i < n; ++i) {
        std::swap(a[i], a[n - 1]);
        permutations2(std::move(a), n - 1, out);
        std::swap(a[i], a[n - 1]);
    }
}

std::vector<std::string> permutations2(std::string s)
{
    std::vector<std::string> out;
    permutations2(std::move(s), s.size(), out);
    return out;
}

template<typename Item_type>
void permutations2(
        std::vector<Item_type> &&a,
        std::size_t n,
        std::vector<std::vector<Item_type>> &out
)
{
    if (n == 1) {
        out.emplace_back(a);
        return;
    }
    for (auto i = 0; i < n; ++i) {
        std::swap(a[i], a[n - 1]);
        permutations2(std::move(a), n - 1, out);
        std::swap(a[i], a[n - 1]);
    }
}

template<typename Item_type>
std::vector<std::vector<Item_type>> permutations2(std::vector<Item_type> a)
{
    std::vector<std::vector<Item_type>> out;
    permutations2(std::move(a), a.size(), out);
    return out;
}

int main()
{
    auto out = permutations1("abc");
    for (const auto &s : out) {
        std::cout << s << "\n";
    }

    std::cout << "\n";

    auto t = std::vector<int>{1, 2, 3};
    auto out2 = permutations1(t);

    for (const auto &v : out2) {
        for (const auto &i : v) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n";

    auto out3 = permutations2("abc");
    for (const auto &s : out3) {
        std::cout << s << "\n";
    }

    std::cout << "\n";

    auto out4 = permutations2(t);
    for (const auto &v : out4) {
        for (const auto &i : v) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
    return 0;
}