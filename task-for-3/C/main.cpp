#include "main.h"

#include <iostream>

int main() {
    int a, b, c;
    std::cin >> a >> b >> c;
    std::cout << "(a + b) * c = " << multiply(add(a, b), c) << "\n";
}
