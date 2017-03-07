#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <cassert>
#include <iostream>
#include <list>
#include <unordered_map>
#include <utility>
#include <vector>
#include <deque>

template<std::size_t capacity>
class Lru_cache {
public:
    std::pair<bool, int> lookup(int key)
    {
        auto it = _table.find(key);
        if (it == _table.end()) { return {false, std::numeric_limits<int>::min()}; }
        _move_to_front(key, it);
        return {true, it->second.second};
    }

    void insert(int key, int val)
    {
        auto it = _table.find(key);
        if (it != _table.end()) {
            _move_to_front(key, it);
        } else {
            if (_table.size() == capacity) {
                _table.erase(_lru_queue.back());
                _lru_queue.pop_back();
            }
            _lru_queue.emplace_front(key);
            _table[key] = {_lru_queue.begin(), val};
        }
    }

    bool erase(int key)
    {
        auto it = _table.find(key);
        if (it == _table.end()) { return false; }
        _lru_queue.erase(it->second.first);
        _table.erase(it);
        return true;
    }

private:
    using Table_type = std::unordered_map<int, std::pair<std::deque<int>::iterator, int>>;
    using Table_iterator = typename Table_type::iterator;

    void _move_to_front(int key, const Table_iterator& it)
    {
        _lru_queue.erase(it->second.first);
        _lru_queue.emplace_front(key);
        it->second.first = _lru_queue.begin();
    }

    Table_type _table;
    std::deque<int> _lru_queue;
};

#endif // LRU_CACHE_H
