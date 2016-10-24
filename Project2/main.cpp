/*
 * Francisco Huelsz
 * A01019512
 * BinTrees
 */

#include <iostream>
#include "BinTree.h"
#include "PostFix.h"


int main() {
    std::cout << "Hello, World!" << std::endl;
    /*
    BinTree<int> charTree;

    charTree.insert(0);

    for(int i = 1; i <= 20; i++) {
        charTree.insert(i);
        charTree.insert(-i);
    }

    charTree.printInOrder();
    std::cout << std::endl;
    charTree.printTree();
     */

    PostFix pf("34+2*1+2-1-6/2^");
    pf.setPostfix("2345++1++");
    pf.setPostfix("1234+*+");
    pf.setPostfix("2 1 2 3 4 + * + ^");
    pf.setPostfix("5 1 2 + 4 * + 3 -");

    std::cout << pf.evaluate() << std::endl;

    pf.printPostTree();

    return 0;
}