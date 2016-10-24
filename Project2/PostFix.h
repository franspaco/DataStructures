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
    BinTree<char> tree;
    LinkedList<TreeNode<char> *> buffer;

    void buildTree();
    int  recursiveTreeEvaluate(TreeNode<char> * _root);
    void recursivePostPrint(TreeNode<char> * _root);
public:

    PostFix() {}
    PostFix(std::string _inpt);

    ~PostFix();

    void setPostfix(std::string _inpt);

    int evaluate();

    void printPostTree();

};


#endif //PROJECT2_POSTFIX_H
