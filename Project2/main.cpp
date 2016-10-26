/*
 * Francisco Huelsz
 * A01019512
 * BinTrees
 */

#include <iostream>
#include "BinTree.h"
#include "PostFix.h"


int main() {
    /*
     // Test prints
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

    pf.setPostfix("1 1 + 1 1 + + 1 1 + 1 1 + + +");
    pf.printTree();
    std::cout << pf.evaluate() << std::endl;
    pf.printPostTree();
     */

    PostFix pf;
    std::string inpt = "";

    pln(" -=-=-=- POSTFIX (RPN) EVALUATOR -=-=-=-");
    pln("PLease insert a postfix expression:");
    pln("  - Insert spaces between every element");
    pln("  - Example: \"5 11 22 + 42 * + 3 -\"");
    pln("Type in 'q' to quit.");

    do {
        pln("Type in postfix:");
        std::getline(std::cin, inpt);
        if(inpt == "q")
            break;
        pf.setPostfix(inpt);
        std::cout << "Input processed as: \"";
        pf.printPostTree();
        pln("\"");
        pln("Generated tree:");
        pf.printTree();
        std::cout << "Evaluated result: ";
        std::cout << pf.evaluate() << std::endl;
        pln("\n");
    }while(inpt != "q");

    pf.clean();

    return 0;
}