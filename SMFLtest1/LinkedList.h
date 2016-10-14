/*
* Francisco Huelsz
* A01019512
* LinkedList.h 
* v0.3
*/
#pragma once
#include "Node.h"
#include <stdexcept>

template <class T>
class LinkedList {
private: 
	Node<T> * root = nullptr;
public:
	LinkedList();
	~LinkedList();
	void clear();
	void put(T _inpt);            //in back as data
	void push(T _inpt);           //in front as data
	void push(Node<T> * newNode); //in front as Node
	void print();

	int getLength();

	Node<T> * getRoot() const { return root; }

	//Homework:
	void insertAtPosition(T data, int position);
	void insertAtPosition(Node<T> * new_node, int position);
	T getDataAtHead();
	T getDataAtTail();
	T getDataAtPosition(int position);
};

template<class T>
inline LinkedList<T>::LinkedList() {
}

template<class T>
inline LinkedList<T>::~LinkedList() {
	clear();
}

template<class T>
inline void LinkedList<T>::clear() {
	//Clear all nodes
	Node<T> * item = root;
	while (item != nullptr) {
		root = item->getNext();
		delete item;
		item = root;
	}
}

template<class T>
inline void LinkedList<T>::put(T _inpt) {
	//put on end
	if (root == nullptr) {
		root = new Node<T>(_inpt);
	}
	else {
		Node<T> * current = root;
		while (current->getNext() != nullptr) {
			current = current->getNext();
		}
		current->setNext(new Node<T>(_inpt));
	}
}

template<class T>
inline void LinkedList<T>::push(T _inpt) {
	//push to front
	Node<T> * newNode = new Node<T>(_inpt);
	newNode->setNext(root);
	root = newNode;
}

template<class T>
inline void LinkedList<T>::push(Node<T> * newNode) {
	//push to front
	newNode->setNext(root);
	root = newNode;
}

template<class T>
inline void LinkedList<T>::print() {
	//Prints
	Node<T> * current = root;
	int count = 0;
	while (current!= nullptr) {
		std::cout << count++ << " --> " << current->getData() << std::endl;
		current = current->getNext();
	}
}

template<class T>
inline int LinkedList<T>::getLength() {
	Node<T> * current = root;
	int count = 0;
	while (current != nullptr) {
		current = current->getNext();
		count++;
	}
	return count;
}

// ****************************** HOMEWORK METHODS HERE *****************************************
template<class T>
inline void LinkedList<T>::insertAtPosition(T data, int position) {
	//Will insert to the position if possible.
	//If position > size-1 it will insert at the tail
	if (position > 0) {
		Node<T> * current = root;
		int indx = 1;
		while ((current->getNext() != nullptr) && (indx < position)) {
			//while to get to the corresponding node or, if impossible, the last one
			current = current->getNext();
			indx++;
		}
		Node<T> * newNode = new Node<T>(data);
		newNode->setNext(current->getNext());
		current->setNext(newNode);
	}
	else {
		push(data);
	}
}

template<class T>
inline void LinkedList<T>::insertAtPosition(Node<T> * new_node, int position) {
	//Will insert to the position if possible.
	//If position > size-1 it will insert at the tail
	if (position > 0) {
		Node<T> * current = root;
		int indx = 1;
		while ((current->getNext() != nullptr) && (indx < position)) {
			//while to get to the corresponding node or, if impossible, the last one
			current = current->getNext();
			indx++;
		}

		new_node->setNext(current->getNext());
		current->setNext(new_node);
	}
	else {
		push(new_node);
	}
}

template<class T>
inline T LinkedList<T>::getDataAtHead() {
	//returns data at head
	if (root != nullptr) {
		return root->getData();
	}
	else {
		//if head is nullptr throw exception
		throw std::runtime_error("EXCEPTION: root is null!");
	}
}

template<class T>
inline T LinkedList<T>::getDataAtTail() {
	//returns data at tail
	if (root != nullptr) {
		Node<T> * current = root;
		int indx = 0;
		while (current->getNext() != nullptr) {
			//while to reach the last node
			current = current->getNext();
		}
		return current->getData();
	}
	else {
		//if head is nullptr throw exception
		throw std::runtime_error("EXCEPTION: root is null!");
	}
}

template<class T>
inline T LinkedList<T>::getDataAtPosition(int position) {
	//Will read the position if possible.
	//If position > size+1 it will return the data in the tail.
	if (root != nullptr) {
		if (position > 0) {
			Node<T> * current = root;
			int indx = 1;
			while ((current->getNext() != nullptr) && (indx <= position)) {
				//while to get to the corresponding node or, if impossible, the last one
				current = current->getNext();
				indx++;
			}
			return current->getData();
		}
		else {
			return getDataAtHead();
		}
	}
	else {
		throw std::runtime_error("EXCEPTION: root is null!");
	}
}