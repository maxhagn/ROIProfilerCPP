#include <string>
#include <vector>
#include <iostream>
#include <random>
#include "../lib/DataStorage.cpp"

int main(void) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution <std::int64_t> dis(1, 20000000);

    std::cout << dis(gen) << "\n";

    return 0;
}