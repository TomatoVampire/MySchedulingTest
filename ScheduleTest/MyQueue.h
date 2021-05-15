#pragma once
#include<iostream>
using namespace std;

template<class T>
struct Node {
	T data;
	Node* next;
	Node(T& d) :data(d), next(NULL) {}
	Node() :data(T(-1)), next(NULL) {}
};

template<class E>
class MyQueue {
protected:
	Node<E>* head;
	Node<E>* tail;
	int size;
public:
	MyQueue():size(0){
		head = new Node<E>();
		tail = head;
	}

	int push(E a) {
		Node<E>* t = new Node<E>(a);
		tail->next = t;
		tail = t;
		size++;
		return 1;
	}

	E front() {
		if (head->next == NULL) return head->data;
		return head->next->data;
	}

	E pop() {
		if (size == 0) return E(-1);
		else {
			E a = front();
			Node<E>* temp = head->next;
			head->next = temp->next;
			delete temp;
			size--;
			if (size == 0) tail = head;
			return a;
		}
	}

	void clear() {
		while (size != 0) {
			pop();
		}
		//size = 0;
	}

	E& operator[](int index) {
		auto t = head;
		t = t->next;
		while (index-- && t) t = t->next;
		if (t == NULL) {
			cout << "error!index out of range!\n";
			exit(1);
		}
		return t->data;
	}

	int getsize() {
		return size;
	}

	int isempty() {
		return size == 0 ? 1 : 0;
	}
};