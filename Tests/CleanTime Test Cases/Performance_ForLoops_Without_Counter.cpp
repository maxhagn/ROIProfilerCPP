#include <iostream>
#include <vector>
#include "../lib/DataStorage.cpp"

int main(void) {
    DataStorage dataStorage("Runtime,Scope");
    dataStorage.startEvent(0);
    for ( int i = 1; i <= 1000; i++ ) {
        std::cout << "Hello World";
    }
    for ( int i = 1; i <= 1000; i++ ) {
        int numberA = 892346;
        int numberB = 384378;
        int numberC = numberA * numberB;
    }
    for ( int i = 1; i <= 1000; i++ ) {
        std::vector<std::string> shoppingList;
        shoppingList.push_back("Milk");
        shoppingList.push_back("Eggs");
        shoppingList.push_back("Meat");
        shoppingList.push_back("Water");
        shoppingList.push_back("Sugar");
        shoppingList.push_back("Flour");
        shoppingList.push_back("Salt");
        std::sort( shoppingList.begin( ), shoppingList.end( ));
    }

    dataStorage.endEvent(0);
    dataStorage.print();
    return 0;
}
