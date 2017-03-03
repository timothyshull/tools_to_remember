#include <vector>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

template<
        typename Key_type,
        typename Value_type,
        typename Key_comparator = std::less<Key_type>
>
class Binary_search_st {
private:
    std::vector<Key_type> keys;
    std::vector<Value_type> vals;
    std::size_t n{0};
    Key_comparator comp;

public:
    explicit Binary_search_st(std::size_t max)
            : keys(max),
              vals(max),
              comp{} {}

    Binary_search_st() = default;

    Binary_search_st(const Binary_search_st&) = default;

    Binary_search_st(Binary_search_st&&) = default;

    ~Binary_search_st() = default;

    Binary_search_st& operator=(const Binary_search_st&) = default;

    Binary_search_st& operator=(Binary_search_st&&) = default;

    inline bool empty() const noexcept { return n == 0; }

    inline std::size_t size() const noexcept { return n; }

    Value_type get(Key_type& key)
    {
        if (empty()) { throw std::out_of_range{}; }
        auto i = rank(key);
        if (i < n && keys[i] == key) { return vals[i]; }
        else { throw std::out_of_range{""}; }
    }

    Value_type get(Key_type&& key)
    {
        if (empty()) { throw std::out_of_range{}; }
        auto i = rank(key);
        if (i < n && keys[i] == key) { return vals[i]; }
        else { throw std::out_of_range{""}; }
    }

    std::size_t rank(Key_type& key)
    {
        std::size_t lo{0};
        auto hi = n - 1;
        while (lo <= hi) {
            auto mid = lo + (hi - lo) / 2;
            int cmp = key.compareTo(keys[mid]);
            if (comp(key, keys[mid])) { hi = mid - 1; }
            else if (comp(keys[mid], key)) { lo = mid + 1; }
            else { return mid; }
        }
        return lo;
    }

    std::size_t rank(Key_type&& key)
    {
        std::size_t lo{0};
        auto hi = n - 1;
        while (lo <= hi) {
            auto mid = lo + (hi - lo) / 2;
            int cmp = key.compareTo(keys[mid]);
            if (comp(key, keys[mid])) { hi = mid - 1; }
            else if (comp(keys[mid], key)) { lo = mid + 1; }
            else { return mid; }
        }
        return lo;
    }

    void put(Key_type& key, Value_type& val)
    {
        auto i = rank(key);

        if (i < n && keys[i] == key) {
            vals[i] = val;
            return;
        }

        // if (n == keys.size()) { resize(2 * keys.size()); }
        if (n == keys.size()) { throw std::range_error{}; }

        for (auto j = n; j > i; --j) {
            keys[j] = keys[j - 1];
            vals[j] = vals[j - 1];
        }
        keys[i] = key;
        vals[i] = val;
        n++;

        // assert check();
    }
};