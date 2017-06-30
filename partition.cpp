#include <vector>
#include <iostream>

template<typename Item_type>
void partition(
        const Item_type item,
        const Item_type max,
        std::vector<Item_type> &&cpart,
        std::vector<std::vector<Item_type>> &parts
)
{
    if (item == 0 && !cpart.empty()) {
        parts.emplace_back(cpart);
        return;
    }

    for (auto i = std::min(max, item); i >= 1; --i) {
        auto t = cpart;
        t.push_back(i);
        partition(item - i, i, std::move(t), parts);
    }
}

// integral type
template<typename Item_type>
std::vector<std::vector<Item_type>> partition(const Item_type n)
{
    std::vector<std::vector<Item_type>> out;
    partition<Item_type>(n, n, {}, out);
    return out;
}

int main()
{
    auto out = partition(6);
    for (const auto &v : out) {
        for (const auto &e : v) {
            std::cout << e << " ";
        }
        std::cout << "\n";
    }
    return 0;
}