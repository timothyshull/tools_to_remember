#include <stdexcept>

// Binary search in a BST (just check if key is in tree)
template<typename Key_type, typename Value_type>
struct BST_node;

template<typename Key_type, typename Value_type>
struct BST_node {
    Key_type key;
    Value_type value;
    BST_node<Key_type, Value_type>* left;
    BST_node<Key_type, Value_type>* right;
};

template<typename Key_type, typename Value_type>
class BST {
public:
    Value_type get(const Key_type& key)
    {
        return _get(root, key);
    }

    int rank(const Key_type& key)
    {
        return _rank(root, key);
    }

private:
    BST_node<Key_type, Value_type>* root;

    Value_type _get(BST_node<Key_type, Value_type>* root, const Key_type& key)
    {
        if (root == nullptr) { throw std::out_of_range{}; }
        if (key < root->key) { return _get(root->left, key); }
        else if (root->key < key) { return _get(root->right, key); }
        else { return root->value; }
    }

    int _rank(BST_node<Key_type, Value_type>* root, const Key_type& key)
    {
        if (root == nullptr) { return 0; }
        if (key < root->key) { return _rank(key, root->left); }
        else if (root->key < key) { return 1 + _size(root->left) + _rank(key, root->right); }
        else { return _size(root->left); }
    }

    int _size(BST_node<Key_type, Value_type>* node)
    {
        if (node == nullptr) { return 0; }
        else { return 1 + _size(node->left) + _size(node->right); }
    }
};