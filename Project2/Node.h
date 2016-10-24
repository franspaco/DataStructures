/*
* Francisco Huelsz
* A01019512
* Node.h
* v1
*/
#ifndef NODE_H
#define NODE_H

#include <iostream>

template <class T>
class Node {
private:
	T data;
	Node * next = nullptr;
public:
	// Constructors
	Node();
	Node(T _data);
	// Destructor
	~Node();
	// Access methods
	void setData(T _data);
	void setNext(Node * _next);
	T getData();
	Node * getNext();

	// Method that does not belong to this class, but is a friend
	template <class S>
	friend std::ostream & operator<< (std::ostream & stream, const Node<S> & node);
};

template <class T>
std::ostream & operator<< (std::ostream & stream, const Node<T> & node) {
	stream << "-" << node.data << "-";
	return stream;
}

#endif

template<class T>
inline Node<T>::Node() {
}

template<class T>
inline Node<T>::Node(T _data) {
	data = _data;
}

template<class T>
Node<T>::~Node() {
	//next = nullptr;
}

template<class T>
void Node<T>::setData(T _data) {
	data = _data;
}

template<class T>
void Node<T>::setNext(Node * _next) {
	next = _next;
}

template<class T>
T Node<T>::getData() {
	return data;
}

template<class T>
Node<T> * Node<T>::getNext() {
	return next;
}
