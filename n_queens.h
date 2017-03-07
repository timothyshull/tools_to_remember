#ifndef N_QUEENS_H
#define N_QUEENS_H

class n_queens {
/******************************************************************************
 *  Compilation:  javac Queens.java
 *  Execution:    java Queens n
 *
 *  Solve the 8 queens problem using recursion and backtracing.
 *  Prints out all solutions.
 *
 *  Limitations: works for n <= 25, but slows down considerably
 *  for larger n.
 *
 *  Remark: this program implicitly enumerates all n^n possible
 *  placements (instead of n!), but the backtracing prunes off
 *  most of them, so it's not necessarily worth the extra
 *  complication of enumerating only permutations.
 *
 *
 *  % java Queens 3
 *
 *  % java Queens 4
 *  * Q * *
 *  * * * Q
 *  Q * * *
 *  * * Q *
 *
 *  * * Q *
 *  Q * * *
 *  * * * Q
 *  * Q * *
 *
 *  % java Queens 8
 *  Q * * * * * * *
 *  * * * * Q * * *
 *  * * * * * * * Q
 *  * * * * * Q * *
 *  * * Q * * * * *
 *  * * * * * * Q *
 *  * Q * * * * * *
 *  * * * Q * * * *
 *
 *  ...
 *
 ******************************************************************************/


        /***************************************************************************
         * Return true if queen placement q[n] does not conflict with
         * other queens q[0] through q[n-1]
         ***************************************************************************/
    public static boolean isConsistent(int[] q, int n) {
            for (int i = 0; i < n; i++) {
                if (q[i] == q[n])             return false;   // same column
                if ((q[i] - q[n]) == (n - i)) return false;   // same major diagonal
                if ((q[n] - q[i]) == (n - i)) return false;   // same minor diagonal
            }
            return true;
        }

        /***************************************************************************
         * Prints n-by-n placement of queens from permutation q in ASCII.
         ***************************************************************************/
    public static void printQueens(int[] q) {
            int n = q.length;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (q[i] == j) StdOut.print("Q ");
                    else           StdOut.print("* ");
                }
                StdOut.println();
            }
            StdOut.println();
        }


        /***************************************************************************
         *  Try all permutations using backtracking
         ***************************************************************************/
    public static void enumerate(int n) {
            int[] a = new int[n];
            enumerate(a, 0);
        }

    public static void enumerate(int[] q, int k) {
            int n = q.length;
            if (k == n) printQueens(q);
            else {
                for (int i = 0; i < n; i++) {
                    q[k] = i;
                    if (isConsistent(q, k)) enumerate(q, k+1);
                }
            }
        }


    public static void main(String[] args) {
            int n = Integer.parseInt(args[0]);
            enumerate(n);
        }
};





// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>

void solve_n_queens(int, int, std::vector<int>&, std::vector<std::vector<int>>&);

bool is_valid(const std::vector<int>&);

// @include
std::vector<std::vector<int>> n_queens(int n)
{
    std::vector<std::vector<int>> result;
    std::vector<int> col;
    solve_n_queens(n, 0, col, result);
    return result;
}

void solve_n_queens(int n, int row, std::vector<int>& col_placement, std::vector<std::vector<int>>& result)
{
    // All queens are legally placed.
    if (row == n) { result.emplace_back(col_placement); }
    else {
        for (auto col = 0; col < n; ++col) {
            col_placement.emplace_back(col);
            if (is_valid(col_placement)) { solve_n_queens(n, row + 1, col_placement, result); }
            col_placement.pop_back();
        }
    }
}

// test if a newly placed queen will conflict any earlier queens
// placed before.
bool is_valid(const std::vector<int>& col_placement)
{
    auto row_id = col_placement.size() - 1;
    for (auto i = 0; i < row_id; ++i) {
        int diff = std::abs(col_placement[i] - col_placement[row_id]);
        if (diff == 0 || diff == row_id - i) { return false; } // A column or diagonal constraint is violated.
    }
    return true;
}
// @exclude

std::vector<std::string> vector_to_string(const std::vector<int>& col_placement)
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

int main(int argc, char** argv)
{
    simple_test();
    std::random_device rd;
    std::default_random_engine gen{rd()};
    int n{};
    if (argc == 2) {
        n = std::stoi(argv[1]);
    } else {
        std::uniform_int_distribution<int> dis{1, 15};
        n = dis(gen);
    }
    std::cout << "n = " << n << "\n";
    auto result = n_queens(n);
    for (const auto& vec : result) {
        auto text_repr = vector_to_string(vec);
        for (const auto& s : text_repr) { std::cout << s << "\n"; }
        std::cout << "\n";
    }
    return 0;
}


#endif // N_QUEENS_H
