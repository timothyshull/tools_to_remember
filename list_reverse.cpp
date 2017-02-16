template<typename Item_type>
struct List_node;

template<typename Item_type>
struct List_node {
    Item_type item;
    List_node<Item_type>* next = nullptr;
};

// incorrect - from Chaojun
template<typename Item_type>
List_node<Item_type>* reverse_recursive(List_node<Item_type>* head)
{
    if (head == nullptr) { return nullptr; }
    List_node<Item_type>* node = head->next;
    head->next = nullptr;

    List_node<Item_type>* final_node{reverse_recursive(node)};
    // head->next aka node may be null, attempting to access here
    node->next = head;

    return final_node;
}

// correct
template<typename Item_type>
List_node<Item_type>* recursive_reverse2(List_node<Item_type>* current, List_node<Item_type>* prev)
{
    // only necessary if called outside of reverse2
    if (current == nullptr) { return nullptr; }

    List_node<Item_type>* next{current->next};
    current->next = prev;

    if (next == nullptr) { return current; }

    return recursive_reverse2(next, current);
}

template<typename Item_type>
List_node<Item_type>* reverse2(List_node<Item_type>* head)
{
    if (head == nullptr) { return nullptr; }
    return recursive_reverse2<Item_type>(head, nullptr);
}



// ****
template<typename Item_type>
List_node<Item_type>* reverse(List_node<Item_type>* head)
{
    List_node<Item_type>* current{head};
    List_node<Item_type>* reversed{nullptr};

    List_node<Item_type>* tmp;
    while (current != nullptr) {
        tmp = current->next;
        current->next = reversed;
        reversed = current;
        current = tmp;
    }
    return reversed;
}