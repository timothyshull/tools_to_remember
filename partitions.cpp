#include <cstddef>
#include <iostream>
#include <vector>
#include <iomanip>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

// Knuth partitions - Algorithm P, V4
// returns partitions in reverse lexicographic order
// previously used a Visitor class to accumulate partitions -> removed to simplify
// n - value to partition, changes throughout
// a - current partition
// m
// q
// x
std::vector<std::vector<int>> knuth_partitions(int n)
{
    if (n < 0) { throw std::invalid_argument{"The number to partition, n, should be an integer greater than 0"}; }
    std::vector<std::vector<int>> partitions;
    std::vector<int> a(static_cast<std::vector<int>::size_type>(n), 0);
    // auto n = n - 1;
    if (n == 0) { return partitions; }
    // P1
    a[0] = 0;
    auto m = 1;
    while (true) { // P2
        a[m] = n;
        auto q = n == 1 ? m - 1 : m;
        while (true) { // P3
            partitions.emplace_back(a.begin() + 1, a.begin() + m + 1); // begin + m + 1 is 1 past m so ends at a sub m
            if (a[q] == 2) { // P4
                a[q] = 1;
                --q;
                ++m;
                a[m] = 1;
                continue; // goto P3
            } else { // P5
                if (q == 0) { return partitions; }
                auto x = a[q] - 1;
                a[q] = x;
                n = m - q + 1;
                m = q + 1;
                while (x < n) { // P6
                    a[m] = x;
                    ++m;
                    n -= x;
                }
                break; // goto P2
            }
        }
    }
}


// TODO: test
// n = 11 and m = 4
// 8111, 7211, 6311, 5411, 5321, 4421, 4331, 5222, 4322, 3332
std::vector<std::vector<int>> knuth_partition_m_parts(int n, int m) {
    if (m < 2 || m > n) { throw std::invalid_argument{"The number of parts, m, should be 2 <= m <= n"}; }
    std::vector<std::vector<int>> partitions;
    // H1
    std::vector<int> a(static_cast<std::vector<int>::size_type>(m + 1), 1);
    a[0] = n - m + 1;
    a[m] = -1;

    while (true) {
        partitions.emplace_back(a.begin(), a.begin() + m + 1);
        if (a[1] < a[0] - 1) {
            --a[0];
            ++a[1];
        } else { // H4
            auto j = 2; // 3 in algorithm
            auto s = a[0] + a[1] - 1;
            while (a[j] >= a[0] - 1) {
                s = s + a[j];
                ++j;
            }
            // s = a1 + ... a sub (j - 1) - 1
            if (j > m) { break; }
            auto x = a[j] + 1;
            a[j] = x;
            // ++a[j];
            --j;
            while (j >= 1) { // j > 1 ?
                a[j] = x;
                s -= x;
                --j;
            }
            a[0] = s; // inside while loop?
        }
    }
    return partitions;
}

std::vector<std::vector<int>> partitions(int part_tgt, int summand_count = 0, const std::vector<int>& summand_subset = {})
{
    auto x = part_tgt;
    auto count = 0;
    auto num_summands = static_cast<std::size_t>(summand_count ? summand_count : part_tgt);
    auto level = num_summands - 1;
    std::vector<int> summands(num_summands + 1); // summands should be const after creation
    std::vector<int> coeffs(num_summands + 1, 0);
    std::vector<int> remainder(num_summands + 1, 0);
    auto ci = 0;
    auto ri = part_tgt;
    if (part_tgt <= 0) { throw std::invalid_argument{"The number to partition, n, should be an integer type greater than 0"}; }
    if (!summand_subset.empty()) { for (auto j = 0; j < summand_count; ++j) { summands[j] = summand_subset[j]; }} // TODO: check if summand_subset[j] is valid
    else { for (auto j = 0; j < num_summands; ++j) { summands[j] = j + 1; }}

    remainder[summand_count - 1] = x;
    remainder[summand_count] = x;

    std::vector<std::vector<int>> parts;

    auto next_return = level;
    while (next_return < num_summands) {
        if (level >= num_summands) { break; }
        remainder[level] = ri;
        coeffs[level] = ci;

        auto i = level;
        while (true) {
            for (; i != 0 && 0 < remainder[i]; --i) {
                coeffs[i - 1] = 0;
                remainder[i - 1] = remainder[i];
            }

            if (i == 0) {
                if (remainder[i] != 0 && summands[i] != 0) { // added && summands[i] != 0 to avoid bad division
                    auto d = remainder[i] / summands[i];
                    remainder[i] -= d * summands[i]; // for unsigned types overflow can happen here
                    coeffs[i] = d;
                }
            }

            if (remainder[i] == 0) { // partition found
                ++count;
                level = i;
                break;
            }

            ++i;
            if (i >= num_summands) {
                level = num_summands;
                break;
            }
            remainder[i] -= summands[i];
            ++coeffs[i];
        }

        for (auto j = 0; j < level; ++j) {
            coeffs[j] = 0;
            remainder[j] = 0;
        }

        ++level;
        ri = remainder[level] - summands[level]; // for unsigned types, overflow can happen here
        ci = coeffs[level] + 1;

        next_return = level - 1;

        if (next_return < num_summands) {
            std::vector<int> r;
            for (auto k = 0; k < x; ++k) {
                auto c = coeffs[k];
                auto v = summands[k];
                for (auto j = 0; j < c; ++j) { r.push_back(v); }
            }
            parts.push_back(r);
        }
    }
    return parts;
};

TEST(partitions, simple_unrestricted)
{
//    Partition_gen<int> pp{3};
//    std::vector<std::vector<int>> parts;
//    while (pp.next() < 3) {
//        parts.push_back(pp.get_partition());
//    }
    auto parts = partitions(3);
//
    ASSERT_THAT(parts.size(), Eq(23));
}

TEST(knuth_partitions, size_10)
{
    auto parts = knuth_partitions(9);
    ASSERT_THAT(parts.size(), Eq(30));
}

TEST(knuth_partitions, content_10)
{
    auto parts = knuth_partitions(9);
    ASSERT_THAT(parts, ContainerEq(std::vector<std::vector<int>> {
            {9},
            {8, 1},
            {7, 2},
            {7, 1, 1},
            {6, 3},
            {6, 2, 1},
            {6, 1, 1, 1},
            {5, 4},
            {5, 3, 1},
            {5, 2, 2},
            {5, 2, 1, 1},
            {5, 1, 1, 1, 1},
            {4, 4, 1},
            {4, 3, 2},
            {4, 3, 1, 1},
            {4, 2, 2, 1},
            {4, 2, 1, 1, 1},
            {4, 1, 1, 1, 1, 1},
            {3, 3, 3},
            {3, 3, 2, 1},
            {3, 3, 1, 1, 1},
            {3, 2, 2, 2},
            {3, 2, 2, 1, 1},
            {3, 2, 1, 1, 1, 1},
            {3, 1, 1, 1, 1, 1, 1},
            {2, 2, 2, 2, 1},
            {2, 2, 2, 1, 1, 1},
            {2, 2, 1, 1, 1, 1, 1},
            {2, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1}
    }));
}







template<typename T>
vector<T> partition(const vector<T>& A)
{
    vector<vector<unordered_set<T>>> table(
            A.size() + 1, vector<unordered_set<int>>(A.size() + 1));
    table[0][0].insert(T(0));
    for (int i = 1; i <= A.size(); ++i) {
        for (int j = 0; j <= i; ++j) {
            for (const T& v : table[i - 1][j]) {
                table[i][j].insert(v);
            }
            for (const T& v : table[i - 1][j]) {
                table[i][j + 1].insert(v + A[i - 1]);
            }
        }
    }

    T sum = accumulate(A.cbegin(), A.cend(), T(0));
    for (int j = 1; j < A.size(); ++j) {
        for (const T& v : table[A.size()][j]) {
            if (v * (A.size() - j) == (sum - v) * j) {
                vector<T> ret;
                int i = A.size();
                T sum = v;
                while (i > 0) {
                    if (table[i - 1][j].find(sum) == table[i - 1][j].cend()) {
                        --j;
                        sum -= A[i - 1];
                        ret.push_back(A[i - 1]);
                    }
                    --i;
                }
                return ret;
            }
        }
    }
    return vector<int>();
}



