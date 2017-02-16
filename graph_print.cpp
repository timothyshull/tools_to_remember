#include <iostream>

// graph print
template<typename Graph_type>
void graph_print(const Graph_type& graph)
{
    for (int s{0}; s < graph.num_vertices(); ++s) {
        std::cout.width(2);
        std::cout << s << ":";
        for (auto t : graph.adjacent(s)) {
            std::cout.width(2);
            std::cout << t << " ";
        }
        std::cout << "\n";
    }
}