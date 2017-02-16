#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>

std::vector<int> rand_vector(int len)
{
    std::vector<int> ret;
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<int> dis{0, 99};
    while (--len) {
        ret.emplace_back(dis(gen));
    }
    return ret;
}

struct Item;

int optimum_subject_to_item_capacity(const std::vector<Item>&, int, int, std::vector<std::vector<int>>&);

// @include
struct Item {
    int weight;
    int value;
};

int optimum_subject_to_capacity(const std::vector<Item>& items, int capacity)
{
    // V[i][j] holds the optimum value when we choose from items[0 : i] and have
    // a capacity of j.
    std::vector<std::vector<int>> v(items.size(), std::vector<int>(static_cast<std::vector<int>::size_type>(capacity + 1), -1));
    // narrow_cast
    return optimum_subject_to_item_capacity(items, static_cast<int>(items.size() - 1), capacity, v);
}

// Returns the optimum value when we choose from items[0 : k] and have a
// capacity of available_capacity.
int optimum_subject_to_item_capacity(const std::vector<Item>& items, int k, int available_capacity, std::vector<std::vector<int>>& v)
{
    if (k < 0) {
        // No items can be chosen.
        return 0;
    }

    if (v[k][available_capacity] == -1) {
        int without_curr_item{optimum_subject_to_item_capacity(items, k - 1, available_capacity, v)};
        int with_curr_item{available_capacity < items[k].weight ?
                           0 :
                           items[k].value + optimum_subject_to_item_capacity(items, k - 1, available_capacity - items[k].weight, v)};
        v[k][available_capacity] = std::max(without_curr_item, with_curr_item);
    }
    return v[k][available_capacity];
}


// dynamic
//int knapsack(int m)
//{
//    int i, space, max, maxi = 0, t;
//    if (maxKnown[m] != unknown) { return maxKnown[m]; }
//    for (i = 0, max = 0; i < N; i++) {
//        if ((space = m - items[i].size) >= 0) {
//            if ((t = knap(space) + items[i].val) > max) {
//                max = t;
//                maxi = i;
//            }
//        }
//    }
//    maxKnown[m] = max;
//    itemKnown[m] = items[maxi];
//    return max;
//}

// recursive
//int knapsack(int cap)
//{
//    int i;
//    int space;
//    int max;
//    int t;
//    for (i = 0, max = 0; i < N; ++i) {
//        if ((space = cap - items[i].size) >= 0) {
//            if ((t = knapsack(space) + items[i].val) > max) {
//                max = t;
//            }
//        }
//    }
//    return max;
//}