#ifndef TRANSITIVE_CLOSURE_H
#define TRANSITIVE_CLOSURE_H

#include "Directed_dfs.h"

class Transitive_closure {
private:
    std::vector<Directed_dfs> _tc;

public:
    Transitive_closure(const Digraph& digraph);

    inline bool reachable(int v, int w) const { return _tc[v].marked(w); }
};

#endif // TRANSITIVE_CLOSURE_H
