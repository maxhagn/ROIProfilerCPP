#include <iostream>
#include <fstream>
#include "../lib/DataStorage.cpp"

int main(void) {
    DataStorage dataStorage("Runtime,Scope");
    dataStorage.startEvent(0);
    double n, t1 = 0, t2 = 1, nextTerm = 0;
    n = 1000;

    std::cout << "Fibonacci Series: ";

    for (int i = 1; i <= n; ++i) {
        if(i == 1) {
            std::cout << t1;
            std::cout << ", ";
        }
        else if(i == 2) {
            std::cout << t2;
            std::cout << ", ";
        }
        nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;

        std::cout << nextTerm << ", ";
    }

    dataStorage.endEvent(0);
    dataStorage.print();
    return 0;
}
