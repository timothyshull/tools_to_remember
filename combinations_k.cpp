#include <vector>
#include <iostream>

// requires integer type
template<typename Item_type>
void combinations_k(
        std::vector<Item_type> &items,
        std::size_t position,
        Item_type next,
        std::size_t combo_size,
        std::size_t num_elems,
        std::vector<std::vector<Item_type>> &out
)
{
    if (position == combo_size) {
        out.push_back({items.begin(), items.end()});
        return;
    }
    for (auto i = next; i < num_elems; ++i) {
        items[position] = i;
        combinations_k(items, position + 1, i + 1, combo_size, num_elems, out);
    }
}

template<typename Item_type>
std::vector<std::vector<Item_type>> combinations_k(
        std::size_t combo_size,
        std::size_t num_elems
)
{
    std::vector<Item_type> items(combo_size, 0);
    std::vector<std::vector<Item_type>> out;
    combinations_k(items, 0, 0, combo_size, num_elems, out);
    return out;
}

int main()
{
    auto out = combinations_k<int>(3, 5);
    for (const auto &v : out) {
        for (const auto &e : v) {
            std::cout << e << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
