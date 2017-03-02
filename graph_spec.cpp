#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Graph.h"

using namespace testing;

TEST(graph, default_ctor_num_vertices)
{
    Graph g;
    ASSERT_THAT(g.num_vertices(), Eq(0));
}

TEST(graph, default_ctor_num_edges)
{
    Graph g;
    ASSERT_THAT(g.num_edges(), Eq(0));
}

TEST(graph, ctor_10_vertices)
{
    Graph g{10};
    ASSERT_THAT(g.num_vertices(), Eq(10));
}

TEST(graph, ctor_10_vertices_10_edges)
{
    Graph g{10};
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 4);
    g.add_edge(4, 5);
    g.add_edge(5, 6);
    g.add_edge(6, 7);
    g.add_edge(7, 8);
    g.add_edge(8, 9);
    g.add_edge(9, 0);
    ASSERT_THAT(g.num_edges(), Eq(10));
}