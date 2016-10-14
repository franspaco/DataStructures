/*
Francisco Huelsz
A01019512

Stack.h

*/

#pragma once
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>

using namespace std;

template <class Type>
class Stack {
private:
	Type * root;
	int  size;
	int  last;
public:
	Stack(int in);
	~Stack();

	int  push(Type in);
	Type pop();
	Type  top();
	void print();
	
};

template <class Type>
Stack<Type>::Stack(int in) {
	//Init size, allocate space, and init last address as 0, meaning empty
	size = in;
	root = (int*)malloc(in * (sizeof(int)));
	last = 0;
}

template <class Type>
Stack<Type>::~Stack() {
	//Destructor: frees allocated memory
	free(root);
}

template <class Type>
int Stack<Type>::push(Type in) {
	//Tries to push a new element to the last place, 
	//  rejects it if no space available.
	//Returns 1 on success, 0 otherwise.
	//Increases last addres.
	if (last < size) {
		root[last] = in;
		last++;
		return 1;
	}
	return 0;
}

template <class Type>
Type Stack<Type>::pop() {
	//If not empty will return the element at the end of the list,
	// if empty a -1 will be returned.
	//Decreases the last address.
	if (last > 0) {
		last--;
		return root[last];
	}
	else {
		return -1;
	}
}

template <class Type>
Type Stack<Type>::top() {
	//If not empty will return the element at the beginning of the list,
	// if empty a -1 will be returned.
	if (last > 0) {
		return root[last - 1];
	}
	else {
		return -1;
	}
}

template <class Type>
void Stack<Type>::print() {
	//Prints all the elements (from zero to last-1)
	cout << " -- First -- \n";
	for (int i = 0; i < last; i++) {
		cout << root[i] << endl;
	}
	cout << " -- Last -- \n";
}