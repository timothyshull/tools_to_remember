#include <vector>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

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
        swim(_n);
    }

    void insert(std::size_t i, Key_type&& key)
    {
        ++_n;
        _qp[i] = _n;
        _pq[_n] = i;
        _keys[i] = key;
        swim(_n);
    }

    inline Key_type min() const { return _keys[_pq[1]]; }

    std::size_t pop()
    {
        auto i = _pq[1];
        swap(1, _n--);
        sink(1);
        // keys[pq[n + 1]] = nullptr;
        _qp[_pq[_n + 1]] = std::numeric_limits<std::size_t>::max();
        return i;
    }

private:
    void swap(std::size_t i, std::size_t j)
    {
        auto t = _pq[i];
        _pq[i] = _pq[j];
        _pq[j] = t;
        _qp[_pq[i]] = i;
        _qp[_pq[j]] = j;
    }

    void swim(std::size_t k)
    {
        while (k > 1 && _comp(k / 2, k)) {
            swap(k, k / 2);
            k = k / 2;
        }
    }

    void sink(std::size_t k)
    {
        while (2 * k <= _n) {
            auto j = 2 * k;
            if (j < _n && _comp(j, j + 1)) { ++j; }
            if (!_comp(k, j)) { break; }
            swap(k, j);
            k = j;
        }
    }
};

TEST(index_min_pq, default_size)
{
    Index_min_pq<int> a;
    ASSERT_THAT(a.size(), Eq(0));
}

TEST(index_min_pq, test_10_max_empty)
{
    Index_min_pq<int> a{10};
    ASSERT_TRUE(a.empty());
}

TEST(index_min_pq, test_non_empty)
{
    Index_min_pq<int> a{1};
    a.insert(1, 1);
    ASSERT_FALSE(a.empty());
}

//TEST(index_min_pq, test_3_elems)
//{
//    Index_min_pq<int> a{3};
//    a.push(1);
//    a.push(2);
//    a.push(3);
//    ASSERT_THAT(a.pop(), Eq(3));
//}
//
//TEST(index_min_pq, test_10_max_3_size)
//{
//    Index_min_pq<int> a{10};
//    a.push(1);
//    a.push(2);
//    a.push(3);
//    ASSERT_THAT(a.size(), Eq(3));
//}
//
//TEST(index_min_pq, test_3_lvalue)
//{
//    Index_min_pq<int> a{10};
//    auto b = 1;
//    auto c = 2;
//    auto d = 3;
//    a.push(b);
//    a.push(c);
//    a.push(d);
//    ASSERT_THAT(a.pop(), Eq(3));
//}
//
//TEST(index_min_pq, test_3_then_empty)
//{
//    Index_min_pq<int> a{10};
//    a.push(1);
//    a.push(2);
//    a.push(3);
//    a.pop();
//    a.pop();
//    a.pop();
//    ASSERT_TRUE(a.empty());
//}
//
//TEST(index_min_pq, test_comparator)
//{
//    Index_min_pq<int, std::greater<int>> a{3};
//    a.push(3);
//    a.push(2);
//    a.push(1);
//    ASSERT_THAT(a.pop(), Eq(1));
//}
