- binary search - array and BST
- quicksort - X
- topological sort
- cycles
    - directed - X
    - undirected - X
- traversal
    - recursive
        - preorder - X
        - inorder - X
        - postorder - X
    - iterative
        - preorder - X
        - inorder - X
        - postorder - X
- level order tree printing - X


- general string ops - X
- general file ops - add tests



- divide-and-conquer
    - maximum subarray - X
    - matrix multiplication (not Strassen) - X
- permutations
- combinations
- partitions
- backtracking
    - n-Queens
    - traveling salesperson - Hamilton path
    - convex hull - Graham Scan
    - sudoku
- basic linear programming
    - shortest paths
    - maxflow
    - mincost flow
    - Simplex algorithm
- basic dynamic programming
    - rod cutting
    - longest common subsequence
    - knapsack
    - subset sum
    - coin change
- basic greedy programming
    - Huffman codes
- Horner's method - X

- cheatsheet
    - sort
        - selection - X
        - insertion - X
        - bubble - X
        - shellsort - X
        - mergesort - X
        - quicksort - X
        - heapsort - X
        - counting sort * - X
        - radix sort * -> TODO: 3-way radix quicksort
        - bucket sort * - X
    - priority queues
        - array - X
        - binary heap - X
        - TODO: consider more?
    - symbol tables
        - sequential search (unordered array) - X
        - binary search (binary search)
        - binary search tree
        - red-black BST
        - hash table (separate-chaining) - X
        - hash table (linear-probing) - X
     - graphs
        - path
        - cycle
        - directed cycle
        - bipartiteness/odd cycle
        - connected components
        - strong components
        - Eulerian cycle
        - directed Eulerian cycle
        - transitive closure
        - minimum spanning tree
            - Kruskal
            - Prim
            - Boruvka
        - shortest paths
            - unit - BFS paths
            - non-negative - Dijkstra
            - negative - Bellman-ford
        - all-pairs shortest paths - Floyd Warshall
        - maxflow-mincut - Ford-Fulkerson



ADD LATER:
- subset sum
- longest common subsequence
- Simplex algorithm


NOTE:
should modify usage of comparator and == to remove == and implement as !(comp(a, b) || comp(b, a))