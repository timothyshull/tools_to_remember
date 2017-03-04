#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>

int compute_prefix_distance(
        const std::string& a,
        int a_idx,
        const std::string& b,
        int b_idx,
        std::vector<std::vector<int>>& prefix_distances);

int levenshtein_distance(const std::string& a, const std::string& b)
{
    std::vector<std::vector<int>> prefix_distances(a.size(), std::vector<int>(b.size(), -1));
    return compute_prefix_distance(a, static_cast<int>(a.size() - 1), b, static_cast<int>(b.size() - 1), prefix_distances);
}

int compute_prefix_distance(
        const std::string& a,
        int a_idx,
        const std::string& b,
        int b_idx,
        std::vector<std::vector<int>>& prefix_distances)
{
    // std::vector<std::vector<int>>& distance_between_prefixes = *distance_between_prefixes_ptr;
    // A is empty so add all of B's characters.
    if (a_idx < 0) { return b_idx + 1; }
    // B is empty so delete all of A's characters.
    if (b_idx < 0) { return a_idx + 1; }

    if (prefix_distances[a_idx][b_idx] == -1) {
        if (a[a_idx] == b[b_idx]) {
            prefix_distances[a_idx][b_idx] = compute_prefix_distance(a, a_idx - 1, b, b_idx - 1, prefix_distances);
        } else {
            prefix_distances[a_idx][b_idx] = 1 + std::min(
                    {compute_prefix_distance(a, a_idx - 1, b, b_idx - 1, prefix_distances),
                     compute_prefix_distance(a, a_idx - 1, b, b_idx, prefix_distances),
                     compute_prefix_distance(a, a_idx, b, b_idx - 1, prefix_distances)}
            );
        }
    }
    return prefix_distances[a_idx][b_idx];
}

// recursive implementation is inefficient
std::size_t levenshtein_distance(const std::string& s, std::size_t len_s, const std::string& t, std::size_t len_t)
{
    if (len_s < 0) { return len_t + 1; }
    if (len_t < 0) { return len_s + 1; }
    int cost = (s[len_s - 1] != t[len_t - 1]) ? 1 : 0;
    return std::min({levenshtein_distance(s, len_s - 1, t, len_t) + 1, levenshtein_distance(s, len_s, t, len_t - 1) + 1, levenshtein_distance(s, len_s - 1, t, len_t - 1) + cost});
}

// inline int levenshtein_distance(const std::string& s, const std::string& t) { return levenshtein_distance(a, a.size() - 1, b, b.size() - 1); }

// NOTE: check out https://en.wikipedia.org/wiki/Hirschberg%27s_algorithm also