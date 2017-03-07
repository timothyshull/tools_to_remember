#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <numeric>

#include "tree_traversal.h"

using namespace testing;

void build_tree(Tree_node<int>*& root, std::vector<int>& v, int l, int h)
{
    if (l > h) { return; }
    if (root == nullptr) { root = new Tree_node<int>; }
    auto m = (l + h) / 2;
    root->item = v[m];
    build_tree(root->left, v, l, m - 1);
    build_tree(root->right, v, m + 1, h);
}

Tree_node<int>* construct_balanced_tree(int n)
{
    if (n <= 2 || n % 2 != 1) { throw std::invalid_argument{"The size must be even"}; }
    std::vector<int> v(static_cast<std::vector<int>::size_type>(n));
    std::iota(v.begin(), v.end(), 0);
    auto root = new Tree_node<int>;
    build_tree(root, v, 0, n - 1);
    return root;
}

// START tests

TEST(tree_traversal, preorder_recursive)
{
    struct Visitor {
        std::vector<int> vals;

        void operator()(Tree_node<int>* p) { if (p != nullptr) { vals.push_back(p->item); }}
    };

    auto root = construct_balanced_tree(11);
    Visitor v;
    preorder_recursive(root, v);
    ASSERT_THAT(v.vals, ContainerEq(std::vector<int> {5, 2, 0, 1, 3, 4, 8, 6, 7, 9, 10}));
}

TEST(tree_traversal, preorder_iterative)
{
    struct Visitor {
        std::vector<int> vals;

        void operator()(Tree_node<int>* p) { if (p != nullptr) { vals.push_back(p->item); }}
    };

    auto root = construct_balanced_tree(11);
    Visitor v;
    preorder_iterative(root, v);
    ASSERT_THAT(v.vals, ContainerEq(std::vector<int> {5, 2, 0, 1, 3, 4, 8, 6, 7, 9, 10}));
}

TEST(tree_traversal, inorder_recursive)
{
    struct Visitor {
        std::vector<int> vals;

        void operator()(Tree_node<int>* p) { if (p != nullptr) { vals.push_back(p->item); }}
    };

    auto root = construct_balanced_tree(11);
    Visitor v;
    inorder_recursive(root, v);
    ASSERT_THAT(v.vals, ContainerEq(std::vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));
}

TEST(tree_traversal, inorder_iterative)
{
    struct Visitor {
        std::vector<int> vals;

        void operator()(Tree_node<int>* p) { if (p != nullptr) { vals.push_back(p->item); }}
    };

    auto root = construct_balanced_tree(11);
    Visitor v;
    inorder_iterative(root, v);
    ASSERT_THAT(v.vals, ContainerEq(std::vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));
}

TEST(tree_traversal, postorder_recursive)
{
    struct Visitor {
        std::vector<int> vals;

        void operator()(Tree_node<int>* p) { if (p != nullptr) { vals.push_back(p->item); }}
    };

    auto root = construct_balanced_tree(11);
    Visitor v;
    postorder_recursive(root, v);
    ASSERT_THAT(v.vals, ContainerEq(std::vector<int> {1, 0, 4, 3, 2, 7, 6, 10, 9, 8, 5}));
}

TEST(tree_traversal, postorder_iterative)
{
    struct Visitor {
        std::vector<int> vals;

        void operator()(Tree_node<int>* p) { if (p != nullptr) { vals.push_back(p->item); }}
    };

    auto root = construct_balanced_tree(11);
    Visitor v;
    postorder_iterative(root, v);
    ASSERT_THAT(v.vals, ContainerEq(std::vector<int> {1, 0, 4, 3, 2, 7, 6, 10, 9, 8, 5}));
}

TEST(tree_traversal, breadth_first)
{
    struct Visitor {
        std::vector<int> vals;

        void operator()(Tree_node<int>* p) { if (p != nullptr) { vals.push_back(p->item); }}
    };

    auto root = construct_balanced_tree(11);
    Visitor v;
    breadth_first(root, v);
    ASSERT_THAT(v.vals, ContainerEq(std::vector<int> {5, 2, 8, 0, 3, 6, 9, 1, 4, 7, 10}));
}