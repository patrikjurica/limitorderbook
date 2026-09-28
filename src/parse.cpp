#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <sstream>

#include "order.hpp"

int parse(std::string Path, std::vector<Order> &vec) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return 1;
    }

    std::string line;
    uint64_t id = 0;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string word;

        // 2. Extract each field using ';' as the delimiter
        while (std::getline(ss, word, ';')) {
            std::cout << "[" << word << "] ";
        }
        std::cout << '\n'; // End of line
    }

    return 0;
}



