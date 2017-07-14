#include <vector>
#include <deque>
#include <set>
#include <iostream>

class Knapsack {
private:
    std::vector<int> const &_profits;
    std::vector<int> const &_weights;
    std::vector<std::vector<int>> _options;
    std::vector<std::deque<bool>> _solution;
    int _num_items;
    int _max_weight;

public:
    Knapsack(std::vector<int> const &profits, std::vector<int> const &weights, int max_weight)
            : _profits{profits},
              _weights{weights},
              _options(profits.size() + 1, std::vector<int>(static_cast<std::vector<int>::size_type>(max_weight + 1))),
              _solution{profits.size() + 1, std::deque<bool>(static_cast<std::deque<bool>::size_type>(max_weight + 1))},
              _num_items{static_cast<int>(profits.size())},
              _max_weight{max_weight}
    {
        for (auto i = 1; i <= _num_items; ++i) {
            for (auto j = 1; j <= _max_weight; ++j) {
                auto option1 = _options[i - 1][j];
                auto option2 = std::numeric_limits<int>::min();
                if (_weights[i - 1] <= j) {
                    option2 = _profits[i - 1] + _options[i - 1][j - _weights[i - 1]]; // item 1 is index 0
                }

                _options[i][j] = std::max(option1, option2);
                _solution[i][j] = option1 < option2;
            }
        }
    }

    std::set<int> get_items_to_take()
    {
        auto items_to_take = std::set<int>{};
        auto n = _num_items;
        auto w = _max_weight;
        while (n > 0) {
            if (_solution[n][w]) {
                items_to_take.emplace(n);
                w = w - _weights[n - 1];
            }
            --n;
        }
        return items_to_take;
    }

    int get_total_weight()
    {
        auto n = _num_items;
        auto w = _max_weight;
        auto total_weight = 0;
        while (n > 0) {
            if (_solution[n][w]) {
                total_weight += _weights[n - 1];
                w = w - _weights[n - 1];
            }
            --n;
        }
        return total_weight;
    }

    int get_max_profit()
    {
        return _options[_num_items][_max_weight];
    }
};

int main()
{
    auto profits = std::vector<int>{874, 620, 345, 369, 360, 470};
    auto weights = std::vector<int>{580, 1616, 1906, 1942, 50, 294};
    auto knapsack = Knapsack{profits, weights, 2000};
    for (const auto e : knapsack.get_items_to_take()) {
        std::cout << e << "\n";
    }
    std::cout << knapsack.get_max_profit() << "\n";
    std::cout << knapsack.get_total_weight() << "\n";
    return 0;
}