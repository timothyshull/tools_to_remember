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
    if (n < 0) { throw std::invalid_argument{"The number to partition, n, should be an integer type greater than 0"}; }
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

template<typename Number_type>
struct Partition_gen {
    Number_type x;

    std::size_t count;
    std::size_t num_summands;
    std::size_t level;

    std::vector<Number_type> summands;
    std::vector<Number_type> coeffs;
    std::vector<Number_type> remainder;
    Number_type ci;
    Number_type ri;

    explicit Partition_gen(Number_type part_tgt, Number_type summand_count = 0, const std::vector<Number_type>& summand_subset = {})
            : x{part_tgt},
              count{0},
              num_summands{static_cast<std::size_t>(summand_count ? summand_count : part_tgt)},
              level{num_summands - 1},
              summands(num_summands + 1), // summands should be const after creation
              coeffs(num_summands + 1, 0),
              remainder(num_summands + 1, 0),
              ci{0},
              ri{part_tgt}
    {
        if (part_tgt <= 0) { throw std::invalid_argument{"The number to partition, n, should be an integer type greater than 0"}; }
        if (!summand_subset.empty()) { for (auto j = 0; j < summand_count; ++j) { summands[j] = summand_subset[j]; }} // TODO: check if summand_subset[j] is valid
        else { for (auto j = 0; j < num_summands; ++j) { summands[j] = j + 1; }}

        remainder[summand_count - 1] = x;
        remainder[summand_count] = x;
    }

    ~Partition_gen() = default;

    Partition_gen(const Partition_gen&) = delete;

    Partition_gen& operator=(const Partition_gen&) = delete;

    std::size_t next()
    {
        if (level >= num_summands) { return num_summands; }
        remainder[level] = ri;
        coeffs[level] = ci;
        level = generate_partition(level);

        for (auto j = 0; j < level; ++j) {
            coeffs[j] = 0;
            remainder[j] = 0;
        }
        ++level;
        ri = remainder[level] - summands[level]; // for unsigned types, overflow can happen here
        ci = coeffs[level] + 1;

        return level - 1;
    }

    std::size_t generate_partition(std::size_t i)
    {
        while (true) {
//            while (i != 0 && 0 < remainder[i]) {
//                coeffs[i - 1] = 0;
//                remainder[i - 1] = remainder[i];
//                --i;
//            }
            // issue with size_t and decrementing here?
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
                return i;
            }

            ++i;
            if (i >= num_summands) { return num_summands; }
            remainder[i] -= summands[i];
            ++coeffs[i];
        }
    }

    std::vector<Number_type> get_partition()
    {
        std::vector<Number_type> r;
        for (auto k = 0; k < x; ++k) {
            auto c = coeffs[k];
            auto v = summands[k];
            for (auto j = 0; j < c; ++j) {
                r.push_back(v);
            }
        }
        return r;
    }
};

// TODO: use print partition to get values formatted to use in test and fix issues with underflow of unsigned types

//TEST(partitions, simple_unrestricted)
//{
//    int n{9};
//
//    Partition_gen<int> p{n};
//    std::vector<std::vector<int>> partitions;
////    while (true) {
////        auto t = p.next();
////        auto u = 1;
////        // partitions.push_back(p.get_partition());
////    }
//    // should compare against the number of summands passed
//    while (p.next() < n) {
//        partitions.push_back(p.get_partition());
//    }
//
//    ASSERT_THAT(partitions.size(), Eq(10));
////    ASSERT_THAT(partitions, UnorderedElementsAre(std::vector<std::vector<std::size_t>> {
////            {1, 1, 1, 1, 1, 1, 1, 1, 1},
////            {1, 1, 1, 1, 1, 1, 1, 2}
////    }));
//}

//int main()
//{
//    std::vector<unsigned> a(10);
//    Test_visitor<unsigned> v;
//    partitions<unsigned, Test_visitor<unsigned>>(10, a, v);
//    v.show_partitions();
//    return 0;
//}

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

        // level = generate_partition(level);
        auto i = level;
        while (true) {
//            while (i != 0 && 0 < remainder[i]) {
//                coeffs[i - 1] = 0;
//                remainder[i - 1] = remainder[i];
//                --i;
//            }
            // issue with size_t and decrementing here?
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

        std::vector<int> r;
        for (auto k = 0; k < x; ++k) {
            auto c = coeffs[k];
            auto v = summands[k];
            for (auto j = 0; j < c; ++j) { r.push_back(v); }
        }
        parts.push_back(r);

        ++level;
        ri = remainder[level] - summands[level]; // for unsigned types, overflow can happen here
        ci = coeffs[level] + 1;

        next_return = level - 1;
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



