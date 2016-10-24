/*
 * Francisco Huelsz
 * A01019512
 * BinTrees
 */

#include <iostream>
#include "BinTree.h"
#include "PostFix.h"


int main() {
    std::cout << "Hello!" << std::endl;

    PostFix pf("5 11 22 + 42 * + 3 -");
    pf.printTree();
    std::cout << pf.evaluate() << std::endl;
    pf.printPostTree();

    pf.setPostfix("25 35 + 2 ^");
    pf.printTree();
    std::cout << pf.evaluate() << std::endl;
    pf.printPostTree();

    pf.setPostfix("1 2 3 + 8 4 + - + 5 4 - /");
    pf.printTree();
    std::cout << pf.evaluate() << std::endl;
    pf.printPostTree();

    pf.setPostfix("1 2 3 4 5 6 7 8 9 + + + + + + + +");
    pf.printTree();
    std::cout << pf.evaluate() << std::endl;
    pf.printPostTree();

    pf.setPostfix("9 8 + 7 + 6 + 5 + 4 + 3 + 2 + 1 +");
    pf.printTree();
    std::cout << pf.evaluate() << std::endl;
    pf.printPostTree();
    

    return 0;
}