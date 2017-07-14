#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>

// TODO: convert to class to simplify and rename
int prefix_distance(
        const std::string &a,
        int a_idx,
        const std::string &b,
        int b_idx,
        std::vector<std::vector<int>> &prefix_distances
);

int levenshtein_distance(const std::string &a, const std::string &b)
{
    std::vector<std::vector<int>> prefix_distances(a.size(), std::vector<int>(b.size(), -1));
    return prefix_distance(prefix_distances, a, static_cast<int>(a.size() - 1), b, static_cast<int>(b.size() - 1));
}

int prefix_distance(
        std::vector<std::vector<int>> &prefix_distances,
        const std::string &a,
        int a_idx,
        const std::string &b,
        int b_idx
)
{
    // std::vector<std::vector<int>>& distance_between_prefixes = *distance_between_prefixes_ptr;
    // A is empty so add all of B's characters.
    if (a_idx < 0) {
        return b_idx + 1;
    }
    // B is empty so delete all of A's characters.
    if (b_idx < 0) {
        return a_idx + 1;
    }
    if (prefix_distances[a_idx][b_idx] == -1) {
        if (a[a_idx] == b[b_idx]) {
            prefix_distances[a_idx][b_idx] = prefix_distance(prefix_distances, a, a_idx - 1, b, b_idx - 1);
        } else {
            prefix_distances[a_idx][b_idx] = 1 + std::min(
                    {
                            prefix_distance(prefix_distances, a, a_idx - 1, b, b_idx - 1),
                            prefix_distance(prefix_distances, a, a_idx - 1, b, b_idx),
                            prefix_distance(prefix_distances, a, a_idx, b, b_idx - 1)
                    }
            );
        }
    }
    return prefix_distances[a_idx][b_idx];
}

// recursive implementation is inefficient
std::size_t levenshtein_distance(const std::string &s, std::size_t len_s, const std::string &t, std::size_t len_t)
{
    if (len_s < 0) {
        return len_t + 1;
    }
    if (len_t < 0) {
        return len_s + 1;
    }

    auto cost = (s[len_s - 1] != t[len_t - 1]) ? 1 : 0;
    return std::min(
            {
                    levenshtein_distance(s, len_s - 1, t, len_t) + 1,
                    levenshtein_distance(s, len_s, t, len_t - 1) + 1,
                    levenshtein_distance(s, len_s - 1, t, len_t - 1) + cost
            }
    );
}

// inline int levenshtein_distance(const std::string& s, const std::string& t) { return levenshtein_distance(a, a.size() - 1, b, b.size() - 1); }

// NOTE: check out https://en.wikipedia.org/wiki/Hirschberg%27s_algorithm also