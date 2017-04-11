#ifndef TREE_TRAVERSAL_H
#define TREE_TRAVERSAL_H

#include <queue>
#include <stack>

#include "Tree_node.h"

// Traversal
// 5.16 level-order/breadth first -> similar to DSSCPP top-down lr tree bfs
template<typename Item_type, typename Visitor_type>
void breadth_first(Tree_node<Item_type>* root, Visitor_type& visit)
{
    if (root == nullptr) { return; }

    std::queue<Tree_node<Item_type>*> queue;
    queue.push(root);

    while (!queue.empty()) {
        auto t = queue.front();
        queue.pop();
        visit(t);
        if (t->left != nullptr) { queue.push(t->left); }
        if (t->right != nullptr) { queue.push(t->right); }
    }
}

//5.14
template<typename Item_type, typename Visitor_type>
void preorder_recursive(Tree_node<Item_type>* root, Visitor_type& visit)
{
    if (root == nullptr) { return; }
    visit(root);
    preorder_recursive<Item_type, Visitor_type>(root->left, visit);
    preorder_recursive<Item_type, Visitor_type>(root->right, visit);
}

// from DSSCPP
template<typename Item_type, typename Visitor_type>
void inorder_recursive(Tree_node<Item_type>* root, Visitor_type& visit)
{
    if (root == nullptr) { return; }
    inorder_recursive<Item_type, Visitor_type>(root->left, visit);
    visit(root);
    inorder_recursive<Item_type, Visitor_type>(root->right, visit);
}

template<typename Item_type, typename Visitor_type>
void postorder_recursive(Tree_node<Item_type>* root, Visitor_type& visit)
{
    if (root == nullptr) { return; }
    postorder_recursive<Item_type, Visitor_type>(root->left, visit);
    postorder_recursive<Item_type, Visitor_type>(root->right, visit);
    visit(root);
}

// 5.15 - iterative preorder
template<typename Item_type, typename Visitor_type>
void preorder_iterative(Tree_node<Item_type>* root, Visitor_type& visit)
{
    if (root == nullptr) { return; }

    std::stack<Tree_node<Item_type>*> stack;
    stack.push(root);

    while (!stack.empty()) {
        auto t = stack.top();
        stack.pop();
        visit(t);
        if (t->right != nullptr) { stack.push(t->right); }
        if (t->left != nullptr) { stack.push(t->left); }
    }
}

// iterative inorder
template<typename Item_type, typename Visitor_type>
void inorder_iterative(Tree_node<Item_type>* root, Visitor_type& visit)
{
    if (root == nullptr) { return; }

    std::stack<Tree_node<Item_type>*> stack;
    auto t = root;

    while (t != nullptr) {
        while (t != nullptr) {
            if (t->right != nullptr) { stack.push(t->right); }
            stack.push(t);
            t = t->left;
        }

        t = stack.top();
        stack.pop();

        while (!stack.empty() && t->right == nullptr) {
            visit(t);
            t = stack.top();
            stack.pop();
        }

        visit(t);
        if (stack.empty()) { return; }
        t = stack.top();
        stack.pop();
    }
}

// iterative postorder
// NOTE: LRV (left-to-right postorder) traversal generates the same sequence as a
// VRL (right-to-left preorder) traversal
// this uses two temporary pointers to distinguish between nodes with both
// children and nodes with one child. Nodes with two children are pushed to the
// stack twice, once before traversing the left subtree and once before
// traversing the right subtree
template<typename Item_type, typename Visitor_type>
void postorder_iterative(Tree_node<Item_type>* root, Visitor_type& visit)
{
    if (root == nullptr) { return; }

    std::stack<Tree_node<Item_type>*> stack;
    auto t1 = root;
    auto t2 = root;

    while (t1 != nullptr) {
        while (t1->left != nullptr) {
            stack.push(t1);
            t1 = t1->left;
        }

        while (t1->right == nullptr || t1->right == t2) {
            visit(t1);
            t2 = t1;
            if (stack.empty()) { return; }
            t1 = stack.top();
            stack.pop();
        }

        stack.push(t1);
        t1 = t1->right;
    }
}

#endif // TREE_TRAVERSAL_H