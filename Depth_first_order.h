#ifndef DEPTH_FIRST_ORDER_H
#define DEPTH_FIRST_ORDER_H

#include <deque>

#include "Digraph.h"

class Depth_first_order {
private:
    std::deque<bool> _marked;
    std::vector<int> _pre_num;
    std::vector<int> _post_num;
    std::deque<int> _preorder; // queue
    std::deque<int> _postorder; // queue
    int _pre_count;
    int _post_count;

public:
    Depth_first_order(const Digraph& digraph);

    inline int pre(int v) const { return _pre_num[v]; }

    inline int post(int v) const { return _post_num[v]; }

    inline std::vector<int> post() const { return {_postorder.begin(), _postorder.end()}; }

    inline std::vector<int> pre() const { return {_preorder.begin(), _preorder.end()}; }

    inline std::vector<int> reverse_post() const { return {_postorder.rbegin(), _postorder.rend()}; }

private:
    void _dfs(const Digraph& digraph, int v);
};

#endif // DEPTH_FIRST_ORDER_H
