#ifndef TREE_NODE_H
#define TREE_NODE_H

template<typename Item_type>
struct Tree_node;

template<typename Item_type>
struct Tree_node {
    Item_type item;
    Tree_node<Item_type>* left = nullptr;
    Tree_node<Item_type>* right = nullptr;

    ~Tree_node()
    {
        if (left != nullptr) { delete left; }
        if (right != nullptr) { delete right; }
    }
};

#endif // TREE_NODE_H
