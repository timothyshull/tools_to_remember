#ifndef N_QUEENS_H
#define N_QUEENS_H

#include <vector>

// Sedgewick
bool is_consistent(std::vector<int> const &q, int n);

void print_queen_placement(std::vector<int> const &q);

void enumerate(int n);

void enumerate(std::vector<int> &q, int k);

// EPI
void solve_n_queens(int, int, std::vector<int> &, std::vector<std::vector<int>> &);

bool is_valid(const std::vector<int> &);

std::vector<std::vector<int>> n_queens(int n);

void solve_n_queens(int n, int row, std::vector<int> &col_placement, std::vector<std::vector<int>> &result);

bool is_valid(const std::vector<int> &col_placement);

std::vector<std::string> vector_to_string(const std::vector<int> &col_placement);

#endif // N_QUEENS_H
