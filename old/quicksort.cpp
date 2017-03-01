// ch 7 - ACPP
//template<class Item_type>
//int partition(std::vector<Item_type>& collection, int l_bound, int r_bound)
//{
//    int i{l_bound - 1};
//    int j{r_bound};
//
//    Item_type v{collection[r_bound]};
//    for (;;) {
//        while (collection[++i] < v) {}
//        while (v < collection[--j]) { if (j == l_bound) { break; }}
//        if (i >= j) { break; }
//        std::swap(collection[i], collection[j]);
//    }
//    std::swap(collection[i], collection[r_bound]);
//    return i;
//}

#include <vector>
#include <stack>

// from AJ -> similar in approach to the Dutch national flag problem
template<typename Item_type>
int partition(std::vector<Item_type>& collection, int l_bound, int r_bound)
{
    int i{l_bound};
    int j{r_bound + 1};

    Item_type v{collection[l_bound]};
    while (true) {
        while (collection[++i] < v) { if (i == r_bound) { break; }}
        while (v < collection[--j]) { if (j == l_bound) { break; }}
        if (i >= j) { break; }
        std::swap(collection[i], collection[j]);
    }
    std::swap(collection[l_bound], collection[j]);
    return j;
}

template<class Item_type>
void quicksort(std::vector<Item_type>& collection, int l_bound, int r_bound)
{
    if (r_bound <= l_bound) { return; }
    int i{partition(collection, l_bound, r_bound)};
    quicksort(collection, l_bound, i - 1);
    quicksort(collection, i + 1, r_bound);
}

template<class Item_type>
inline void quicksort(std::vector<Item_type>& collection) { quicksort(collection, 0, static_cast<int>(collection.size() - 1)); }

// -----

// -----
inline void push2(std::stack<int>& s, int a, int b)
{
    s.push(b);
    s.push(a);
}

template<class Item_type>
void quicksort_iterative(std::vector<Item_type>& collection, int l_bound, int r_bound)
{
    std::stack<int> s;
    push2(s, l_bound, r_bound);
    int i;
    while (!s.empty()) {
        l_bound = s.top();
        s.pop();
        r_bound = s.top();
        s.pop();

        if (r_bound <= l_bound) { continue; }
        i = partition(collection, l_bound, r_bound);
        if (i - l_bound > r_bound - i) {
            push2(s, l_bound, i - 1);
            push2(s, i + 1, r_bound);
        } else {
            push2(s, i + 1, r_bound);
            push2(s, l_bound, i - 1);
        }
    }
}

// sort utilities
// template<class Item>
//void exch(Item& A, Item& B) {
//    Item t = A;
//    A = B;
//    B = t;
//}

//template<class Item>
//void compexch(Item& A, Item& B) { if (B < A) { exch(A, B); }}

template<typename Item_type>
void comp_exch(std::vector<Item_type>& collection, int index_a, int index_b) { if (collection[index_b] < collection[index_a]) { std::swap(collection[index_a], collection[index_b]); }}

// ---- insertion
template<class Item_type>
void insertion_sort(std::vector<Item_type>& collection, int l_bound, int r_bound)
{
    int i;
    for (i = r_bound; i > l_bound; --i) {
        comp_exch(collection, i - 1, i);
    }

    int j;
    for (i = l_bound + 2; i <= r_bound; ++i) {
        j = i;
        Item_type v{collection[i]};
        while (v < collection[j - 1]) {
            collection[j] = collection[j - 1];
            --j;
        }
        collection[j] = v;
    }
}


// -----


template<class Item_type>
void quicksort_m3(std::vector<Item_type>& collection, int l_bound, int r_bound)
{
    static const int cutoff{10};
    if (r_bound - l_bound <= cutoff) { return; }
    std::swap(collection[(l_bound + r_bound) / 2], collection[r_bound - 1]);
    comp_exch(collection, l_bound, r_bound - 1);
    comp_exch(collection, l_bound, r_bound);
    comp_exch(collection, r_bound - 1, r_bound);

    int i{partition(collection, l_bound + 1, r_bound - 1)};
    quicksort_m3(collection, l_bound, i - 1);
    quicksort_m3(collection, i + 1, r_bound);
}

template<class Item_type>
void hybridsort(std::vector<Item_type>& collection, int l_bound, int r_bound)
{
    quicksort_m3(collection, l_bound, r_bound);
    insertion_sort(collection, l_bound, r_bound);
}

// -----
template<class Item_type>
void quicksort_3_way(std::vector<Item_type>& collection, int l_bound, int r_bound)
{
    int k;
    Item_type v{collection[r_bound]};
    if (r_bound <= l_bound) { return; }

    int i{l_bound - 1};
    int j{r_bound};
    int p{l_bound - 1};
    int q{r_bound};

    for (;;) {
        while (collection[++i] < v) {}
        while (v < collection[--j]) { if (j == l_bound) { break; }}
        if (i >= j) { break; }

        std::swap(collection[i], collection[j]);
        if (collection[i] == v) {
            ++p;
            std::swap(collection[p], collection[i]);
        }
        if (v == collection[j]) {
            --q;
            std::swap(collection[q], collection[j]);
        }
    }

    std::swap(collection[i], collection[r_bound]);

    j = i - 1;
    i = i + 1;
    for (k = l_bound; k <= p; ++k, --j) { std::swap(collection[k], collection[j]); }
    for (k = r_bound - 1; k >= q; --k, ++i) { std::swap(collection[k], collection[i]); }

    quicksort_3_way(collection, l_bound, j);
    quicksort_3_way(collection, i, r_bound);
}