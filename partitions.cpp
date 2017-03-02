#include <cstddef>
#include <iostream>
#include <vector>

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

int main()
{
    std::vector<unsigned> a(10);
    Test_visitor<unsigned> v;
    partitions<unsigned, Test_visitor<unsigned>>(10, a, v);
    v.show_partitions();
    return 0;
}