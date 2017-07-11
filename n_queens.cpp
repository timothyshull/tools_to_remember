#include "n_queens.h"

#include <cassert>
#include <iostream>
#include <random>

// Sedgewick
bool is_consistent(std::vector<int> const &q, int n)
{
    for (int i = 0; i < n; i++) {
        if (q[i] == q[n]) { return false; }   // same column
        if ((q[i] - q[n]) == (n - i)) { return false; }   // same major diagonal
        if ((q[n] - q[i]) == (n - i)) return false;   // same minor diagonal
    }
    return true;
}

void print_queen_placement(std::vector<int> const &q)
{
    auto n = q.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (q[i] == j) { std::cout << "Q \n"; }
            else { std::cout << "* \n"; }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void enumerate(int n)
{
    std::vector<int> a(static_cast<unsigned long>(n));
    enumerate(a, 0);
}

void enumerate(std::vector<int> &q, int k)
{
    auto n = q.size();
    if (k == n) { print_queen_placement(q); }
    else {
        for (auto i = 0; i < n; i++) {
            q[k] = i;
            if (is_consistent(q, k)) { enumerate(q, k + 1); }
        }
    }
}

// EPI
std::vector<std::vector<int>> n_queens(int n)
{
    std::vector<std::vector<int>> result;
    std::vector<int> col;
    solve_n_queens(n, 0, col, result);
    return result;
}

void solve_n_queens(int n, int row, std::vector<int> &col_placement, std::vector<std::vector<int>> &result)
{
    if (row == n) { result.emplace_back(col_placement); }
    else {
        for (auto col = 0; col < n; ++col) {
            col_placement.emplace_back(col);
            if (is_valid(col_placement)) { solve_n_queens(n, row + 1, col_placement, result); }
            col_placement.pop_back();
        }
    }
}

bool is_valid(const std::vector<int> &col_placement)
{
    auto row_id = col_placement.size() - 1;
    for (auto i = 0; i < row_id; ++i) {
        int diff = std::abs(col_placement[i] - col_placement[row_id]);
        if (diff == 0 || diff == row_id - i) { return false; }
    }
    return true;
}

std::vector<std::string> vector_to_string(const std::vector<int> &col_placement)
{
    std::vector<std::string> sol;
    for (auto row : col_placement) {
        std::string line(col_placement.size(), '.');
        line[row] = 'Q';
        sol.emplace_back(line);
    }
    return sol;
}

static void simple_test()
{
    auto result = n_queens(2);
    assert(0 == result.size());

    result = n_queens(3);
    assert(0 == result.size());

    result = n_queens(4);
    assert(2 == result.size());

    std::vector<int> place1{1, 3, 0, 2};
    std::vector<int> place2{2, 0, 3, 1};
    assert(result[0] == place1 || result[0] == place2);
    assert(result[1] == place1 || result[1] == place2);
    assert(result[0] != result[1]);
}

int main(int argc, char **argv)
{
    simple_test();
    std::random_device rd;
    std::default_random_engine gen{rd()};
    auto n = 0;
    if (argc == 2) {
        n = std::stoi(argv[1]);
    } else {
        std::uniform_int_distribution<int> dis{1, 15};
        n = dis(gen);
    }
    std::cout << "n = " << n << "\n";
    auto result = n_queens(n);
    for (const auto &vec : result) {
        auto text_repr = vector_to_string(vec);
        for (const auto &s : text_repr) { std::cout << s << "\n"; }
        std::cout << "\n";
    }
    return 0;
}