/*
 * Francisco Huelsz
 * A01019512
 * BinTrees
 */

#ifndef PROJECT2_BINTREE_H
#define PROJECT2_BINTREE_H

#include "TreeNode.h"
#include <iomanip>

#define INDENT 5

template<class T>
void pln(T thing) {
    //lazy printing method
    std::cout << thing << std::endl;
}

template<class T>
class BinTree {
private:
    TreeNode<T> * root = nullptr;

    //Recursive methods, these take in the subtree's root
    void clear(TreeNode<T> * _root);
    void insert(TreeNode<T> * _root, TreeNode<T> * new_node);
    void printInOrder(TreeNode<T> * _root);
    void printTree(TreeNode<T> * _root, int indent, char icon);

public:
    //Constructors:
    BinTree() {}
    BinTree(TreeNode<T> * node) { root = node; }

    //Destructor:
    ~BinTree() { clear(); };

    //Clearing:
    void clear();

    //Root operations:
    TreeNode<T> * getRoot() { return root; };
    void setRoot(TreeNode<T> * _root) { root = _root; }

    //Insertion:
    void insert(T data);
    void insert(TreeNode<T> * new_node);

    //Printing
    void printInOrder() { printInOrder(root); }
    void printTree() { printTree(root, INDENT, '-'); }

};

//**************************************************************************************
//Clear:

template <class T>
void BinTree<T>::clear() {
    clear(root);
}
template <class T>
void BinTree<T>::clear(TreeNode<T> *_root) {
    if (_root == nullptr)
        return;
    clear(_root->getLeft());
    clear(_root->getRight());
    delete _root;
}

//**************************************************************************************
//Insert:

template <class T>
void BinTree<T>::insert(T data) {
    TreeNode<T> * new_node = new TreeNode<T>(data);
    insert(new_node);
}

template <class T>
void BinTree<T>::insert(TreeNode<T> * new_node) {
    if (root == nullptr)
        root = new_node;
    else
        insert(root, new_node);
}

template <class T>
void BinTree<T>::insert(TreeNode<T> *_root, TreeNode<T> *new_node) {
    if (new_node->getData() < _root->getData()) {
        std::cout << new_node->getData() << " < " << _root->getData() << std::endl;
        if (_root->getLeft() == nullptr)
            _root->setLeft(new_node);
        else
            insert(_root->getLeft(), new_node);
    } else if (new_node->getData() > _root->getData()){
        std::cout << new_node->getData() << " > " << _root->getData() << std::endl;
        if(_root->getRight() == nullptr)
            _root->setRight(new_node);
        else
            insert(_root->getRight(), new_node);
    }else
        return; // Do not insert duplicate data
}

//**************************************************************************************
//Printing:
template <class T>
void BinTree<T>::printInOrder(TreeNode<T> *_root) {
    if (_root != nullptr){
        printInOrder(_root->getLeft());
        std::cout << " " << _root->getData() << " ";
        printInOrder(_root->getRight());
    }
}
template <class T>
void BinTree<T>::printTree(TreeNode<T> *_root, int indent, char icon) {
    if (_root != nullptr){
        printTree(_root->getRight(), indent + INDENT, '/');
        std::cout << std::setw(indent) << " " << icon << "- " << _root->getData() << std::endl;
        printTree(_root->getLeft(), indent + INDENT, '\\');
    }
}

#endif //PROJECT2_BINTREE_H
