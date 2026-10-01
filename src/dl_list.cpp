#include "order.hpp"
#include <cstddef>

typedef struct dl_node {
    struct dl_node* prev;
    struct dl_node* next;
    Order* order;

    dl_node(Order* item) : prev(nullptr), next(nullptr), order(item) {}
} dl_node;

struct dl_list{

private:
    dl_node* first;
    dl_node* last;
    size_t length;

public:
    dl_list() : first(nullptr), last(nullptr), length(0) {}

    ~dl_list()
    {
        while (!is_empty()) {
            dl_node* node = first;
            first = first->next;

            delete node->order;
            delete node;
        }
    }

    void insert_back( Order* item )
    {
        dl_node* node = new dl_node(item);

        if (first == nullptr) {
            first = node;
            last = node;
        } else {
            last->next = node;
            node->prev = last;
            last = node;
        }

        length++;
    }

    bool is_empty() const
    {
        if (first == nullptr) { return true; }
        return false;
    }

    dl_node* extract_first()
    {
        if (first == nullptr) {
            return nullptr;
        }

        dl_node* item = first;
        first = first->next;
        item->next = nullptr;

        if (first != nullptr) {
            first->prev = nullptr;
        } else {
            last = nullptr;
        }

        length--;
        return item;
    }

    size_t len() const { return length; }
};