#pragma once
#include <iostream>


class UnderFlow : public std::exception {
public:
	const char* what() const noexcept override {
		return "ERROR: UNDERFLOW";
	}
};

class InvalidIndex : public std::exception {
public:
	const char* what() const noexcept override {
		return "ERROR: INVALID INDEX";
	}
};


template <typename T>
class DoubleNode {
private:
	T data;
	DoubleNode<T>* next;
	DoubleNode<T>* prev;	//You can move forward/backwards

public:
	//Constructor
	DoubleNode(T val) {
		data = val;
		next = nullptr;
		prev = nullptr;
	}

	//Getter
	DoubleNode* getNext() {
		return next;
	}
	DoubleNode* getPrev() {
		return prev;
	}

	T& getData() {
		return data;
	}

	//setter
	void setNext(DoubleNode<T>* val) {
		next = val;
	}
	void setPrev(DoubleNode<T>* val) {
		prev = val;
	}

};



template <typename T>
class DoubleLinkedList {
private:
	int length;
	DoubleNode<T>* first;
	DoubleNode<T>* last;

public:
	DoubleLinkedList() {
		length = 0;
		first = nullptr;
		last = nullptr;

	}

	//Destructor
	~DoubleLinkedList() {
		DoubleNode<T>* current = first;
		while (current) {
			DoubleNode<T>* next = current->getNext();
			delete current;
			current = next;
		}
	}

	int size() {
		return length;
	}

	bool isEmpty() {
		return length == 0;
	}

	// === addItem ===
	//Adds the new value to a new Node in order
	void addItem(T val) {
		DoubleNode<T>* newNode = new DoubleNode<T>(val);

		if (!first) {
			first = last = newNode;
		}
		else {
			last->setNext(newNode);
			newNode->setPrev(last);
			last = newNode;
		}
		length++;

	}
	
	// === find ===
	DoubleNode<T>* find(const T& val) {
		DoubleNode<T>* current = first;
		while (current) {
			if (current->getData() == val) {
				return current;
			}
			current = current->getNext();
		}
		return nullptr;
	}

	// === remove ===
	DoubleNode<T>* remove(const T& val) {
		DoubleNode<T>* current = find(val);
		if (!current) {
			return nullptr;
		}

		if (current == first) {
			first = first->getNext();
			if (first) {
				first->setPrev(nullptr);
			}
			else {
				last = nullptr; //list is now empty
			}
		}
		else if (current == last) {
			last = last->getPrev();
			if (last) {
				last->setNext(nullptr);
			}
		}
		else {
			DoubleNode<T>* prev = current->getPrev();
			DoubleNode<T>* next = current->getNext();
			if (prev) {
				prev->setNext(next);
			}
			if (next) {
				next->setPrev(prev); 
			}
		}
		length--;
		current->setNext(nullptr);
		current->setPrev(nullptr);
		return current;
	}

	// === seeAt ===
	DoubleNode<T>* seeAt(int index) {
		if (index < 0 || index > length) {
			return nullptr;
		}

		DoubleNode<T>* current = first;
		for (int i = 0; i < index; i++) {
			current = current->getNext();
		}
		return current;
	}
};




