#include <vector>

int num_coins(const std::vector<int>& coins, int cents)
{
    auto n = 0;
    for (auto i = 0; i < coins.size(); ++i) {
        n += cents / coins[i];
        cents %= coins[i];
    }
    return n;
}

int min_coins(int amount, const std::vector<int>& coins)
{
    std::vector<int> sub(static_cast<std::vector<int>::size_type>(amount + 1));
    std::vector<int> counts(coins.size());
    sub[0] = 0;
    for (auto total = 1; total <= amount; total++) {
        for (auto j = 0; j < counts.size(); ++j) { counts[j] = -1; }
        for (auto j = 0; j < coins.size(); ++j) {
            if (coins[j] <= total) { counts[j] = sub[total - coins[j]] + 1; }
        }
        sub[total] = -1;
        for (auto j = 1; j < counts.size(); ++j) {
            if (counts[j] > 0 && (sub[total] == -1 || sub[total] > counts[j])) { sub[total] = counts[j]; }
        }
    }
    return sub[amount];
}

int num_ways_to_change(int amount, const std::vector<int>& coins)
{
    if (coins.size() == 0) { return 0; }
    std::vector<std::vector<int>> solution(
            coins.size() + 1,
            std::vector<int>(static_cast<std::vector<int>::size_type>(amount + 1), 0)
    );

    for (auto i = 0; i <= coins.size(); ++i) { solution[i][0] = 1; }
    // for (auto i = 1; i <= amount; ++i) { solution[0][i] = 0; }

    for (auto i = 1; i <= coins.size(); ++i) {
        for (auto j = 1; j <= amount; ++j) {
            if (coins[i - 1] <= j) { solution[i][j] = solution[i - 1][j] + solution[i][j - coins[i - 1]]; }
            else { solution[i][j] = solution[i - 1][j]; }
        }
    }
    return solution[coins.size()][amount];
}