/*
 * Francisco Huelsz
 * A01019512
 * BinTrees
 */

#include <cmath>
#include <stdexcept>
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
    tree.clear();
    TreeNode<std::string> * op = nullptr;

    TreeNode<std::string> * temp;

    for (int i = 0; i < postfix.length(); i++){
        //Iterate over every char of the postfix

        //Current token
        std::string next = "";

        if(postfix.at(i) == ' ')
            continue;

        //Tokenize string:
        while(i < postfix.length() && postfix.at(i) != ' '){
            //If the char is not a space append to current token
            next.append(std::string(1, postfix.at(i)));
            i++;
        }

        if(next == "+" || next == "*" || next == "-" || next == "/" || next == "^") {
            //If token is an operator

            //Create operator node and set the child nodes
            op = new TreeNode<std::string>(next);
            op->setRight(buffer.popLast());
            op->setLeft(buffer.popLast());

            if(op->getRight() == nullptr || op->getLeft() == nullptr){
                std::cout << "INVALID POSTFIX" << std::endl;
                return;
            }

            //Add operator TreeNode to buffer LinkedList
            buffer.put(op);

            //Set operator as root
            tree.setRoot(op);
        }
        else if (isNumber(next)){
            //If token is a number
            temp = new TreeNode<std::string>(next);
            //Add number TreeNode to buffer LinkedList
            buffer.put(temp);
        }else{
            std::cout << "INVALID POSTFIX" << std::endl;
            throw std::runtime_error("INVALID POSTFIX");
        }
    }
}

//**************************************************************************************
//Evaluation:

int PostFix::evaluate() {
    return recursiveTreeEvaluate(tree.getRoot());
}

int PostFix::recursiveTreeEvaluate(TreeNode<std::string> *_root) {
    std::string data = _root->getData();
    char fdata = data.at(0);  //first char of the data


    if(fdata >= '0' && fdata <= '9'){
        //Base case:
        // If first char is a number then data is a number.
        // Returns the numerical value of data.
        return std::stoi(data);
    }

    //If data is not a number:

    //Recursively evaluate the child nodes:
    int left = recursiveTreeEvaluate(_root->getLeft());
    int right = recursiveTreeEvaluate(_root->getRight());

    //Operate and return:
    switch (fdata){
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

void PostFix::recursivePostPrint(TreeNode<std::string> *_root) {
    if (_root == nullptr)
        return;
    recursivePostPrint(_root->getLeft());
    recursivePostPrint(_root->getRight());
    std::cout << _root->getData() << " ";
}

bool PostFix::isNumber(std::string in) {
    for(int i = 0; i < in.length(); i++){
        if(in.at(0) < '0' || in.at(0) > '9')
            return false;
    }
    return true;
}


