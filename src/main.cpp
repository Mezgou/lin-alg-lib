#include <iostream>

int main() {
#ifndef NDEBUG
    std::cout << "Tests..." << std::endl;
#endif
    std::cout << "Hello, World!" << std::endl;
}