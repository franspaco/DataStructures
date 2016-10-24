/*
 * Francisco Huelsz
 * A01019512
 * BinTrees
 */

#include <cmath>
#include "PostFix.h"

//**************************************************************************************
//Constructors:

PostFix::PostFix(std::string _inpt) {
    postfix = _inpt;
    buildTree();
}

//**************************************************************************************
//Destructors:

PostFix::~PostFix() {

}

//**************************************************************************************
//Setters & getters:

void PostFix::setPostfix(std::string _inpt) {
    postfix = _inpt;
    buildTree();
}


//**************************************************************************************
//Tree Construction:

void PostFix::buildTree() {
    TreeNode<char> * left = nullptr;
    TreeNode<char> * right = nullptr;
    TreeNode<char> * op = nullptr;

    TreeNode<char> * temp;

    for (int i = 0; i < postfix.length(); i++){

        char next = postfix.at(i);

        std::cout << "Insert: " << next << std::endl;

        if(next >= '0' && next <= '9'){
            temp = new TreeNode<char>(next);
            buffer.put(temp);
        }
        else if(next == '+' || next == '*' || next == '-' || next == '/' || next == '^'){
            op = new TreeNode<char>(next);
            op->setRight(buffer.popLast());
            op->setLeft(buffer.popLast());
            buffer.put(op);
            tree.setRoot(op);
        }

        tree.printTree();
        std::cout << "\n\n";
    }
    tree.printTree();
}

//**************************************************************************************
//Evaluation:

int PostFix::evaluate() {
    return recursiveTreeEvaluate(tree.getRoot());
}

int PostFix::recursiveTreeEvaluate(TreeNode<char> *_root) {
    int res = 0;
    char next = _root->getData();

    if(next >= '0' && next <= '9'){
        return next - 48;
    }

    int left = recursiveTreeEvaluate(_root->getLeft());
    int right = recursiveTreeEvaluate(_root->getRight());


    switch (next){
        case '+':
            return left + right;
        case '*':
            return left * right;
        case '-':
            return left - right;
        case '/':
            return left / right;
        case '^':
            return std::pow(left, right);
        default:
            break;
    }
}

//**************************************************************************************
//Print:
void PostFix::printPostTree() {
    recursivePostPrint(tree.getRoot());
    std::cout << std::endl;
}

void PostFix::recursivePostPrint(TreeNode<char> *_root) {
    if (_root == nullptr)
        return;
    recursivePostPrint(_root->getLeft());
    recursivePostPrint(_root->getRight());
    std::cout << _root->getData();
}


