#ifndef TOOLS_TO_REMEMBER_INDEX_MIN_PQ_H
#define TOOLS_TO_REMEMBER_INDEX_MIN_PQ_H

#include <stdexcept>
#include <limits>
#include <vector>
#include <functional>

template<typename Key_type, typename Comparator_type = std::less<Key_type>>
class Index_min_pq {
private:
    std::size_t _n{0};
    std::vector<std::size_t> _pq;
    std::vector<std::size_t> _qp;
    std::vector<Key_type> _keys;
    Comparator_type _comp;

public:
    explicit Index_min_pq(std::size_t max)
            : _keys(max + 1),
              _pq(max + 1),
              _qp(max + 1, std::numeric_limits<std::size_t>::max()),
              _comp{} {}

    Index_min_pq() = default;

    Index_min_pq(const Index_min_pq&) = default;

    Index_min_pq(Index_min_pq&&) = default;

    ~Index_min_pq() = default;

    Index_min_pq& operator=(const Index_min_pq&) = default;

    Index_min_pq& operator=(Index_min_pq&&) = default;

    inline bool empty() const noexcept { return _n == 0; }

    inline std::size_t size() const noexcept { return _n; }

    inline bool contains(std::size_t i) const { return _qp[i] != -1; }

    void insert(std::size_t i, Key_type& key)
    {
        ++_n;
        _qp[i] = _n;
        _pq[_n] = i;
        _keys[i] = key;
        _swim(_n);
    }

    void insert(std::size_t i, Key_type&& key)
    {
        ++_n;
        _qp[i] = _n;
        _pq[_n] = i;
        _keys[i] = key;
        _swim(_n);
    }

    inline Key_type min() const { return _keys[_pq[1]]; }

    std::size_t pop()
    {
        auto i = _pq[1];
        _swap(1, _n--);
        _sink(1);
        // keys[pq[n + 1]] = nullptr;
        _qp[_pq[_n + 1]] = std::numeric_limits<std::size_t>::max();
        return i;
    }

    // used in Dijkstra
    std::size_t delete_min()
    {
        if (_n == 0) { throw std::out_of_range{"Priority queue underflow"}; }
        auto min = _pq[1];
        _swap(1, _n--);
        _sink(1);
        _qp[min] = std::numeric_limits<std::size_t>::max();
        // keys[min] = null;
        _pq[_n + 1] = std::numeric_limits<std::size_t>::max();
        return min;
    }

    // used in Dijkstra
    void decrease_key(std::size_t i, Key_type key)
    {
        if (!contains(i)) { throw std::out_of_range{"index is not in the priority queue"}; }
        if (_comp(_keys[i], key) || _keys[i] == key) {
            throw std::invalid_argument{"Calling decreaseKey() with given argument would not strictly decrease the key"};
        }
        _keys[i] = key;
        _swim(_qp[i]);
    }

private:
    void _swap(std::size_t i, std::size_t j)
    {
        auto t = _pq[i];
        _pq[i] = _pq[j];
        _pq[j] = t;
        _qp[_pq[i]] = i;
        _qp[_pq[j]] = j;
    }

    void _swim(std::size_t k)
    {
        while (k > 1 && _comp(k / 2, k)) {
            _swap(k, k / 2);
            k = k / 2;
        }
    }

    void _sink(std::size_t k)
    {
        while (2 * k <= _n) {
            auto j = 2 * k;
            if (j < _n && _comp(j, j + 1)) { ++j; }
            if (!_comp(k, j)) { break; }
            _swap(k, j);
            k = j;
        }
    }
};

#endif // TOOLS_TO_REMEMBER_INDEX_MIN_PQ_H
