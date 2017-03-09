#include <cstddef>
#include <iostream>
#include <vector>
#include <iomanip>
#include <unordered_set>
#include <numeric>

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
std::vector<std::vector<int>> knuth_partition_m_parts(int n, int m)
{
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

class Partition_generator {
private:
    int _x;
    std::size_t _count;
    std::size_t _num_summands;
    int _level;
    std::vector<int> _summands;
    std::vector<int> _coeffs;
    std::vector<int> _remainder;
    int _ci;
    int _ri;
    std::vector<std::vector<int>> _partitions;

public:
    Partition_generator(int part_tgt, int summand_count = 0, const std::vector<int>& summand_subset = {})
            : _x{part_tgt},
              _count{0},
              _num_summands{static_cast<std::size_t>(summand_count ? summand_count : part_tgt)},
              _level{static_cast<int>(_num_summands - 1)},
              _summands(_num_summands),
              _coeffs(_num_summands, 0),
              _remainder(_num_summands, 0),
              _ci{0},
              _ri{part_tgt}
    {
        if (part_tgt <= 0) { throw std::invalid_argument{"The number to partition, n, should be an integer type greater than 0"}; }
        if (!summand_subset.empty()) { for (auto j = 0; j < summand_count; ++j) { _summands[j] = summand_subset[j]; }} // TODO: check if summand_subset[j] is valid
        else { for (auto j = 0; j < _num_summands; ++j) { _summands[j] = j + 1; }}
        _remainder[_num_summands - 1] = _x;
        _generate_partitions();
    }

    ~Partition_generator() = default;

    inline std::vector<std::vector<int>> get_partitions() const { return _partitions; }

private:
    void _print_state()
    {
        std::cout << "x: " << _x << "\n";
        std::cout << "count: " << _count << "\n";
        std::cout << "num_summands: " << _num_summands << "\n";
        std::cout << "level: " << _level << "\n";
        std::cout << "summands: ";
        for (auto e : _summands) { std::cout << " " << e << " "; }
        std::cout << "\n";
        std::cout << "coeffs: ";
        for (auto e : _coeffs) { std::cout << " " << e << " "; }
        std::cout << "\n";
        std::cout << "remainder: ";
        for (auto e : _remainder) { std::cout << " " << e << " "; }
        std::cout << "\n";
        std::cout << "ci: " << _ci << "\n";
        std::cout << "ri: " << _ri << "\n\n\n";
    }

    void _generate_partitions()
    {
        auto start = _level;
        while (start < _num_summands) {
            _print_state();
            if (_level >= _num_summands) { break; }
            // carry over and assign remainder and coefficient from previous iteration
            _remainder[_level] = _ri;
            _coeffs[_level] = _ci;

            _level = _next_partition(_level);

            // zero everything up to level index
            for (auto j = 0; j < _level; ++j) {
                _coeffs[j] = 0;
                _remainder[j] = 0;
            }

            ++_level;
            _ri = _remainder[_level] - _summands[_level]; // for unsigned types, overflow can happen here
            _ci = _coeffs[_level] + 1;

            start = _level - 1;

            // push a partition
            if (start < _num_summands) { _push_partition(); }
        }
    }

    int _next_partition(int i)
    {
        // auto i = level;
        while (true) {
            // zero coefficients and repeat remainder from level downward
            for (; i != 0 && 0 < _remainder[i]; --i) {
                _coeffs[i - 1] = 0;
                _remainder[i - 1] = _remainder[i];
            }

            if (i == 0) {
                if (_remainder[i] != 0 && _summands[i] != 0) { // added && summands[i] != 0 to avoid bad division
                    auto d = _remainder[i] / _summands[i];
                    _remainder[i] -= d * _summands[i]; // for unsigned types overflow can happen here
                    _coeffs[i] = d;
                }
            }

            if (_remainder[i] == 0) { // partition found
                ++_count;
                return i;
            }

            ++i;
            if (i >= _num_summands) { return static_cast<int>(_num_summands); }
            _remainder[i] -= _summands[i];
            ++_coeffs[i];
        }
    }

    void _push_partition()
    {
        std::vector<int> r;
        for (auto k = 0; k < _num_summands; ++k) {
            auto c = _coeffs[k];
            auto v = _summands[k];
            for (auto j = 0; j < c; ++j) { r.push_back(v); }
        }
        _partitions.push_back(r);
    }
};

template<typename Integer_type>
std::vector<Integer_type> partition(const std::vector<Integer_type>& a)
{
    std::vector<std::vector<std::unordered_set<Integer_type>>> table(a.size() + 1, std::vector<std::unordered_set<int>>(a.size() + 1));
    table[0][0].insert(Integer_type(0));
    for (auto i = 1; i <= a.size(); ++i) {
        for (auto j = 0; j <= i; ++j) {
            for (const auto& v : table[i - 1][j]) { table[i][j].insert(v); }
            for (const auto& v : table[i - 1][j]) { table[i][j + 1].insert(v + a[i - 1]); }
        }
    }

    Integer_type sum = std::accumulate(a.cbegin(), a.cend(), Integer_type(0));
    for (auto j = 1; j < a.size(); ++j) {
        for (const auto& v : table[a.size()][j]) {
            if (v * (a.size() - j) == (sum - v) * j) {
                std::vector<Integer_type> ret;
                auto i = a.size();
                auto s2 = v;
                while (i > 0) {
                    if (table[i - 1][j].find(s2) == table[i - 1][j].cend()) {
                        --j;
                        sum -= a[i - 1];
                        ret.push_back(a[i - 1]);
                    }
                    --i;
                }
                return ret;
            }
        }
    }
    return {};
}

class Partition {
public:
    explicit Partition(int n) { partition(n, n, ""); }

private:
    void partition(int n, int max, std::string prefix)
    {
        if (n == 0) {
            std::cout << prefix << "\n";
            return;
        }
        for (auto i = std::min(max, n); i >= 1; --i) { partition(n - i, i, prefix + " " + std::to_string(i)); }
    }
};

class Partition {
    std::vector<std::vector<int>> _partitions;
public:
    explicit Partition(int n) {
        std::vector<int> t;
        partition(n, n, t);
    }

    inline std::vector<std::vector<int>> get_partitions() const { return _partitions; }

private:
    void partition(int n, int max, std::vector<int> v)
    {
        if (n == 0 && !v.empty()) {
            _partitions.emplace_back(v);
            // std::cout << prefix << "\n";
            return;
        }
        for (auto i = std::min(max, n); i >= 1; --i) {
            auto t = v;
            v.push_back(i);
            partition(n - i, i, t);
        }
    }
};


//TEST(partitions, simple_unrestricted)
//{
////    Partition_gen<int> pp{3};
////    std::vector<std::vector<int>> parts;
////    while (pp.next() < 3) {
////        parts.push_back(pp.get_partition());
////    }
//    auto parts = partitions(3);
////
//    ASSERT_THAT(parts.size(), Eq(23));
//}
//
//TEST(knuth_partitions, size_10)
//{
//    auto parts = knuth_partitions(9);
//    ASSERT_THAT(parts.size(), Eq(30));
//}
//
//TEST(knuth_partitions, content_10)
//{
//    auto parts = knuth_partitions(9);
//    ASSERT_THAT(parts, ContainerEq(std::vector<std::vector<int>> {
//            {9},
//            {8, 1},
//            {7, 2},
//            {7, 1, 1},
//            {6, 3},
//            {6, 2, 1},
//            {6, 1, 1, 1},
//            {5, 4},
//            {5, 3, 1},
//            {5, 2, 2},
//            {5, 2, 1, 1},
//            {5, 1, 1, 1, 1},
//            {4, 4, 1},
//            {4, 3, 2},
//            {4, 3, 1, 1},
//            {4, 2, 2, 1},
//            {4, 2, 1, 1, 1},
//            {4, 1, 1, 1, 1, 1},
//            {3, 3, 3},
//            {3, 3, 2, 1},
//            {3, 3, 1, 1, 1},
//            {3, 2, 2, 2},
//            {3, 2, 2, 1, 1},
//            {3, 2, 1, 1, 1, 1},
//            {3, 1, 1, 1, 1, 1, 1},
//            {2, 2, 2, 2, 1},
//            {2, 2, 2, 1, 1, 1},
//            {2, 2, 1, 1, 1, 1, 1},
//            {2, 1, 1, 1, 1, 1, 1, 1},
//            {1, 1, 1, 1, 1, 1, 1, 1, 1}
//    }));
//}




int main()
{
//    std::cout << "Partition_generator(3);\n";
//    Partition_generator pg1{3, 2};
//    std::cout << "Partition_generator(5);\n";
//    Partition_generator pg2{5, 3, {1, 2, 3}};
    Partition p2{5};
    auto t = p2.get_partitions();

    return 0;
}





