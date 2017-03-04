#include <cstddef>
#include <iostream>
#include <vector>
#include <iomanip>

template<typename Integer_type>
struct Test_visitor {
    std::vector<std::vector<Integer_type>> partitions;

    void operator()(std::vector<Integer_type>& a, std::size_t size)
    {
        std::vector<Integer_type> p(size - 1);
        // a[0] == 0
        for (auto i = 1; i < size; ++i) {
            p[i - 1] = a[i];
        }
        partitions.emplace_back(p);
    }

    void show_partitions()
    {
        for (auto p : partitions) {
            for (auto i = 0; i < p.size(); ++i) {
                std::cout << p[i];
                if (i < p.size() - 1) { std::cout << " + "; }
            }
            std::cout << "\n";
        }
    }
};

// Knuth partitions - Algorithm P, V4
template<typename Integer_type, typename Visitor_type>
void partitions(Integer_type t, std::vector<Integer_type>& a, Visitor_type& visit)
{
    a.clear();
    a.assign(static_cast<typename std::vector<Integer_type>::size_type>(t), 0);
    auto n = t - 1;
    if (n == 0) {
        visit(a, t); // visit empty partition
        return;
    }
    //P1
    a[0] = 0;
    auto m = 1;
    while (true) { //P2
        a[m] = n;
        auto q = m - (n == 1);
        while (true) { //P3
            visit(a, m + 1);
            if (a[q] == 2) { //P4
                a[q] = 1;
                q -= 1;
                m += 1;
                a[m] = 1;
                continue; // goto P3
            } else { //P5
                if (q == 0) { return; }
                auto x = a[q] - 1;
                a[q] = x;
                for (n = m - q + 1, m = q + 1; x < n; m += 1, n -= x) { a[m] = x; } // P6
                break; // goto P2
            }
        }
    }
}


template<typename Item_type>
class Partition_gen {
public:
    std::size_t _count;
    std::size_t _num_vals;
    std::size_t _level;

    std::vector<Item_type> _part_vals;
    std::vector<Item_type> _part_mults;
    std::vector<Item_type> _remainder;
    Item_type _pm_i;
    Item_type _rmdr_i;
    Item_type _part_tgt;

public:
    explicit Partition_gen(Item_type x, Item_type n = 0, const std::vector<Item_type>& pv = {})
            : _count{0},
              _num_vals{static_cast<std::size_t>(n ? n : x)},
              _level{_num_vals - 1},
              _part_vals(_num_vals + 1),
              _part_mults(_num_vals + 1),
              _remainder(_num_vals + 1),
              _pm_i{0},
              _rmdr_i{x},
              _part_tgt{x}
    {
        if (!pv.empty()) { for (auto j = 0; j < _num_vals; ++j) { _part_vals[j] = pv[j]; }}
        else { for (auto j = 0; j < _num_vals; ++j) { _part_vals[j] = j + 1; }}

        for (auto k = 0; k < _num_vals; ++k) { _part_mults[k] = 0; }
        for (auto k = 0; k < _num_vals; ++k) { _remainder[k] = 0; }

        _remainder[_num_vals - 1] = _part_tgt;
        _remainder[_num_vals] = _part_tgt;
    }

    ~Partition_gen() = default;

    Partition_gen(const Partition_gen&) = delete;

    Partition_gen& operator=(const Partition_gen&) = delete;

    std::size_t next()
    {
        if (_level >= _num_vals) { return _num_vals; }
        _remainder[_level] = _rmdr_i;
        _part_mults[_level] = _pm_i;
        _level = next_func(_level);

        for (auto j = 0; j < _level; ++j) { _part_mults[j] = _remainder[j] = 0; }
        ++_level;
        _rmdr_i = _remainder[_level] - _part_vals[_level];
        _pm_i = _part_mults[_level] + 1;

        return _level - 1;
    }

    std::size_t next_func(std::size_t i)
    {
        while (true) {
            while (i != 0 && 0 < _remainder[i]) {
                _part_mults[i - 1] = 0;
                _remainder[i - 1] = _remainder[i];
                --i;
            }

            if (i == 0) {
                if (_remainder[i] != 0) {
                    auto d = _remainder[i] / _part_vals[i];
                    _remainder[i] -= d * _part_vals[i];
                    _part_mults[i] = d;
                }
            }

            if (_remainder[i] == 0) {
                ++_count;
                return i;
            }

            ++i;
            if (i >= _num_vals) { return _num_vals; }
            _remainder[i] -= _part_vals[i];
            ++_part_mults[i];
        }
    }

    void print() const
    {
        bool fq = true;
        for (auto k = 0; k < _part_tgt; ++k) {
            auto c = _part_mults[k];
            auto v = _part_vals[k];
            for (auto j = 0; j < c; ++j) {
                if (fq) { fq = false; }
                else { std::cout << " +"; }
                std::cout << std::setw(2) << v;
            }
        }
        std::cout << "\n";
    }
};

int main()
{
    std::vector<unsigned> a(10);
    Test_visitor<unsigned> v;
    partitions<unsigned, Test_visitor<unsigned>>(10, a, v);
    v.show_partitions();
    return 0;
}