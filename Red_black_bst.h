#ifndef TOOLS_TO_REMEMBER_RED_BLACK_BST_H
#define TOOLS_TO_REMEMBER_RED_BLACK_BST_H

#include <functional>
#include <algorithm>
#include <vector>

template<typename Key_type, typename Value_type, typename Key_comparator = std::less<Key_type>>
class Red_black_bst {
private:
    enum class Color : bool { red, black };

    struct Node;

    using Owning_node_pointer = Node*;
    using Raw_node_pointer = Node*;

    Owning_node_pointer _root = nullptr;
    Key_comparator _comp;

    struct Node {
        Key_type key;
        Value_type val;
        Owning_node_pointer left = nullptr;
        Owning_node_pointer right = nullptr;
        Color color;
        std::size_t size = 0;

        Node(Key_type key, Value_type val, Color color, std::size_t size)
                : key{key},
                  val{val},
                  color{color},
                  size{size} {}

        ~Node()
        {
            if (left != nullptr) { delete left; }
            if (right != nullptr) { delete right; }
        }
    };

public:
    Red_black_bst() {}

    ~Red_black_bst() { if (_root != nullptr) { delete _root; }}

    inline std::size_t size() const noexcept { return _size(_root); }

    inline bool empty() const noexcept { return _root == nullptr; }

    inline Value_type get(Key_type key) const { return _get(_root, key); }

    inline bool contains(Key_type key) const { return get(key) != nullptr; }

    void put(Key_type key, Value_type val)
    {
        _root = _put(_root, key, val);
        _root->color = Color::black;
    }

    void delete_min()
    {
        if (empty()) { throw std::out_of_range{"BST underflow"}; }
        if (!_is_red(_root->left) && !_is_red(_root->right)) { _root->color = Color::red; }
        _root = _delete_min(_root);
        if (!empty()) { _root->color = Color::black; }
    }

    void delete_max()
    {
        if (empty()) { throw std::out_of_range{"BST underflow"}; }
        if (!_is_red(_root->left) && !_is_red(_root->right)) { _root->color = Color::red; }
        _root = _delete_max(_root);
        if (!empty()) { _root->color = Color::black; }
    }

    void remove(Key_type key)
    {
        if (!contains(key)) { return; }
        if (!_is_red(_root->left) && !_is_red(_root->right)) { _root->color = Color::red; }
        _root = _remove(_root, key);
        if (!empty()) { _root->color = Color::black; }
    }

    inline int height() const noexcept { return _height(_root); }

    Key_type min()
    {
        if (empty()) { throw std::out_of_range{"called min() with empty symbol table"}; }
        return _min(_root)->key;
    }

    Key_type max()
    {
        if (empty()) { throw std::out_of_range{"called max() with empty symbol table"}; }
        return _max(_root)->key;
    }

    Key_type floor(Key_type key)
    {
        if (empty()) { throw std::out_of_range{"called floor() with empty symbol table"}; }
        auto x = _floor(_root, key);
        if (x == nullptr) { return nullptr; }
        else { return x->key; }
    }

    Key_type ceiling(Key_type key)
    {
        if (empty()) { throw std::out_of_range{"called ceiling() with empty symbol table"}; }
        auto x = _ceiling(_root, key);
        if (x == nullptr) { return nullptr; }
        else { return x->key; }
    }

    Key_type select(std::size_t k)
    {
        if (k < 0 || k >= size()) { throw std::invalid_argument{""}; }
        auto x = _select(_root, k);
        return x->key;
    }

    inline std::size_t rank(Key_type key) const noexcept { return _rank(key, _root); }

    std::vector<Key_type> keys()
    {
        if (empty()) { return {}; }
        return keys(min(), max());
    }

    std::vector<Key_type> keys(Key_type lo, Key_type hi)
    {
        std::vector<Key_type> v;
        _keys(_root, v, lo, hi);
        return v;
    }

    std::size_t size(Key_type lo, Key_type hi)
    {
        if (_comp(hi, lo)) { return 0; }
        if (contains(hi)) { return rank(hi) - rank(lo) + 1; }
        else { return rank(hi) - rank(lo); }
    }

private:
    bool _is_red(Raw_node_pointer x)
    {
        if (x == nullptr) { return false; }
        return x->color == Color::red;
    }

    std::size_t _size(Raw_node_pointer x) const
    {
        if (x == nullptr) { return 0; }
        return x->size;
    }

    Value_type _get(Raw_node_pointer x, Key_type key) const
    {
        while (x != nullptr) {
            if (_comp(key, x->key)) { x = x->left; }
            else if (_comp(x->key, key)) { x = x->right; }
            else { return x->val; }
        }
        return nullptr;
    }

    Raw_node_pointer _put(Raw_node_pointer h, Key_type key, Value_type val)
    {
        if (h == nullptr) { return new Node(key, val, Color::red, 1); }

        if (_comp(key, h->key)) { h->left = _put(h->left, key, val); }
        else if (_comp(h->key, key)) { h->right = _put(h->right, key, val); }
        else { h->val = val; }

        if (_is_red(h->right) && !_is_red(h->left)) { h = _rotate_left(h); }
        if (_is_red(h->left) && _is_red(h->left->left)) { h = _rotate_right(h); }
        if (_is_red(h->left) && _is_red(h->right)) { _flip_colors(h); }
        h->size = _size(h->left) + _size(h->right) + 1;

        return h;
    }

    Raw_node_pointer _delete_min(Raw_node_pointer h)
    {
        if (h->left == nullptr) { return nullptr; }
        if (!_is_red(h->left) && !_is_red(h->left->left)) { h = _move_red_left(h); }
        h->left = _delete_min(h->left);
        return _balance(h);
    }

    Raw_node_pointer _delete_max(Raw_node_pointer h)
    {
        if (_is_red(h->left)) { h = _rotate_right(h); }
        if (h->right == nullptr) { return nullptr; }
        if (!_is_red(h->right) && !_is_red(h->right->left)) { h = _move_red_right(h); }
        h->right = _delete_max(h->right);
        return _balance(h);
    }

    Raw_node_pointer _remove(Raw_node_pointer h, Key_type key)
    {
        if (_comp(key, h->key) < 0) {
            if (!_is_red(h->left) && !_is_red(h->left->left)) { h = _move_red_left(h); }
            h->left = _remove(h->left, key);
        } else {
            if (_is_red(h->left)) { h = _rotate_right(h); }
            if (key == h->key && (h->right == nullptr)) { return nullptr; }
            if (!_is_red(h->right) && !_is_red(h->right->left)) { h = _move_red_right(h); }
            if (key == h->key) {
                auto x = _min(h->right);
                h->key = x->key;
                h->val = x->val;
                h->right = _delete_min(h->right);
            } else { h->right = _remove(h->right, key); }
        }
        return _balance(h);
    }

    Raw_node_pointer _rotate_right(Raw_node_pointer h)
    {
        auto x = h->left;
        h->left = x->right;
        x->right = h;
        x->color = x->right->color;
        x->right->color = Color::red;
        x->size = h->size;
        h->size = _size(h->left) + _size(h->right) + 1;
        return x;
    }

    Raw_node_pointer _rotate_left(Raw_node_pointer h)
    {
        auto x = h->right;
        h->right = x->left;
        x->left = h;
        x->color = x->left->color;
        x->left->color = Color::red;
        x->size = h->size;
        h->size = _size(h->left) + _size(h->right) + 1;
        return x;
    }

    void _flip_colors(Raw_node_pointer h)
    {
        h->color = !h->color;
        h->left->color = !h->left->color;
        h->right->color = !h->right->color;
    }

    Raw_node_pointer _move_red_left(Raw_node_pointer h)
    {
        _flip_colors(h);
        if (_is_red(h->right->left)) {
            h->right = _rotate_right(h->right);
            h = _rotate_left(h);
            _flip_colors(h);
        }
        return h;
    }

    Raw_node_pointer _move_red_right(Raw_node_pointer h)
    {
        _flip_colors(h);
        if (_is_red(h->left->left)) {
            h = _rotate_right(h);
            _flip_colors(h);
        }
        return h;
    }

    Raw_node_pointer _balance(Raw_node_pointer h)
    {
        if (_is_red(h->right)) { h = _rotate_left(h); }
        if (_is_red(h->left) && _is_red(h->left->left)) { h = _rotate_right(h); }
        if (_is_red(h->left) && _is_red(h->right)) { _flip_colors(h); }
        h->size = _size(h->left) + _size(h->right) + 1;
        return h;
    }

    int _height(Raw_node_pointer x) const noexcept
    {
        if (x == nullptr) { return -1; }
        return 1 + std::max(_height(x->left), _height(x->right));
    }

    Raw_node_pointer _min(Raw_node_pointer x)
    {
        if (x->left == nullptr) { return x; }
        else { return _min(x->left); }
    }

    Raw_node_pointer _max(Raw_node_pointer x)
    {
        if (x->right == nullptr) { return x; }
        else { return _max(x->right); }
    }

    Raw_node_pointer _floor(Raw_node_pointer x, Key_type key)
    {
        if (x == nullptr) { return nullptr; }
        if (key == x->key) { return x; }
        if (_comp(key, x->key)) { return _floor(x->left, key); }
        auto t = _floor(x->right, key);
        if (t != nullptr) { return t; }
        else { return x; }
    }

    Raw_node_pointer _ceiling(Raw_node_pointer x, Key_type key)
    {
        if (x == nullptr) { return nullptr; }
        if (key == x->key) { return x; }
        if (_comp(x->key, key)) { return _ceiling(x->right, key); }
        auto t = _ceiling(x->left, key);
        if (t != nullptr) { return t; }
        else { return x; }
    }

    Raw_node_pointer _select(Raw_node_pointer x, std::size_t k)
    {
        auto t = _size(x->left);
        if (t > k) { return _select(x->left, k); }
        else if (t < k) { return _select(x->right, k - t - 1); }
        else { return x; }
    }

    std::size_t _rank(Key_type key, Raw_node_pointer x) const noexcept
    {
        if (x == nullptr) { return 0; }
        if (_comp(key, x->key)) { return _rank(key, x->left); }
        else if (_comp(x->key, key)) { return 1 + _size(x->left) + _rank(key, x->right); }
        else { return _size(x->left); }
    }

    void _keys(Raw_node_pointer x, std::vector<Key_type> key_vector, Key_type lo, Key_type hi)
    {
        if (x == nullptr) { return; }
        if (_comp(lo, x->key)) { _keys(x->left, key_vector, lo, hi); }
        if ((_comp(lo, x->key) || lo == x->key) && (_comp(x->key, hi) || hi == x->key)) { key_vector.push_back(x->key); }
        if (_comp(x->key, hi)) { _keys(x->right, key_vector, lo, hi); }
    }

    bool _is_bst() { return _is_bst(_root, nullptr, nullptr); }

    bool _is_bst(Raw_node_pointer x, Key_type min, Key_type max)
    {
        if (x == nullptr) { return true; }
        if (min != nullptr && (_comp(x->key, min) || x->key == min)) { return false; }
        if (max != nullptr && (_comp(max, x->key) || x->key == max)) { return false; }
        return _is_bst(x->left, min, x->key) && _is_bst(x->right, x->key, max);
    }

    bool _is_23() { return _is_23(_root); }

    bool _is_23(Raw_node_pointer x)
    {
        if (x == nullptr) { return true; }
        if (_is_red(x->right)) { return false; }
        if (x != _root && _is_red(x) && _is_red(x->left)) { return false; }
        return _is_23(x->left) && _is_23(x->right);
    }

    bool _is_balanced()
    {
        auto black = 0;
        auto x = _root;
        while (x != nullptr) {
            if (!_is_red(x)) { ++black; }
            x = x->left;
        }
        return _is_balanced(_root, black);
    }

    bool _is_balanced(Raw_node_pointer x, int black)
    {
        if (x == nullptr) { return black == 0; }
        if (!_is_red(x)) { --black; }
        return _is_balanced(x->left, black) && _is_balanced(x->right, black);
    }

};

#endif // TOOLS_TO_REMEMBER_RED_BLACK_BST_H
