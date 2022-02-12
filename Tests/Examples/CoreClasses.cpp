#include <iostream>

void foo () {
    int i = 0;
    while ( i <= 10 ) { i++; }
    while ( i <= 20 ) { i++; }
    while ( i <= 30 ) { i++; }

    std::cout << i;
}

int main(void) {
    foo();
    return 0;
}
