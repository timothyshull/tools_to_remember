#include "Depth_first_search.h"

// Don't forget to initialize count to 0 here
Depth_first_search::Depth_first_search(Graph& graph, int s)
        : _visited(graph.num_vertices()),
          _count{0} { _dfs(graph, s); }

void Depth_first_search::_dfs(Graph& graph, int v)
{
    _visited[v] = true;
    ++_count;
    for (auto w : graph.adjacent(v)) {
        if (!_visited[w]) { _dfs(graph, w); }
    }
}
