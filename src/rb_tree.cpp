#include <cstddef>
#include "dl_list.hpp"
#include "order.hpp"
#include "rb_tree.hpp"

Tree::Tree() : root(nullptr), min(nullptr), max(nullptr)  {}

Tree::~Tree()
{
    if (!is_empty())
    {
        dealloc(root);
    }
}

void Tree::dealloc(Node* node)
{
    if (node->left != nullptr) { dealloc(node->left); }
    if (node->right != nullptr) { dealloc(node->right); }

    delete node->orders;
    delete node;
}

Node* Tree::create_node(Order* order, Colour colour, Node* parent) {
    dl_list* orders_list = new dl_list;
    orders_list->insert_back(order);
    Node* node = new Node{
            parent,
            nullptr,
            nullptr,
            colour,
            orders_list,
            order->price
    };
    return node;
}

Node* Tree::recursive_insert(Node* node, Order* order)
{
    if (order->price == node->price_level)
    {
        node->orders->insert_back(order);
    }
    else if (order->price > node->price_level) {

        if (node->right == nullptr) {
            node->right = create_node(order, RED, node);
            return node->right;
        } else {
            return recursive_insert(node->right, order);
        }

    } else {

        if (node->left == nullptr) {
            node->left = create_node(order, RED, node);
            return node->left;
        } else {
            return recursive_insert(node->left, order);
        }
    }
    return nullptr;
}

void Tree::left_rotate(Node* x) {
    Node* y = x->right;

    if (y == nullptr) { return; }

    x->right = y->left;

    if (y->left != nullptr)
    {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == nullptr)
    {
        root = y;
    } else {
        if (x == x->parent->left)
        {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
    }

    y->left = x;
    x->parent = y;
}

void Tree::right_rotate(Node* x) {
    Node* y = x->left;

    if (y == nullptr) { return; }

    x->left = y->right;

    if (y->right != nullptr)
    {
        y->right->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == nullptr)
    {
        root = y;
    } else {
        if (x == x->parent->right)
        {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
    }

    y->right = x;
    x->parent = y;
}

bool Tree::is_black(Node* node)
{
    return node == nullptr || node->colour == BLACK;
}

Node* Tree::find_successor(Node* node) {
    if (node == nullptr) return nullptr;

    if ( node->right != nullptr) {
        Node* curr = node->right;
        while (curr->left != nullptr) {
            curr = curr->left;
        }
        return curr;
    }

    Node* curr = node;
    Node* p = node->parent;
    while (p != nullptr && curr == p->right) {
        curr = p;
        p = p->parent;
    }
    return p;
}

Node* Tree::find_predecessor(Node* node) {
    if (node == nullptr) return nullptr;

    if ( node->left != nullptr ) {
        Node* curr = node->left;
        while (curr->right != nullptr) {
            curr = curr->right;
        }
        return curr;
    }

    Node* curr = node;
    Node* p = node->parent;
    while (p != nullptr && curr == p->left) {
        curr = p;
        p = p->parent;
    }
    return p;
}

size_t Tree::is_empty() const
{
    if (root == nullptr) { return true; }
    return false;
}

void Tree::insert(Order* order)
    {
        if (root == nullptr) {
            root = create_node(order, BLACK, nullptr);
            min = root;
            max = root;
            return;
        }

        Node* node = recursive_insert(root, order);

        if (order->price > max->price_level) { max = node; }
        if (order->price < min->price_level) { min = node; }

        if (node == nullptr || node->parent->colour == BLACK) { return; }

        while (node != root && node->parent->colour == RED)
        {
            if (node->parent == node->parent->parent->left)
            {
                Node* uncle = node->parent->parent->right;

                if (!is_black(uncle))
                {
                    node->parent->colour = BLACK;
                    uncle->colour = BLACK;
                    node->parent->parent->colour = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right)
                    {
                        node = node->parent;
                        left_rotate(node);
                    }
                    node->parent->colour = BLACK;
                    node->parent->parent->colour = RED;
                    right_rotate(node->parent->parent);
                }
            } else {
                if (node->parent == node->parent->parent->right) {
                    Node *uncle = node->parent->parent->left;

                    if (!is_black(uncle))
                    {
                        node->parent->colour = BLACK;
                        uncle->colour = BLACK;
                        node->parent->parent->colour = RED;
                        node = node->parent->parent;
                    } else {
                        if (node == node->parent->left)
                        {
                            node = node->parent;
                            right_rotate(node);
                        }
                        node->parent->colour = BLACK;
                        node->parent->parent->colour = RED;
                        left_rotate(node->parent->parent);
                    }
                }
            }
        }
        root->colour = BLACK;
    }

int Tree::best_buy() const
{
    return max->price_level;
}

int Tree::best_sell() const
{
    return min->price_level;
}

Order* Tree::extract_best_buy()
{
    Order* order = max->orders->extract_first();

    if (max->orders->is_empty())
    {
        Node* predecessor = max;
        do {
            predecessor = find_predecessor(predecessor);
        } while (predecessor != nullptr && predecessor->orders->is_empty());
        max = predecessor;
    }

    return order;
}

Order* Tree::extract_best_sell()
{
    Order* order = min->orders->extract_first();

    if (min->orders->is_empty())
    {
        Node* successor = min;
        do {
            successor = find_successor(successor);
        } while (successor != nullptr && successor->orders->is_empty());
        min = successor;
    }

    return order;
}

bool Tree::is_buy_side_empty() const {
    return max == nullptr || max->orders->is_empty();
}

bool Tree::is_sell_side_empty() const {
    return min == nullptr || min->orders->is_empty();
}
