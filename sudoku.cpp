#include <algorithm>
#include <cassert>
#include <cmath>
#include <deque>
#include <iostream>
#include <vector>

bool solve_sudoku(int, int, std::vector<std::vector<int>>&);

bool is_addable(const std::vector<std::vector<int>>&, int, int, int);

// @include
inline bool solve_sudoku(std::vector<std::vector<int>>& partial_assignment) { return solve_sudoku(0, 0, partial_assignment); }

bool solve_sudoku(int i, int j, std::vector<std::vector<int>>& partial_assignment)
{
    const static int empty_entry = 0;
    if (i == partial_assignment.size()) {
        i = 0;
        if (++j == partial_assignment[i].size()) { return true; }
    }
    if ((partial_assignment)[i][j] != empty_entry) { return solve_sudoku(i + 1, j, partial_assignment); }
    for (auto val = 1; val <= partial_assignment.size(); ++val) {
        if (is_addable(partial_assignment, i, j, val)) {
            partial_assignment[i][j] = val;
            if (solve_sudoku(i + 1, j, partial_assignment)) { return true; }
        }
    }
    partial_assignment[i][j] = empty_entry;
    return false;
}

bool is_addable(const std::vector<std::vector<int>>& partial_assignment, int i, int j, int val)
{
    for (auto v : partial_assignment) { if (v[j] == val) { return false; }}
    for (auto e : partial_assignment[i]) { if (e == val) { return false; }}

    auto region_size = static_cast<int>(std::sqrt(partial_assignment.size())); // narrow_cast
    int i2 = i / region_size;
    int j2 = j / region_size;
    for (auto a = 0; a < region_size; ++a) {
        for (auto b = 0; b < region_size; ++b) {
            auto i3 = region_size * i2 + a;
            auto j3 = region_size * j2 + b;
            if (partial_assignment[i3][j3] == val) { return false; }
        }
    }
    return true;
}
// @exclude

int main(int argc, char* argv[])
{
    std::vector<std::vector<int>> a{
            {0, 2, 6, 0, 0, 0, 8, 1, 0},
            {3, 0, 0, 7, 0, 8, 0, 0, 6},
            {4, 0, 0, 0, 5, 0, 0, 0, 7},
            {0, 5, 0, 1, 0, 7, 0, 9, 0},
            {0, 0, 3, 9, 0, 5, 1, 0, 0},
            {0, 4, 0, 3, 0, 2, 0, 5, 0},
            {1, 0, 0, 0, 3, 0, 0, 0, 2},
            {5, 0, 0, 2, 0, 4, 0, 0, 9},
            {0, 3, 8, 0, 0, 0, 4, 6, 0}
    };
    assert(solve_sudoku(a));
    std::vector<std::vector<int>> expected{
            {7, 2, 6, 4, 9, 3, 8, 1, 5},
            {3, 1, 5, 7, 2, 8, 9, 4, 6},
            {4, 8, 9, 6, 5, 1, 2, 3, 7},
            {8, 5, 2, 1, 4, 7, 6, 9, 3},
            {6, 7, 3, 9, 8, 5, 1, 2, 4},
            {9, 4, 1, 3, 6, 2, 7, 5, 8},
            {1, 9, 4, 8, 3, 6, 5, 7, 2},
            {5, 6, 7, 2, 1, 4, 3, 8, 9},
            {2, 3, 8, 5, 7, 9, 4, 6, 1}
    };
    assert(a == expected);
    return 0;
}





void UnitTest(TestSentry::Ptr& sentry, const char* description, SudokuField input)
{
    TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
    stream->RegisterInput(input);
    stream->RegisterExpectedOutput("");
    try {
        solve_sudoku(&input);
        stream->RegisterUserOutput(input, IsValidSudoku(input));
    } catch (...) {
        stream->RegisterUnhandledException();
    }
}

void directed_tests(const TestOptions& options)
{
    TestSentry::Ptr sentry = options.GetTestSentry(16, "Sudoku solver");

    UnitTest(sentry, "Trivial test",
             {{7, 2, 6, 4, 9, 3, 8, 1, 5},
              {3, 1, 5, 7, 2, 8, 9, 4, 6},
              {4, 8, 9, 6, 5, 1, 2, 3, 7},
              {8, 5, 2, 1, 4, 7, 6, 9, 3},
              {6, 7, 3, 9, 8, 5, 1, 2, 4},
              {9, 4, 1, 3, 6, 2, 7, 5, 8},
              {1, 9, 4, 8, 3, 6, 5, 7, 2},
              {5, 6, 7, 2, 1, 4, 3, 8, 9},
              {2, 3, 8, 5, 7, 9, 4, 6, 1}});
    UnitTest(sentry, "Single missing element test",
             {{7, 2, 6, 4, 9, 3, 8, 1, 5},
              {3, 1, 5, 7, 2, 8, 9, 4, 6},
              {4, 8, 9, 6, 5, 1, 2, 3, 7},
              {8, 5, 2, 1, 0, 7, 6, 9, 3},
              {6, 7, 3, 9, 8, 5, 1, 2, 4},
              {9, 4, 1, 3, 6, 2, 7, 5, 8},
              {1, 9, 4, 8, 3, 6, 5, 7, 2},
              {5, 6, 7, 2, 1, 4, 3, 8, 9},
              {2, 3, 8, 5, 7, 9, 4, 6, 1}});
    UnitTest(sentry, "Single missing block test",
             {{7, 2, 6, 4, 9, 3, 8, 1, 5},
              {3, 1, 5, 7, 2, 8, 9, 4, 6},
              {4, 8, 9, 6, 5, 1, 2, 3, 7},
              {8, 5, 2, 0, 0, 0, 6, 9, 3},
              {6, 7, 3, 0, 0, 0, 1, 2, 4},
              {9, 4, 1, 0, 0, 0, 7, 5, 8},
              {1, 9, 4, 8, 3, 6, 5, 7, 2},
              {5, 6, 7, 2, 1, 4, 3, 8, 9},
              {2, 3, 8, 5, 7, 9, 4, 6, 1}});
    UnitTest(sentry, "Easy sudoku test",
             {{4, 0, 8, 6, 1, 9, 5, 7, 2},
              {2, 7, 0, 3, 5, 0, 6, 4, 1},
              {1, 6, 0, 4, 2, 7, 9, 3, 8},
              {8, 5, 1, 7, 6, 0, 3, 9, 4},
              {6, 0, 3, 1, 9, 5, 8, 2, 7},
              {9, 2, 7, 8, 3, 4, 1, 5, 6},
              {3, 8, 0, 9, 4, 1, 7, 6, 5},
              {0, 9, 4, 0, 8, 6, 2, 1, 3},
              {0, 1, 6, 2, 7, 3, 4, 0, 9}});
    UnitTest(sentry, "Medium sudoku test",
             {{0, 0, 0, 1, 7, 4, 0, 8, 3},
              {4, 7, 0, 6, 8, 3, 0, 0, 0},
              {3, 8, 0, 2, 9, 5, 7, 0, 0},
              {0, 0, 4, 9, 5, 1, 0, 7, 6},
              {1, 0, 5, 0, 2, 0, 0, 4, 0},
              {0, 9, 7, 4, 6, 8, 1, 3, 0},
              {7, 0, 0, 0, 0, 9, 8, 6, 0},
              {6, 0, 0, 7, 4, 0, 3, 5, 0},
              {0, 0, 3, 8, 0, 6, 0, 0, 0}});
    UnitTest(sentry, "Hard sudoku test",
             {{0, 2, 6, 0, 0, 0, 8, 1, 0},
              {3, 0, 0, 7, 0, 8, 0, 0, 6},
              {4, 0, 0, 0, 5, 0, 0, 0, 7},
              {0, 5, 0, 1, 0, 7, 0, 9, 0},
              {0, 0, 3, 9, 0, 5, 1, 0, 0},
              {0, 4, 0, 3, 0, 2, 0, 5, 0},
              {1, 0, 0, 0, 3, 0, 0, 0, 2},
              {5, 0, 0, 2, 0, 4, 0, 0, 9},
              {0, 3, 8, 0, 0, 0, 4, 6, 0}});
}



bool has_duplicate(const std::vector<std::vector<int>>&, std::size_t, std::size_t, std::size_t, std::size_t);

// @include
// Check if a partially filled matrix has any conflicts.
bool is_solvable_sudoku(const std::vector<std::vector<int>>& partial_assignment)
{
    // Check row constraints.
    for (std::size_t i = 0; i < partial_assignment.size(); ++i) {
        if (has_duplicate(partial_assignment, i, i + 1, 0, partial_assignment.size())) { return false; }
    }

    // Check column constraints.
    for (std::size_t j = 0; j < partial_assignment.size(); ++j) {
        if (has_duplicate(partial_assignment, 0, partial_assignment.size(), j, j + 1)) { return false; }
    }

    // Check region constraints.
    auto region_size = static_cast<std::size_t>(std::sqrt(partial_assignment.size())); // narrow_cast
    for (auto i2 = 0; i2 < region_size; ++i2) {
        for (auto j2 = 0; j2 < region_size; ++j2) {
            if (has_duplicate(
                    partial_assignment,
                    region_size * i2,
                    region_size * (i2 + 1),
                    region_size * j2,
                    region_size * (j2 + 1))
                    ) { return false; }
        }
    }
    return true;
}

// Return true if subarray partial_assignment[start_row : end_row -
// 1][start_col : end_col - 1] contains any duplicates in {1, 2, ...,
// partial_assignment.size()}; otherwise return false.
bool has_duplicate(
        const std::vector<std::vector<int>>& partial_assignment,
        std::size_t start_row,
        std::size_t end_row,
        std::size_t start_col,
        std::size_t end_col
)
{
    std::deque<bool> is_present(partial_assignment.size() + 1, false);
    for (auto i = start_row; i < end_row; ++i) {
        for (auto j = start_col; j < end_col; ++j) {
            if (partial_assignment[i][j] != 0 && is_present[partial_assignment[i][j]]) { return true; }
            is_present[partial_assignment[i][j]] = true;
        }
    }
    return false;
}
// @exclude

int main(int argc, char* argv[])
{
    std::vector<std::vector<int>> a{
            {0, 2, 6, 0, 0, 0, 8, 1, 0},
            {3, 0, 0, 7, 0, 8, 0, 0, 6},
            {4, 0, 0, 0, 5, 0, 0, 0, 7},
            {0, 5, 0, 1, 0, 7, 0, 9, 0},
            {0, 0, 3, 9, 0, 5, 1, 0, 0},
            {0, 4, 0, 3, 0, 2, 0, 5, 0},
            {1, 0, 0, 0, 3, 0, 0, 0, 2},
            {5, 0, 0, 2, 0, 4, 0, 0, 9},
            {0, 3, 8, 0, 0, 0, 4, 6, 0}
    };
    assert(is_solvable_sudoku(a));
    // There are two 3s.
    a[8] = {3, 3, 8, 0, 0, 0, 4, 6, 0};
    assert(!is_solvable_sudoku(a));
    return 0;
}
