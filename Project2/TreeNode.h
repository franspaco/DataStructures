/*
 * Francisco Huelsz
 * A01019512
 * BinTrees
 */

#ifndef PROJECT2_TREENODE_H
#define PROJECT2_TREENODE_H

#include <iostream>

template <class T>
class TreeNode {
private:
    T data;
    TreeNode * left = nullptr;
    TreeNode * right = nullptr;
    int height = 1;

public:
    //Constructors:
    TreeNode() {}
    TreeNode( T _data) { data = _data; }

    //Data manipulation:
    T getData() { return data; }
    void setData(T _data) { data = _data; }

    //Left:
    TreeNode * getLeft() { return left; }
    void setLeft(TreeNode * _left) { left = _left; }

    //Right
    TreeNode * getRight() { return right; }
    void setRight(TreeNode * _right) { right = _right; }

    //Height:
    int getHeight() { return height; }
    void setHeight(int _height) { height = _height; }

    //iostream printing operator overload:
    template <class S>
    friend std::ostream & operator<< (std::ostream & stream, const TreeNode<S> & node);

};

template <class T>
std::ostream & operator<< (std::ostream & stream, const TreeNode<T> & node){
    stream << node.data;
    return stream;
}

#endif //PROJECT2_TREENODE_H
