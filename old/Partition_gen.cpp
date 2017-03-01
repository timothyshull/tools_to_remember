#include <vector>
#include <iostream>
#include <iomanip>

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

// See the partition-gen-demo in fxt
int main()
{
    Partition_gen<int> t{10, 0, {2, 3, 4}};

    while (t.next() < 10) {
        t.print();
    }
    std::cout << "here";
    return 0;
}

//1 + 1 + 1 + 1 + 1
//1 + 1 + 2 + 2
//1 + 1 + 1 + 3
//2 + 2 + 3
//1 + 3 + 3
//1 + 1 + 1 + 1 + 1 + 5
//1 + 1 + 2 + 2 + 5
//1 + 1 + 1 + 3 + 5