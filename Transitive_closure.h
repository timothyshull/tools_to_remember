#ifndef TOOLS_TO_REMEMBER_TRANSITIVE_CLOSURE_H
#define TOOLS_TO_REMEMBER_TRANSITIVE_CLOSURE_H

#include "Directed_dfs.h"

class Transitive_closure {
private:
    std::vector<Directed_dfs> _tc;

public:
    Transitive_closure(const Digraph& digraph);

    inline bool reachable(int v, int w) const { return _tc[v].marked(w); }
};

#endif // TOOLS_TO_REMEMBER_TRANSITIVE_CLOSURE_H
