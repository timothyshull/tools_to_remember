#include <iostream>
#include <queue>

// tree print
template<typename Item_type>
struct Tree_node;

template<typename Item_type>
struct Tree_node {
    Item_type item;
    Tree_node<Item_type>* left;
    Tree_node<Item_type>* right;
};

// tree print -> inorder
template<typename Item_type>
void print_node(Item_type& x, int h)
{
    for (int i = 0; i < h; ++i) { std::cout << "  "; }
    std::cout << x << "\n";
}

template<typename Item_type>
void print_node(Item_type&& x, int h) { print_node(x, h); }

template<typename Item_type>
void show(Tree_node<Item_type>* node, int h = 0)
{
    if (node == nullptr) {
        print_node<char>('*', h);
        return;
    }
    show(node->right, h + 1);
    print_node(node->item, h);
    show(node->left, h + 1);
}

// level order print -> BFS and newline for each level
template<typename Item_type>
void breadth_first_print(Tree_node<Item_type>* root)
{
    if (root == nullptr) { return; }

    std::queue<Tree_node<Item_type>*> queue;
    Tree_node<Item_type> dummy;
    Tree_node<Item_type>* tmp;

    queue.push(root);
    queue.push(&dummy);
    while (!queue.empty()) {
        tmp = queue.front();
        queue.pop();
        if (tmp != &dummy) {
            std::cout << tmp->item << " ";
            if (tmp->left != nullptr) { queue.push(tmp->left); }
            if (tmp->right != nullptr) { queue.push(tmp->right); }
        } else {
            std::cout << "\n";
            if (!queue.empty()) { queue.push(&dummy); }
        }
    }
}