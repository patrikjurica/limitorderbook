#ifndef REG_HPP
#define REG_HPP

#include <unordered_map>
#include <string>
#include <vector>

typedef struct SymbolRegistry{

private:
    std::unordered_map<std::string, unsigned int> symbol_to_id;
    std::vector<unsigned int> price_factor;
    unsigned int size;

public:
    SymboRegistry(unsigned int size) {
        symbol_to_id_.reserve(size);
        price_factor_.reserve(size);
        size = 0;
    }

    unsigned int get_price_factor(unsigned int id) const {
        return price_factor[id];
    }

    unsigned int get_price_factor(std::string_view name) const {
        auto it = symbol_to_id_.find(name);
        if (it != symbol_to_id_.end()) {
            return price_factor_[it->second];
        }
        return size + 1;
    }

    unsigned int add_symbol(const std::string& symbol, unsigned int id, unsigned int factor) {
        unsigned int new_id = static_cast<unsigned int>(symbol_to_id_.size());

        symbol_to_id_[symbol] = new_id;
        price_factor_.push_back(factor);
        return new_id;
    }

    unsigned int get_id(std::string_view name) const {
        auto it = symbol_to_id_.find(name);
        if (it != symbol_to_id_.end()) {
            return it->second;
        }
        return size + 1;
    }

    unsigned int get_size() const { return size; }
} SymbolRegistry;

#endif