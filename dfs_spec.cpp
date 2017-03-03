#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <random>
#include <stack>

#include "Depth_first_search.h"

using namespace testing;

// manual dfs with explicit stack -> for testing only
bool check_connectivity(Graph& g, int v, int w)
{
    std::unordered_set<int> set;
    std::stack<int> stack;
    stack.push(v);

    int t;
    while (!stack.empty()) {
        t = stack.top();
        stack.pop();
        if (t == w) { return true; }
        if (set.find(t) == set.end()) {
            set.insert(t);
            for (auto u : g.adjacent(t)) {
                if (t == w) { return true; }
                if (set.find(u) == set.end()) { stack.push(u); }
            }
        }
    }

    return false;
}

TEST(dfs, graph_1_vertex)
{
    Graph g{1};
    Depth_first_search d{g, 0};
    ASSERT_THAT(d.count(), Eq(1));
}

TEST(dfs, graph_2_vertices_reachable)
{
    Graph g{2};
    g.add_edge(0, 1);
    Depth_first_search d{g, 0};
    ASSERT_THAT(d.count(), Eq(2));
}

TEST(dfs, graph_2_vertices_unreachable)
{
    Graph g{2};
    Depth_first_search d{g, 0};
    ASSERT_THAT(d.count(), Eq(1));
}

TEST(dfs, graph_2_vertices_reachable_visited)
{
    Graph g{2};
    g.add_edge(0, 1);
    Depth_first_search d{g, 0};
    ASSERT_TRUE(d.visited(0));
    ASSERT_TRUE(d.visited(1));
}

TEST(dfs, graph_2_vertices_unreachable_visited)
{
    Graph g{2};
    Depth_first_search d{g, 0};
    ASSERT_TRUE(d.visited(0));
    ASSERT_FALSE(d.visited(1));
}

TEST(dfs, graph_5_vertices_reachable)
{
    Graph g{5};
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 4);
    Depth_first_search d{g, 0};
    ASSERT_THAT(d.count(), Eq(5));
}

TEST(dfs, graph_5_vertices_reachable_visited)
{
    Graph g{5};
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 4);
    Depth_first_search d{g, 0};
    ASSERT_TRUE(d.visited(0));
    ASSERT_TRUE(d.visited(1));
    ASSERT_TRUE(d.visited(2));
    ASSERT_TRUE(d.visited(3));
    ASSERT_TRUE(d.visited(4));
}

TEST(dfs, graph_5_vertices_2_reachable)
{
    Graph g{5};
    g.add_edge(0, 1);
    Depth_first_search d{g, 0};
    ASSERT_THAT(d.count(), Eq(2));
}

TEST(dfs, graph_randomized)
{
    // std::size_t max_num_vertices{10000};
    std::size_t max_num_vertices{100};
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<std::size_t> dis{0, max_num_vertices};

    auto num_vertices = dis(gen);
    std::uniform_int_distribution<> vdis{0, static_cast<int>(num_vertices - 1)};

    // the set does not disallow self-loops so really v^2 (vs v^2 - v)
    auto max_num_edges = static_cast<std::size_t>(num_vertices ^ 4);
    std::uniform_int_distribution<std::size_t> edis{1, max_num_edges};
    auto num_edges = edis(gen);

    Graph g{num_vertices};

    std::unordered_set<int> path;
    while (num_edges) {
        path.insert(vdis(gen));
        --num_edges;
    }
    auto it1 = path.begin();
    auto it2 = path.begin();
    if (it1 != path.end()) { ++it1; }
    for (; it1 != path.end(); ++it1, (void) ++it2) { g.add_edge(*it2, *it1); }

    auto start_vertex = *path.begin();
    Depth_first_search d{g, start_vertex};
    for (auto i = 0; i < num_vertices; ++i) { ASSERT_EQ(check_connectivity(g, start_vertex, i), d.visited(i)); }
}