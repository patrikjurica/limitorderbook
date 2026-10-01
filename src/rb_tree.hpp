#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>
#include "dl_list.hpp"
#include "order.hpp"

enum Colour {
    RED,
    BLACK
};

struct Node {
    Node* parent;
    Node* left;
    Node* right;
    Colour colour;
    dl_list* orders;
    int price_level;
};

class Tree {
private:
    Node* root;
    Node* min;
    Node* max;

    void dealloc(Node* node);
    Node* create_node(Order* order, Colour colour, Node* parent_node);
    Node* recursive_insert(Node* node, Order* order);
    void left_rotate(Node* x);
    void right_rotate(Node* x);
    bool is_black(Node* node) const;
    Node* find_successor(Node* node) const;
    Node* find_predecessor(Node* node) const;

public:
    Tree();
    ~Tree();

    bool is_empty() const;
    void insert(Order* order);
    int best_buy() const;
    int best_sell() const;
    Order* extract_best_buy();
    Order* extract_best_sell();
    bool is_buy_side_empty() const;
    bool is_sell_side_empty() const;
};

#endif
