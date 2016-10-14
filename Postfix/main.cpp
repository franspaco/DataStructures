#include <iostream>
#include "Postfix.h"

int main() {

    Postfix p("5+3");

    //p.convertToPostfix();

    p.setPostfix("83-");

    std::cout << p.evaluate() << std::endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}