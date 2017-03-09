#include <random>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Depth_first_paths.h"
#include "Union_find.h"

using namespace testing;

TEST(depth_first_paths, simple)
{
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<std::size_t> dis{10, 100};

    auto num_vertices = dis(gen);
    auto num_edges = dis(gen);
    Graph graph{num_vertices};
    std::set<std::pair<int, int>> set;
    std::uniform_int_distribution<int> vdis{0, static_cast<int>(num_vertices)};
    Union_find uf{num_vertices};
    while (graph.num_edges() < num_edges) {
        auto v = vdis(gen);
        auto w = vdis(gen);
        if (v != w && set.find({v, w}) == set.end()) {
            set.insert({v, w});
            graph.add_edge(v, w);
            uf.create_union(v, w);
        }
    }
    auto v = vdis(gen);
    auto w = vdis(gen);
    Depth_first_paths dfp{graph, v};
    ASSERT_THAT(dfp.has_path_to(w), Eq(uf.connected(v, w)));
}