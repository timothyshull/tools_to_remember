#include <cstddef>
#include <iostream>
#include <vector>
#include <iomanip>
#include <unordered_set>
#include <numeric>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

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
            // _print_state();
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

// TODO: reconsider this one
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

// http://introcs.cs.princeton.edu/java/23recursion/Partition.java.html
class Partition {
    std::vector<std::vector<int>> _partitions;
public:
    explicit Partition(int n) { partition(n, n, {}); }

    inline std::vector<std::vector<int>> get_partitions() const { return _partitions; }

private:
    void partition(int n, int max, std::vector<int>&& v)
    {
        if (n == 0 && !v.empty()) {
            _partitions.emplace_back(v);
            return;
        }
        for (auto i = std::min(max, n); i >= 1; --i) {
            auto t = v;
            t.push_back(i);
            partition(n - i, i, t);
        }
    }
};


TEST(partitions, simple_3)
{
    Partition p{3};
    auto parts = p.get_partitions();
    ASSERT_THAT(parts.size(), Eq(3));
}

TEST(partitions, gen_3)
{
    Partition_generator p{3};
    auto parts = p.get_partitions();
    ASSERT_THAT(parts.size(), Eq(3));
}

TEST(partitions, simple_10)
{
    Partition p{9};
    auto parts = p.get_partitions();
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

TEST(partitions, gen_10)
{
    Partition_generator p{9};
    auto parts = p.get_partitions();
    ASSERT_THAT(parts, ContainerEq(std::vector<std::vector<int>> {
            {1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 2},
            {1, 1, 1, 1, 1, 2, 2},
            {1, 1, 1, 2, 2, 2},
            {1, 2, 2, 2, 2},
            {1, 1, 1, 1, 1, 1, 3},
            {1, 1, 1, 1, 2, 3},
            {1, 1, 2, 2, 3},
            {2, 2, 2, 3},
            {1, 1, 1, 3, 3},
            {1, 2, 3, 3},
            {3, 3, 3},
            {1, 1, 1, 1, 1, 4},
            {1, 1, 1, 2, 4},
            {1, 2, 2, 4},
            {1, 1, 3, 4},
            {2, 3, 4},
            {1, 4, 4},
            {1, 1, 1, 1, 5},
            {1, 1, 2, 5},
            {2, 2, 5},
            {1, 3, 5},
            {4, 5},
            {1, 1, 1, 6},
            {1, 2, 6},
            {3, 6},
            {1, 1, 7},
            {2, 7},
            {1, 8},
            {9}})
    );
}
