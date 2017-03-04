#ifndef TOOLS_TO_REMEMBER_FORD_FULKERSON_H
#define TOOLS_TO_REMEMBER_FORD_FULKERSON_H

class Ford_fulkerson {
private static final double FLOATING_POINT_EPSILON = 1E-11;

private boolean[] marked;     // marked[v] = true iff s->v path in residual graph
private FlowEdge[] edgeTo;    // edgeTo[v] = last edge on shortest residual s->v path
private double value;         // current value of max flow

    /**
     * Compute a maximum flow and minimum cut in the network <tt>G</tt>
     * from vertex <tt>s</tt> to vertex <tt>t</tt>.
     *
     * @param G the flow network
     * @param s the source vertex
     * @param t the sink vertex
     * @throws IndexOutOfBoundsException unless 0 <= s < V
     * @throws IndexOutOfBoundsException unless 0 <= t < V
     * @throws IllegalArgumentException  if s = t
     * @throws IllegalArgumentException  if initial flow is infeasible
     */
public FordFulkerson(FlowNetwork G, int s, int t) {
        validate(s, G.V());
        validate(t, G.V());
        if (s == t) throw new IllegalArgumentException("Source equals sink");
        if (!isFeasible(G, s, t)) throw new IllegalArgumentException("Initial flow is infeasible");

        // while there exists an augmenting path, use it
        value = excess(G, t);
        while (hasAugmentingPath(G, s, t)) {

            // compute bottleneck capacity
            double bottle = Double.POSITIVE_INFINITY;
            for (int v = t; v != s; v = edgeTo[v].other(v)) {
                bottle = Math.min(bottle, edgeTo[v].residualCapacityTo(v));
            }

            // augment flow
            for (int v = t; v != s; v = edgeTo[v].other(v)) {
                edgeTo[v].addResidualFlowTo(v, bottle);
            }

            value += bottle;
        }

        // check optimality conditions
        assert check(G, s, t);
    }

    /**
     * Returns the value of the maximum flow.
     *
     * @return the value of the maximum flow
     */
public double value() {
        return value;
    }

    /**
     * Returns true if the specified vertex is on the <tt>s</tt> side of the mincut.
     *
     * @return <tt>true</tt> if vertex <tt>v</tt> is on the <tt>s</tt> side of the micut;
     * <tt>false</tt> otherwise
     * @throws IndexOutOfBoundsException unless 0 <= v < V
     */
public boolean inCut(int v) {
        validate(v, marked.length);
        return marked[v];
    }

    // throw an exception if v is outside prescibed range
private void validate(int v, int V) {
        if (v < 0 || v >= V)
            throw new IndexOutOfBoundsException("vertex " + v + " is not between 0 and " + (V - 1));
    }


    // is there an augmenting path?
    // if so, upon termination edgeTo[] will contain a parent-link representation of such a path
    // this implementation finds a shortest augmenting path (fewest number of edges),
    // which performs well both in theory and in practice
private boolean hasAugmentingPath(FlowNetwork G, int s, int t) {
        edgeTo = new FlowEdge[G.V()];
        marked = new boolean[G.V()];

        // breadth-first search
        Queue<Integer> queue = new Queue<Integer>();
        queue.enqueue(s);
        marked[s] = true;
        while (!queue.isEmpty() && !marked[t]) {
            int v = queue.dequeue();

            for (FlowEdge e : G.adj(v)) {
                int w = e.other(v);

                // if residual capacity from v to w
                if (e.residualCapacityTo(w) > 0) {
                    if (!marked[w]) {
                        edgeTo[w] = e;
                        marked[w] = true;
                        queue.enqueue(w);
                    }
                }
            }
        }

        // is there an augmenting path?
        return marked[t];
    }


    // return excess flow at vertex v
private double excess(FlowNetwork G, int v) {
        double excess = 0.0;
        for (FlowEdge e : G.adj(v)) {
            if (v == e.from()) excess -= e.flow();
            else excess += e.flow();
        }
        return excess;
    }
};

#endif // TOOLS_TO_REMEMBER_FORD_FULKERSON_H
