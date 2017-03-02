#include <string>
#include <iostream>
#include <vector>

void perm1(std::string s) { perm1("", s); }

void perm1(std::string prefix, std::string s)
{
    auto n = s.size();
    if (n == 0) {
        std::cout << prefix << "\n";
    } else {
        for (std::size_t i = 0; i < n; ++i) {
            perm1(prefix + s[i], s.substr(0, i) + s.substr(i + 1, n));
        }
    }

}

// print n! permutation of the elements of array a (not in order)
void perm2(std::string s)
{
    auto n = s.size();
    std::vector<char> a(n);
    for (auto i = 0; i < n; ++i) { a[i] = s[i]; }
    perm2(a, n);
}

void perm2(std::vector<char>& a, std::size_t n)
{
    if (n == 1) {
        for (auto c : a) { std::cout << c; }
        std::cout << "\n";
        return;
    }
    for (auto i = 0; i < n; ++i) {
        std::swap(a[i], a[n - 1]);
        perm2(a, n - 1);
        std::swap(a[i], a[n - 1]);
    }
}

template<typename Item_type, typename Visitor_type>
void heap_r(std::vector<Item_type>& v, int n, Visitor_type& visit)
{
    // or if (test(n)) { return; }
    if (n == 1) {
        visit(v);
        return;
    }
    int k;
    for (auto c = 1; c <= n; ++c) {
        heap_r(v, n - 1, visit);
        k = n % 2 ? 1 : c;
        std::swap(k, n);
    }
}