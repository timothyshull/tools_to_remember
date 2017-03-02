#include <vector>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

// corresponds to MaxPQ
template<typename Key_type, typename Comparator_type = std::less<Key_type>>
class Priority_queue_a {
private:
    std::vector<Key_type> _pq;
    std::size_t _n{0};
    Comparator_type _comp;

public:
    explicit Priority_queue_a(std::size_t max)
            : _pq(max + 1),
              _comp{} {}

    Priority_queue_a() = default;

    Priority_queue_a(const Priority_queue_a&) = default;

    Priority_queue_a(Priority_queue_a&&) = default;

    ~Priority_queue_a() = default;

    Priority_queue_a& operator=(const Priority_queue_a&) = default;

    Priority_queue_a& operator=(Priority_queue_a&&) = default;

    inline bool empty() const noexcept { return _n == 0; }

    inline std::size_t size() const noexcept { return _n; }

    void push(Key_type& v)
    {
        _pq[++_n] = v;
        _swim(_n);
    }

    void push(Key_type&& v)
    {
        _pq[++_n] = v;
        _swim(_n);
    }

    Key_type pop()
    {
        auto t = _pq[1];
        std::swap(_pq[1], _pq[_n--]);
        // pq[n + 1] = nullptr;
        _sink(1);
        return t;
    }

private:
    void _sink(std::size_t k)
    {
        while (2 * k <= _n) {
            auto j = 2 * k;
            if (j < _n && _comp(_pq[j], _pq[j + 1])) { ++j; }
            if (_comp(_pq[k], _pq[j])) { break; }
            std::swap(_pq[k], _pq[j]);
            k = j;
        }
    }

    void _swim(std::size_t k)
    {
        while (k > 1 && _comp(_pq[k / 2], _pq[k])) {
            std::swap(_pq[k / 2], _pq[k]);
            k = k / 2;
        }
    }
};


// begin tests

TEST(priority_queue_array, default_size)
{
    Priority_queue_a<int> a;
    ASSERT_THAT(a.size(), Eq(0));
}

TEST(priority_queue_array, test_10_max_empty)
{
    Priority_queue_a<int> a{10};
    ASSERT_TRUE(a.empty());
}

TEST(priority_queue_array, test_non_empty)
{
    Priority_queue_a<int> a{1};
    a.push(1);
    ASSERT_FALSE(a.empty());
}

TEST(priority_queue_array, test_3_elems)
{
    Priority_queue_a<int> a{3};
    a.push(1);
    a.push(2);
    a.push(3);
    ASSERT_THAT(a.pop(), Eq(3));
}

TEST(priority_queue_array, test_10_max_3_size)
{
    Priority_queue_a<int> a{10};
    a.push(1);
    a.push(2);
    a.push(3);
    ASSERT_THAT(a.size(), Eq(3));
}

TEST(priority_queue_array, test_3_lvalue)
{
    Priority_queue_a<int> a{10};
    auto b = 1;
    auto c = 2;
    auto d = 3;
    a.push(b);
    a.push(c);
    a.push(d);
    ASSERT_THAT(a.pop(), Eq(3));
}

TEST(priority_queue_array, test_3_then_empty)
{
    Priority_queue_a<int> a{10};
    a.push(1);
    a.push(2);
    a.push(3);
    a.pop();
    a.pop();
    a.pop();
    ASSERT_TRUE(a.empty());
}

TEST(priority_queue_array, test_comparator)
{
    Priority_queue_a<int, std::greater<int>> a{3};
    a.push(3);
    a.push(2);
    a.push(1);
    ASSERT_THAT(a.pop(), Eq(1));
}

