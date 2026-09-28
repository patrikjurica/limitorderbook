#ifndef DL_LIST_HPP
#define DL_LIST_HPP

#include "order.hpp"
#include <cstddef>

struct dl_node {
    dl_node* prev;
    dl_node* next;
    Order* order;

    dl_node(Order* item);
};

struct dl_list {
private:
    dl_node* first;
    dl_node* last;
    size_t length;

public:
    dl_list();
    ~dl_list();

    void insert_back(Order* item);
    bool is_empty() const;
    dl_node* extract_first();
    size_t len() const;
};

#endif