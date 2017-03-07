#ifndef SEQUENTIAL_SEARCH_ST_H
#define SEQUENTIAL_SEARCH_ST_H

#include <stdexcept>

template<typename Key_type, typename Value_type>
class Sequential_search_st {
private:
    struct Node;

    using Owning_node_pointer = Node*;
    using Raw_node_pointer = Node*;

    Owning_node_pointer first = nullptr;

    struct Node {
        Key_type key;
        Value_type value;
        Owning_node_pointer next;

        Node(Key_type k, Value_type v, Raw_node_pointer n)
                : key{k},
                  value{v},
                  next{n} {}

        Node() : next{nullptr} {}

        // cannot hand out references to an owning node pointer and copying
        // requires copying the remaining list or creating a new next with a nullptr
        Node(const Node& rhs) = delete;

        Node(Node&& rhs)
                : key{rhs.key},
                  value{rhs.value},
                  next{rhs.next} { rhs.next = nullptr; }

        ~Node() { if (next != nullptr) { delete next; }}

        Node& operator=(const Node&) = delete;

        Node& operator=(Node&& rhs)
        {
            key = rhs.key;
            value = rhs.value;
            next = rhs.next;
            rhs.next = nullptr;
            return *this;
        }
    };

public:
    Sequential_search_st() = default;

    ~Sequential_search_st() { if (first != nullptr) { delete first; }}

    Value_type get(Key_type key) const
    {
        for (auto t = first; t != nullptr; t = t->next) { if (key == t->key) { return t->value; }}
        throw std::out_of_range{""};
    }

    void put(Key_type key, Value_type value)
    {
        for (auto t = first; t != nullptr; t = t->next) {
            if (key == t->key) {
                t->value = value;
                return;
            }
        }
        first = new Node(key, value, first);
    }

};

#endif // SEQUENTIAL_SEARCH_ST_H
