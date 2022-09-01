#include <iostream>
#include "infixToPostfix.h"
#include "postfixCalculator.h"

int main() {
    std::string exp;
    std::cout << "Enter a logical formula: ";
    std::cin >> exp;
    postfixCalculator(infixToPosfix(exp));
    return 0;
}