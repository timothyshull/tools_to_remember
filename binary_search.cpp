#include <vector>

template<typename Item_type>
int binary_search(std::vector<Item_type>& collection, const Item_type& to_find)
{
    if (collection.empty()) { return -1; }

    int l_bound{0};
    int r_bound{static_cast<int>(collection.size() - 1)};

    int m;
    while (r_bound >= l_bound) {
        m = (l_bound + r_bound) / 2;
        if (to_find == collection[m]) { return m; }
        if (to_find < collection[m]) { r_bound = m - 1; } else { l_bound = m + 1; }
    }

    return -1;
}