#include <vector>

struct Graph_vertex;

bool has_cycle(Graph_vertex&);

enum class Vertex_color { white, gray, black };

struct Graph_vertex {
    Vertex_color color = Vertex_color::white;
    std::vector<Graph_vertex*> edges;
};

bool is_deadlocked(const std::vector<Graph_vertex>& vertices)
{
    return std::any_of(
            vertices.begin(),
            vertices.end(),
            [](Graph_vertex& vertex) { return vertex.color == Vertex_color::white && has_cycle(vertex); });
}

bool has_cycle(Graph_vertex& cur)
{
    if (cur.color == Vertex_color::gray) { return true; }

    cur.color = Vertex_color::gray;

    for (auto& next : cur.edges) {
        if (next->color != Vertex_color::black) {
            if (has_cycle(*next)) { return true; }
        }
    }
    cur.color = Vertex_color::black;
    return false;
}

//bool has_cycle_exclusion(Graph_vertex& cur)
//{
//    if (cur.color == Vertex_color::black) { return true; }
//
//    cur.color = Vertex_color::black;
//
//    for (auto& next : cur.edges) { if (has_cycle_exclusion(*next)) { return true; }}
//    return false;
//}