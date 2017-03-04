#ifndef TOOLS_TO_REMEMBER_KRUSKAL_MST_H
#define TOOLS_TO_REMEMBER_KRUSKAL_MST_H

class Kruskal_mst {
private static final double FLOATING_POINT_EPSILON = 1E-12;

private double weight;                        // weight of MST
private Queue<Edge> mst = new Queue<Edge>();  // edges in MST

    /**
     * Compute a minimum spanning tree (or forest) of an edge-weighted graph.
     *
     * @param G the edge-weighted graph
     */
public KruskalMST(EdgeWeightedGraph G) {
        // more efficient to build heap by passing array of edges
        MinPQ<Edge> pq = new MinPQ<Edge>();
        for (Edge e : G.edges()) {
            pq.insert(e);
        }

        // run greedy algorithm
        UF uf = new UF(G.V());
        while (!pq.isEmpty() && mst.size() < G.V() - 1) {
            Edge e = pq.delMin();
            int v = e.either();
            int w = e.other(v);
            if (!uf.connected(v, w)) { // v-w does not create a cycle
                uf.union(v, w);  // merge v and w components
                mst.enqueue(e);  // add edge e to mst
                weight += e.weight();
            }
        }

        // check optimality conditions
        assert check(G);
    }

    /**
     * Returns the edges in a minimum spanning tree (or forest).
     *
     * @return the edges in a minimum spanning tree (or forest) as
     * an iterable of edges
     */
public Iterable<Edge> edges() {
        return mst;
    }

    /**
     * Returns the sum of the edge weights in a minimum spanning tree (or forest).
     *
     * @return the sum of the edge weights in a minimum spanning tree (or forest)
     */
public double weight() {
        return weight;
    }
};

#endif // TOOLS_TO_REMEMBER_KRUSKAL_MST_H
