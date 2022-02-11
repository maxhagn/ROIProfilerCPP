#include <iostream>
#include <vector>
#include "../lib/DataStorage.cpp"
DataStorage dataStorage("Runtime,Scope,ForStmt 2192956,ForStmt 2193096,ForStmt 2225085");
int main(void) {
dataStorage.startEvent(0);
    dataStorage.startEvent(2);
for ( int i = 1; i <= 1000; i++ ) {
        std::cout << "Hello World";
    }
dataStorage.endEvent(2);
    dataStorage.startEvent(3);
for ( int i = 1; i <= 1000; i++ ) {
        int numberA = 892346;
        int numberB = 384378;
        int numberC = numberA * numberB;
    }
dataStorage.endEvent(3);
    dataStorage.startEvent(4);
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
dataStorage.endEvent(4);
    dataStorage.endEvent(0);
dataStorage.print();return 0;
}
