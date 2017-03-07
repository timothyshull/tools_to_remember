#ifndef SEPARATE_CHAINING_HASH_ST_H
#define SEPARATE_CHAINING_HASH_ST_H

#include <functional>
#include <vector>

#include "Sequential_search_st.h"

template<typename Key_type, typename Value_type, typename Hasher_type = std::hash<Key_type>>
class Separate_chaining_hash_st {
private:
    std::size_t _buckets;
    std::vector<Sequential_search_st<Key_type, Value_type>> _st;
    Hasher_type _hasher;
public:
    Separate_chaining_hash_st() : Separate_chaining_hash_st{997} {}

    explicit Separate_chaining_hash_st(std::size_t m)
            : _buckets{m},
              _st(m, Sequential_search_st<Key_type, Value_type>{}),
              _hasher{} {}

    ~Separate_chaining_hash_st() = default;

    inline Value_type get(Key_type key) const { return _st[_hash(key)].get(key); }

    inline void put(Key_type key, Value_type value) { _st[_hash(key)].put(key, value); }

private:
    inline std::size_t _hash(Key_type key) const noexcept { return (_hasher(key) & 0x7FFFFFFF) % _buckets; }
};

#endif // SEPARATE_CHAINING_HASH_ST_H
