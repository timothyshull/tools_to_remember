# 3-8
## Binary search
- _size in binary search tree should be 1 + _size(n->left) + _size(n->right)
- don't forget to add const to all called functions within a const function
- binary search loop is not while (true) -> while (l <= h)
- binary search hi is size - 1

## Quicksort
- in nested while loops can just use == rather than >= or <=
- entry call should use a.size() - 1
- partition should set j = hi + 1
- recursive calls s/b lo, j - 1 and j + 1, hi (think working around partition)
