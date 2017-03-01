#include <vector>

template<typename Item_type>
struct Tree_node;

template<typename Item_type>
struct Tree_node {
    Item_type value;
    Tree_node<Item_type>* left;
    Tree_node<Item_type>* right;
};

// given a binary tree, a key k return all the nodes with a distance d from the node with key k
template<typename Item_type>
std::vector<Tree_node<Item_type>*> get_successor_nodes(std::vector<Tree_node<Item_type>*>& node_list, Tree_node<Item_type>* node, int d)
{
    if (node == nullptr || d < 0) { return node_list; }

    if (d == 0) {
        node_list.emplace_back(node);
        return node_list;
    }

    get_successor_nodes(node_list, node->left, d - 1);
    get_successor_nodes(node_list, node->right, d - 1);
    return node_list;
}

template<typename Item_type>
std::vector<Tree_node<Item_type>*> nodes_within_distance(Tree_node<Item_type>* root, Item_type& value, int d)
{
    if (root == nullptr || d < 0) { return {}; }

    Tree_node<Item_type>* node{root};
    while (node->value != value && node != nullptr) {
        if (value < node->value) { node = node->left; }
        else if (node->value < value) { node = node->right; }
    }

    std::vector<Tree_node<Item_type>*> res;
    get_successor_nodes(res, node, d);
    return res;
}