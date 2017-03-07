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
    Tree_node<Item_type>* tmp;

    queue.push(root);
    while (!queue.empty()) {
        tmp = queue.front();
        queue.pop();
        visit(tmp);
        if (tmp->left != nullptr) { queue.push(tmp->left); }
        if (tmp->right != nullptr) { queue.push(tmp->right); }
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
    Tree_node<Item_type>* tmp;

    stack.push(root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        visit(tmp);
        if (tmp->right != nullptr) { stack.push(tmp->right); }
        if (tmp->left != nullptr) { stack.push(tmp->left); }
    }
}

// iterative inorder
template<typename Item_type, typename Visitor_type>
void inorder_iterative(Tree_node<Item_type>* root, Visitor_type& visit)
{
    if (root == nullptr) { return; }

    std::stack<Tree_node<Item_type>*> stack;
    Tree_node<Item_type>* tmp{root};

    while (tmp != nullptr) {

        while (tmp != nullptr) {
            if (tmp->right) { stack.push(tmp->right); }
            stack.push(tmp);
            tmp = tmp->left;
        }

        tmp = stack.top();
        stack.pop();

        while (!stack.empty() && tmp->right == nullptr) {
            visit(tmp);
            tmp = stack.top();
            stack.pop();
        }

        visit(tmp);

        if (!stack.empty()) {
            tmp = stack.top();
            stack.pop();
        } else {
            tmp = nullptr;
        }
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
    Tree_node<Item_type>* t1{root};
    Tree_node<Item_type>* t2{root};

    while (t1 != nullptr) {
        for (; t1->left != nullptr; t1 = t1->left) { stack.push(t1); }

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