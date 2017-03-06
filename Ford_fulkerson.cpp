#include "Ford_fulkerson.h"

Ford_fulkerson::Ford_fulkerson(const Flow_network& network, int s, int t)
{
    // validate vertices
    if (s == t) { throw std::invalid_argument{"Source equals sink"}; }
    if (!_is_feasible(network, s, t)) { throw std::invalid_argument{"Initial flow is infeasible"}; }

    _value = _excess(network, t);
    while (_has_augmenting_path(network, s, t)) {

        auto bottle = _inf;
        for (auto v = t; v != s; v = _edge_to[v].other(v)) {
            bottle = std::min(bottle, _edge_to[v].residual_capacity_to(v));
        }

        for (auto v = t; v != s; v = _edge_to[v].other(v)) {
            _edge_to[v].add_residual_flow_to(v, bottle);
        }

        _value += bottle;
    }

}

bool Ford_fulkerson::_has_augmenting_path(const Flow_network& network, int s, int t)
{
    _edge_to = std::vector<Flow_edge>(network.num_vertices());
    _marked = std::deque<bool>(network.num_vertices());

    // bfs
    std::deque<int> queue;
    queue.push_back(s);
    _marked[s] = true;
    while (!queue.empty() && !_marked[t]) {
        auto v = queue.front();
        queue.pop_front();

        for (auto& e : network.adjacent(v)) {
            auto w = e.other(v);

            if (e.residual_capacity_to(w) > 0) {
                if (!_marked[w]) {
                    _edge_to[w] = e;
                    _marked[w] = true;
                    queue.push_back(w);
                }
            }
        }
    }

    return _marked[t];
}

double Ford_fulkerson::_excess(const Flow_network& network, int v)
{
    auto excess = 0.0;
    for (auto& e : network.adjacent(v)) {
        if (v == e.from()) { excess -= e.flow(); }
        else { excess += e.flow(); }
    }
    return excess;
}

bool Ford_fulkerson::_is_feasible(const Flow_network& network, int s, int t)
{
    for (auto v = 0; v < network.num_vertices(); ++v) {
        for (auto& e : network.adjacent(v)) {
            if (e.flow() < -_epsilon || e.flow() > e.capacity() + _epsilon) {
                std::cerr << "Edge does not satisfy capacity constraints: " << e.from() << "-" << e.to();
                return false;
            }
        }
    }

    if (std::abs(_value + _excess(network, s)) > _epsilon) {
        std::cerr << "Excess at source = " << _excess(network, s);
        std::cerr << "Max flow         = " << value;
        return false;
    }
    if (std::abs(_value - _excess(network, t)) > _epsilon) {
        std::cerr << "Excess at sink   = " << _excess(network, t);
        std::cerr << "Max flow         = " << value;
        return false;
    }
    for (auto v = 0; v < network.num_vertices(); ++v) {
        if (v == s || v == t) { continue; }
        else if (std::abs(_excess(network, v)) > _epsilon) {
            std::cerr << "Net flow out of " << v << " doesn't equal zero";
            return false;
        }
    }
    return true;
}