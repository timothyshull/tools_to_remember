# Graphs
## Paths
### Depth first paths
- marked
- edge_to (parent)
- source
- dfs (recursive)
    - from source only
    - set marked
    - set parent after checking marked
    - dfs
- path_to
    - check marked
    - traverse edge_to from passed vertex to source, pushing to output vector

### Breadth first paths
- marked
- edge_to (parent)
- distance to (initialized with max val)
- bfs
    - from source only
    - set marked for source
    - distance to from source = 0
    - in for each loop
        - check marked
        - set parent
        - set distance to = distance to of parent + 1
        - set marked
- path_to
    - check marked
    - traverse edge_to from passed vertex to source, pushing to output vector
