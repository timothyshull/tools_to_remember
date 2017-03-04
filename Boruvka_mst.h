#ifndef TOOLS_TO_REMEMBER_BORUVKA_MST_H
#define TOOLS_TO_REMEMBER_BORUVKA_MST_H

class Boruvka_mst {
private static final double FLOATING_POINT_EPSILON = 1E-12;

private Bag<Edge> mst = new Bag<Edge>();
private double weight;

public:
    Boruvka_mst(const EdgeWeightedGraph& G) {
        UF uf = new UF(G.V());

        // repeat at most log V times or until we have V-1 edges
        for (int t = 1; t < G.V() && mst.size() < G.V() - 1; t = t + t) {

            // foreach tree in forest, find closest edge
            // if edge weights are equal, ties are broken in favor of first edge in G.edges()
            Edge[] closest = new Edge[G.V()];
            for (Edge e : G.edges()) {
                int v = e.either(), w = e.other(v);
                int i = uf.find(v), j = uf.find(w);
                if (i == j) continue;   // same tree
                if (closest[i] == null || less(e, closest[i])) closest[i] = e;
                if (closest[j] == null || less(e, closest[j])) closest[j] = e;
            }

            // add newly discovered edges to MST
            for (int i = 0; i < G.V(); i++) {
                Edge e = closest[i];
                if (e != null) {
                    int v = e.either(), w = e.other(v);
                    // don't add the same edge twice
                    if (!uf.connected(v, w)) {
                        mst.add(e);
                        weight += e.weight();
                        uf.union(v, w);
                    }
                }
            }
        }

        // check optimality conditions
        assert check(G);
    }

Iterable<Edge> edges() {
        return mst;
    }


double weight() {
        return weight;
    }

private:
    static boolean less(Edge e, Edge f) {
        return e.weight() < f.weight();
    }
};

#endif // TOOLS_TO_REMEMBER_BORUVKA_MST_H
