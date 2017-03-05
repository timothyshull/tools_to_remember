#include <vector>
#include <numeric>

// Knuth Vol. 4, algorithm L
// lexicographic combinations
// generates combinations of the form c1 ... ct for numbers 0 ... n-1
std::vector<std::vector<int>> knuth_combinations(int n, int t)
{
    std::vector<std::vector<int>> combinations;
    std::vector<int> c(static_cast<std::vector<int>::size_type>(t + 2));
    std::iota(c.begin(), c.end() - 2, 1);
    c[t] = n;
    c[t + 1] = 0;
//    while (true) {
//        combinations.emplace_back(c.begin(), c.begin() + t + 1);
//        auto j = 0;
//        while (c[j] + 1 == c[j + 1]) {
//            c[j] = j - 1;
//            ++j;
//        }
//        if (j > t) { break; }
//        ++c[j];
//    }

    // or
    auto j = 0;
    while (j < t) {
        combinations.emplace_back(c.begin(), c.begin() + t + 1);
        while (c[j] + 1 == c[j + 1]) {
            c[j] = j - 1;
            ++j;
        }
        if (j <= t) { ++c[j]; }
    }
    return combinations;
}



std::vector<std::vector<int>> knuth_combinations_t(int n, int t)
{
    if (t >= n) { throw std::invalid_argument{"The value t must be less than n"};}
    std::vector<std::vector<int>> combinations;
    std::vector<int> c(static_cast<std::vector<int>::size_type>(t + 2));
    std::iota(c.begin(), c.end() - 2, 1);
    c[t] = n;
    c[t + 1] = 0;
    auto j = t;
    while (true) {
        combinations.emplace_back(c.begin(), c.begin() + t + 1);
        if (j > 0) {
            auto x = j;
            c[j] = x;
            --j;
            continue;
        }

        if (c[0] + 1 < c[1]) {
            ++c[0];
            continue;
        } else {
            j = 2;
        }

        c[j - 1] = j - 2;
        auto x = c[j] + 1;
        while (x == c[j + 1]) {
            ++j;
        }

        if (j > t) { break; }
    }
    return combinations;
}