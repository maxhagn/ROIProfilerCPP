#include <iostream>
#include "../lib/DataStorage.cpp"
DataStorage dataStorage("Runtime,Scope,CustomCompoundStmt i000002,ForStmt 2086033");
int main(void) {
dataStorage.startEvent(0);
    dataStorage.startEvent(2);
double n, t1 = 0, t2 = 1, nextTerm = 0;
    n = 1000;

    std::cout << "Fibonacci Series: ";

    dataStorage.endEvent(2);
dataStorage.startEvent(3);
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
dataStorage.endEvent(3);

    dataStorage.endEvent(0);
dataStorage.print();return 0;
}
