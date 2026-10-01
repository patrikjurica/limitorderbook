#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

#include "order.hpp"
#include "registry.hpp"

SymbolRegistry* parse_symbols(std::string path, unsigned int size);
int parse_orders(std::string path, std::vector<Order>& vec, SymbolRegistry& registry);

#endif