#ifndef LINEAR_PROBING_HASH_ST_H
#define LINEAR_PROBING_HASH_ST_H

#include <functional>
#include <vector>

// NOTE: linear probing is a form of open-addressing, as is double hashing

template<typename Key_type, typename Value_type, typename Hasher_type = std::hash<Key_type>>
class Linear_probing_hash_st {
private:
    std::size_t _n;
    std::size_t _buckets{16};
    std::vector<Key_type*> _keys;
    std::vector<Value_type> _values;
    Hasher_type _hasher;

public:
    Linear_probing_hash_st()
            : _keys(_buckets, nullptr),
              _values(_buckets),
              _n{0},
              _hasher{} {}

    explicit Linear_probing_hash_st(std::size_t cap)
            : _keys(cap, nullptr),
              _values(cap),
              _buckets{cap},
              _n{0},
              _hasher{} {}

//    Linear_probing_hash_st(const Linear_probing_hash_st& rhs) : Linear_probing_hash_st{rhs._buckets}
//    {
//        for (auto i = 0; i < _buckets; ++i) {
//            if (rhs._keys[i] != nullptr) {
//                Key_type t{new Key_type{*rhs._keys[i]}};
//                this->put(_keys[t], _values[i]);
//            }
//        }
//    }
//
//    Linear_probing_hash_st(Linear_probing_hash_st&& rhs)
//            : _n{rhs._n},
//              _buckets{rhs._buckets},
//              _keys{std::move(rhs._keys)},
//              _values{std::move(rhs._values)},
//              _hasher{rhs._hasher}
//    {
//        rhs._n = 0;
//        rhs._buckets = 0;
//    }

    ~Linear_probing_hash_st() {
        for (auto i = 0; i < _keys.size(); ++i) {
            auto t = _keys[i];
            if (t != nullptr) {
                delete t;
                _keys[i] = nullptr;
            }
        }
    }

    void put(Key_type key, Value_type val)
    {
        // double table size if 50% full
        if (_n >= _buckets / 2) { _resize(2 * _buckets); }

        std::size_t i;
        for (i = _hash(key); _keys[i] != nullptr; i = (i + 1) % _buckets) {
            if (*_keys[i] == key) {
                _values[i] = val;
                return;
            }
        }
        _keys[i] = new Key_type{key};
        _values[i] = val;
        ++_n;
    }

    Value_type get(Key_type key)
    {
        for (auto i = _hash(key); _keys[i] != nullptr; i = (i + 1) % _buckets) {
            if (*_keys[i] == key) {
                return _values[i];
            }
        }
        throw std::out_of_range{""};
    }

private:
    inline std::size_t _hash(Key_type key) const noexcept { return (_hasher(key) & 0x7FFFFFFF) % _buckets; }

    void _resize(std::size_t cap)
    {
        Linear_probing_hash_st<Key_type, Value_type, Hasher_type> t{cap};
        for (auto i = 0; i < _buckets; ++i) { if (_keys[i] != nullptr) { t.put(*_keys[i], _values[i]); }}
        _keys = t._keys;
        _values = t._values;
        _buckets = t._buckets;
        // NOTE: have to explicitly assign nullptr here to avoid dtor issue
        for (auto i = 0; i < t._keys.size(); ++i) { t._keys[i] = nullptr; }
    }
};

#endif // LINEAR_PROBING_HASH_ST_H
