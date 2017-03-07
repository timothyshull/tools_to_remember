#ifndef BST_H
#define BST_H

#include <functional>
#include <stdexcept>
#include <vector>
#include <deque>

// not using references to simplify logic
// difference in comparator norms between C++ and Java require Key_type also implements ==
template<typename Key_type, typename Value_type, typename Key_comparator = std::less<Key_type>>
class Bst {
private:
    struct Node;

    using Owning_node_pointer = Node*;
    using Raw_node_pointer = Node*;

    Owning_node_pointer root = nullptr;
    Key_comparator comp;

    struct Node {
        Key_type key;
        Value_type val;
        Owning_node_pointer left = nullptr;
        Owning_node_pointer right = nullptr;
        std::size_t size;

        Node(Key_type key, Value_type val, std::size_t size) : key{key}, val{val}, size(size) {}

        ~Node()
        {
            if (left != nullptr) { delete left; }
            if (right != nullptr) { delete right; }
        }
    };

public:
    Bst() = default;

    ~Bst() { if (root != nullptr) { delete root; }}

    inline bool empty() const { return size() == 0; }

    inline std::size_t size() const { return _size(root); }

    inline bool contains(Key_type key) const { return get(key) != nullptr; }

    inline Value_type get(Key_type key) const { return _get(root, key); }

    inline void put(Key_type key, Value_type val) { root = _put(root, key, val); }

    void delete_min()
    {
        if (empty()) { throw std::out_of_range{"Symbol table underflow"}; }
        root = _delete_min(root);
    }

    void delete_max()
    {
        if (empty()) { throw std::out_of_range{"Symbol table underflow"}; }
        root = _delete_max(root);
    }

    inline void remove(Key_type key) { root = _remove(root, key); }

    Key_type min() const
    {
        if (empty()) { throw std::out_of_range{"called min() with empty symbol table"}; }
        return _min(root)->key;
    }

    Key_type max() const
    {
        if (empty()) { throw std::out_of_range{"called max() with empty symbol table"}; }
        return _max(root)->key;
    }

    Key_type floor(Key_type key) const
    {
        if (empty()) { throw std::out_of_range{"called floor() with empty symbol table"}; }
        auto x = _floor(root, key);
        if (x == nullptr) { return nullptr; }
        else { return x->key; }
    }

    Key_type ceiling(Key_type key) const
    {
        if (empty()) { throw std::out_of_range{"called ceiling() with empty symbol table"}; }
        auto x = _ceiling(root, key);
        if (x == nullptr) { return nullptr; }
        else { return x->key; }
    }

    Key_type select(std::size_t k)
    {
        if (k < 0 || k >= size()) { throw std::invalid_argument{""}; }
        auto x = _select(root, k);
        return x->key;
    }

    std::size_t rank(Key_type key) const { return _rank(key, root); }

    inline std::vector<Key_type> keys() const { return keys(min(), max()); }

    std::vector<Key_type> keys(Key_type lo, Key_type hi) const
    {
        std::vector<Key_type> v;
        keys(root, v, lo, hi);
        return v;
    }

    std::size_t size(Key_type lo, Key_type hi) const
    {
        if (comp(hi, lo)) { return 0; }
        if (contains(hi)) { return rank(hi) - rank(lo) + 1; }
        else { return rank(hi) - rank(lo); }
    }

    inline int height() const { return _height(root); }

    std::vector<Key_type> level_order()
    {
        std::vector<Key_type> keys;
        std::deque<Raw_node_pointer> queue;
        queue.push_back(root);
        while (!queue.empty()) {
            auto x = queue.front();
            queue.pop_front();
            if (x == nullptr) { continue; }
            keys.push_back(x->key);
            queue.push_back(x->left);
            queue.push_back(x->right);
        }
        return keys;
    }

private:
    std::size_t _size(Raw_node_pointer x) const
    {
        if (x == nullptr) { return 0; }
        else { return x->size; }
    }

    Value_type _get(Raw_node_pointer x, Key_type key) const
    {
        if (x == nullptr) { return nullptr; }
        if (comp(key, x->key)) { return _get(x->left, key); }
        else if (comp(x->key, key)) { return _get(x->right, key); }
        else { return x->val; }
    }

    Raw_node_pointer _put(Raw_node_pointer x, Key_type key, Value_type val)
    {
        if (x == nullptr) { return new Node(key, val, 1); }
        if (comp(key, x->key)) { x->left = _put(x->left, key, val); }
        else if (comp(x->key, key)) { x->right = _put(x->right, key, val); }
        else { x->val = val; }
        x->size = 1 + _size(x->left) + _size(x->right);
        return x;
    }

    Raw_node_pointer _delete_min(Raw_node_pointer x)
    {
        if (x->left == nullptr) { return x->right; }
        x->left = _delete_min(x->left);
        x->size = _size(x->left) + _size(x->right) + 1;
        return x;
    }

    Raw_node_pointer _delete_max(Raw_node_pointer x)
    {
        if (x->right == nullptr) { return x->left; }
        x->right = _delete_max(x->right);
        x->size = _size(x->left) + _size(x->right) + 1;
        return x;
    }

    Raw_node_pointer _remove(Raw_node_pointer x, Key_type key)
    {
        if (x == nullptr) { return nullptr; }

        if (comp(key, x->key)) { x->left = _remove(x->left, key); }
        else if (comp(x->key, key)) { x->right = _remove(x->right, key); }
        else {
            if (x->right == nullptr) { return x->left; }
            if (x->left == nullptr) { return x->right; }
            auto t = x;
            x = _min(t->right);
            x->right = _delete_min(t->right);
            x->left = t->left;
        }
        x->size = _size(x->left) + _size(x->right) + 1;
        return x;
    }

    Raw_node_pointer _min(Raw_node_pointer x) const
    {
        if (x->left == nullptr) { return x; }
        else { return _min(x->left); }
    }

    Raw_node_pointer _max(Raw_node_pointer x) const
    {
        if (x->right == nullptr) { return x; }
        else { return _max(x->right); }
    }

    Raw_node_pointer _floor(Raw_node_pointer x, Key_type key) const
    {
        if (x == nullptr) { return nullptr; }
        if (key == x->key) { return x; }
        if (comp(key, x->key)) { return _floor(x->left, key); }
        auto t = _floor(x->right, key);
        if (t != nullptr) { return t; }
        else { return x; }
    }

    Raw_node_pointer _ceiling(Raw_node_pointer x, Key_type key) const
    {
        if (x == nullptr) { return nullptr; }
        if (key == x->key) { return x; }
        if (comp(key, x->key)) {
            auto t = _ceiling(x->left, key);
            if (t != nullptr) { return t; }
            else { return x; }
        }
        return _ceiling(x->right, key);
    }

    Raw_node_pointer _select(Raw_node_pointer x, std::size_t k)
    {
        if (x == nullptr) { return nullptr; }
        auto t = _size(x->left);
        if (t > k) { return _select(x->left, k); }
        else if (t < k) { return _select(x->right, k - t - 1); }
        else { return x; }
    }

    std::size_t _rank(Key_type key, Raw_node_pointer x) const
    {
        if (x == nullptr) { return 0; }
        if (comp(key, x->key)) { return _rank(key, x->left); }
        else if (comp(x->key, key)) { return 1 + _size(x->left) + _rank(key, x->right); }
        else { return _size(x->left); }
    }

    void keys(Raw_node_pointer x, std::vector<Key_type> queue, Key_type lo, Key_type hi) const
    {
        if (x == nullptr) { return; }
        if (comp(lo, x->key)) { keys(x->left, queue, lo, hi); }
        if ((comp(lo, x->key) || lo == x->key) && (comp(x->key, hi) || x->key == hi)) { queue.push_back(x->key); }
        if (comp(x->key, hi)) { keys(x->right, queue, lo, hi); }
    }

    int _height(Raw_node_pointer x) const
    {
        if (x == nullptr) { return -1; }
        return 1 + std::max(_height(x->left), _height(x->right));
    }

    inline bool _is_bst() const { return _is_bst(root, nullptr, nullptr); }

    bool _is_bst(Raw_node_pointer x, Key_type min, Key_type max) const
    {
        if (x == nullptr) { return true; }
        if (min != nullptr && (comp(x->key, min) || x->key == min)) { return false; }
        if (max != nullptr && (comp(max, x->key) || x->key == min)) { return false; }
        return _is_bst(x->left, min, x->key) && _is_bst(x->right, x->key, max);
    }

};

#endif // BST_H
