#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

#include "order.hpp"
#include "registry.hpp"

SymbolRegistry* parse_symbols(std::string Path, unsigned int size) {
    std::ifstream file(Path);

    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return nullptr;
    }

    std::string line;
    unsigned int id = 0;
    SymbolRegistry* registry = new SymbolRegistry(size);

    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name;
        std::string price_factor_str;

        std::getline(ss, name, ',');
        std::getline(ss, price_factor_str, ',');

        registry->add_symbol(name, id, std::stoul(price_factor_str));
        id++;
    }

    return registry;
}

OrderType parse_order_type(std::string_view word) {
    if (word == "LIMIT")  return OrderType::LIMIT;
    if (word == "MARKET") return OrderType::MARKET;
    if (word == "IOC")    return OrderType::IOC;

    throw std::invalid_argument("Invalid order type: " + std::string(word));
}

Side parse_side(std::string_view word) {
    if (word == "BUY")  return Side::BUY;
    if (word == "SELL") return Side::SELL;

    throw std::invalid_argument("Invalid side: " + std::string(word));
}

int parse_orders(std::string Path, std::vector<Order>& vec, SymbolRegistry& registry) {
    std::ifstream file(Path);

    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return 1;
    }

    std::string line;

    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string word;

        std::getline(ss, word, ',');
        unsigned long timestamp = std::stoul(word);
        std::getline(ss, word, ',');
        unsigned int symbol = registry.get_id(word);
        std::getline(ss, word, ',');
        unsigned int order_id =  std::stoul(word);

        std::getline(ss, word, ',');
        Side side = parse_side(word);

        std::getline(ss, word, ',');
        OrderType order_type = parse_order_type(word);

        std::getline(ss, word, ',');
        unsigned int price = std::stoul(word);
        std::getline(ss, word, ',');
        unsigned int quantity = std::stoul(word);

        vec.emplace_back(order_id,
                         timestamp,
                         symbol,
                         price,
                         quantity,
                         order_type,
                         side
                         );
    }

    return 0;
}



