//
// Created by franspaco on 12/10/16.
//

#ifndef POSTFIX_STACK_H
#define POSTFIX_STACK_H

#include "Node.h"

template <class T>
class Stack {
private:
    Node<T> * head = nullptr;
public:
    ~Stack () { clear(); }
    void clear();
    bool isEmpty() { return head == nullptr; }
    void push (T data);
    void push (Node<T> * new_node);
    Node<T> * pop ();
    Node<T> * top () { return head; }
};

template <class T>
void Stack<T>::clear()
{
    Node<T> * item = head;

    while (item != nullptr)
    {
        head = item->getNext();
        delete item;
        item = head;
    }
}

template <class T>
void Stack<T>::push (T data)
{
    // Create a new node instance with the data provided
    Node<T> * new_node = new Node<T>(data);
    push(new_node);
}

template <class T>
void Stack<T>::push (Node<T> * new_node)
{
    new_node->setNext(head);
    head = new_node;
}

template <class T>
Node<T> * Stack<T>::pop ()
{
    T data = head->getData();
    Node<T> * item = head;
    // Update the head of the list
    head = item->getNext();
    // Return the data only
    return item;
}

#endif //POSTFIX_STACK_H
