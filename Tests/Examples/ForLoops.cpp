#include <iostream>
#include <math.h>
#include <thread>

int main(void) {

    // Compound Statements
    int i = 1;
    i = 10 + i;
    i++;

    // 10 ms
    std::this_thread::sleep_for(std::chrono::microseconds (10));

    // 100 ms
    for ( int j = 1; j <= 10; j++ ) {
        std::this_thread::sleep_for(std::chrono::microseconds (5));
        std::this_thread::sleep_for(std::chrono::microseconds (5));
    }
    // 1000 ms
    for ( int j = 1; j <= 100; j++ ) {
        std::this_thread::sleep_for(std::chrono::microseconds (5));
        std::this_thread::sleep_for(std::chrono::microseconds (5));
    }
    // 10000 ms
    for ( int j = 1; j <= 1000; j++ ) {
        std::this_thread::sleep_for(std::chrono::microseconds (5));
        std::this_thread::sleep_for(std::chrono::microseconds (5));
    }
    return 1;
}
