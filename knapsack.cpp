#include <vector>
#include <deque>

// TODO: come back to this and test
template<typename Item_type>
std::pair<Item_type, std::vector<Item_type>> knapsack(
        const std::vector<Item_type> &profits,
        const std::vector<Item_type> &weights,
        const Item_type &max_weight
)
{
    auto n = profits.size();
    auto w = weights.size();
    std::vector<std::vector<Item_type>> options(n + 1, std::vector<Item_type>(max_weight + 1));
    std::vector<std::deque<bool>> solution(n + 1, std::deque<bool>(max_weight + 1));

    for (auto i = 1; i <= n; ++i) {
        for (auto j = 1; j <= max_weight; ++j) {
            auto option1 = options[i - 1][j];

            auto option2 = weights[i] <= j ?
                           profits[i] + options[i - 1][j - weights[i]] :
                           std::numeric_limits<Item_type>::max();
            options[i][j] = std::max(option1, option2);
            solution[n][w] = option1 < option2;
        }
    }

    std::vector<Item_type> to_take;
    for (auto i = n, j = w; n > 0; --n) {
        if (solution[i][j]) {
            to_take.push_back(n);
            j = j - weights[i];
        }
    }
    return {options[n][max_weight], to_take};
}