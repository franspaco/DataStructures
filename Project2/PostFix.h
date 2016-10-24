/*
 * Francisco Huelsz
 * A01019512
 * BinTrees
 */

#ifndef PROJECT2_POSTFIX_H
#define PROJECT2_POSTFIX_H


#include "BinTree.h"
#include "LinkedList.h"

#include <string>

class PostFix {
private:
    std::string postfix;
    BinTree<std::string> tree;
    LinkedList<TreeNode<std::string> *> buffer;

    void buildTree();
    int  recursiveTreeEvaluate(TreeNode<std::string> * _root);
    void recursivePostPrint(TreeNode<std::string> * _root);
    bool isNumber(std::string in);
public:

    PostFix() {}
    PostFix(std::string _inpt);

    ~PostFix();

    void setPostfix(std::string _inpt);

    int evaluate();

    void printPostTree();

    void printTree() {tree.printTree(); }

};


#endif //PROJECT2_POSTFIX_H
