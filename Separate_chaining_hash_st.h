#ifndef TOOLS_TO_REMEMBER_SEPARATE_CHAINING_HASH_ST_H
#define TOOLS_TO_REMEMBER_SEPARATE_CHAINING_HASH_ST_H

#include <functional>
#include <vector>

#include "Sequential_search_st.h"

template<typename Key_type, typename Value_type, typename Hasher_type = std::hash<Key_type>>
class Separate_chaining_hash_st {
private:
    std::size_t m;
    std::vector<Sequential_search_st<Key_type, Value_type>> st;
    Hasher_type hasher;
public:
    Separate_chaining_hash_st() : Separate_chaining_hash_st{997} {}

    explicit Separate_chaining_hash_st(std::size_t m)
            : m{m},
              st(m, Sequential_search_st<Key_type, Value_type>{}),
              hasher{} {}

    inline Value_type get(Key_type key) const { return st[hash(key)].get(key); }

    inline void put(Key_type key, Value_type value) { st[hash(key)].put(key, value); }

private:
    inline std::size_t hash(Key_type key) const noexcept { return (hasher(key) & 0x7FFFFFFF) % m; }
};

#endif // TOOLS_TO_REMEMBER_SEPARATE_CHAINING_HASH_ST_H
