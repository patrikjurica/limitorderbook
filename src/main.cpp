#include <iostream>
#include <chrono>

int main () {


    // start measuring time
    auto start = std::chrono::high_resolution_clock::now();

    // process orders

    // stop measuring time
    auto stop = std::chrono::high_resolution_clock::now();

    // calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "Time taken to process orders: " << duration.count() << " milliseconds" << std::endl;
    return 0;
}