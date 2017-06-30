#include <string>
#include <vector>
#include <iostream>

void permutations_k(std::string &&a, std::size_t n, std::size_t k, std::vector<std::string> &out)
{
    if (k == 0) {
        out.emplace_back(a.substr(n, std::string::npos));
        return;
    }

    for (auto i = 0; i < n; ++i) {
        std::swap(a[i], a[n - 1]);
        permutations_k(std::move(a), n - 1, k - 1, out);
        std::swap(a[i], a[n - 1]);
    }
}

std::vector<std::string> permutations_k(std::string a, std::size_t k)
{
    std::vector<std::string> out;
    permutations_k(std::move(a), a.size(), k, out);
    return out;
}

template<typename Item_type>
void permutations_k(
        std::vector<Item_type> &&a,
        std::size_t n,
        std::size_t k,
        std::vector<std::vector<Item_type>> &out
)
{
    if (k == 0) {
        out.emplace_back(a.begin() + n, a.end());
        return;
    }

    for (auto i = 0; i < n; ++i) {
        std::swap(a[i], a[n - 1]);
        permutations_k(std::move(a), n - 1, k - 1, out);
        std::swap(a[i], a[n - 1]);
    }
}

template<typename Item_type>
std::vector<std::vector<Item_type>> permutations_k(std::vector<Item_type> a, std::size_t k)
{
    std::vector<std::vector<Item_type>> out;
    permutations_k(std::move(a), a.size(), k, out);
    return out;
}

int main()
{
    auto out = permutations_k("abcd", 2);
    for (const auto &s : out) {
        std::cout << s << "\n";
    }

    std::cout << "\n";

    auto t = std::vector<int>{1, 2, 3, 4};
    auto out2 = permutations_k(t, 2);
    for (const auto &v: out2) {
        for (const auto &e : v) {
            std::cout << e << " ";
        }
        std::cout << "\n";
    }

    return 0;
}