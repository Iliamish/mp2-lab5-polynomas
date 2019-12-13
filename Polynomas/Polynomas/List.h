#pragma once
#include "Monom.h"

template <typename T>
struct TNode {
	T data;
	TNode<T>* next;
};

template <class T>
class TList
{
	int _size = 0;

public:
	TNode<T> * pFirst;
	TList()
	{
		pFirst = nullptr;
	}

	~TList()
	{
		if (pFirst) {
			TNode<T>* end = pFirst;
			while (pFirst->next != end) {
				TNode<T> *tmp = pFirst;
				pFirst = tmp->next;
				delete tmp;
			}
			delete pFirst;
		}
	}

	void clear() {
		TNode<T>* end = pFirst;
		
		while (pFirst->next != end) {
			TNode<T> *tmp = pFirst->next;
			_size--;
			pFirst->next = tmp->next;
			delete tmp;
		}
		

	}

	bool empty() {
		return (pFirst == nullptr);
	}

	void push(T object) {
		_size++;
		if (pFirst == nullptr) {
			TNode<T> *obj = new TNode<T>;
			obj->data = object;
			pFirst = obj;
			obj->next = pFirst;
			return;
		}
		TNode<T> *tmp = pFirst;
		TNode<T> *obj = new TNode<T>;
		obj->data = object;
		while (tmp->next != pFirst) {
			tmp = tmp->next;
		}
		tmp->next = obj;
		obj->next = pFirst;
	}

	TNode<T>* push_after(T object, TNode<T>* start) {
	
	}

	void insert(TNode<T> *prevElement, TNode<T> *afterElement, TNode<T> *obj) {
		obj->next = afterElement;
		prevElement->next = obj;
	}

	TNode<T>& front(){
		return *pFirst;
	}

	int size() {
		return _size;
	}
};

template <>
void TList<Monom>::push(Monom object) {
	_size++;
	TNode<Monom> *tmp = pFirst;
	TNode<Monom> *obj = new TNode<Monom>;
	obj->data = object;
	if (tmp == nullptr) {
		pFirst = obj;
		obj->next = obj;
		return;
	}

	while (tmp->next->data < object && tmp->next->data.degree != -1) {	
		tmp = tmp->next;
	}
	if(tmp->next->data != object)
		insert(tmp, tmp->next, obj);
	else {
		tmp->next->data.coef += object.coef;
		if (tmp->next->data.coef == 0) {
			auto ref = tmp->next;
			tmp->next = tmp->next->next;
			delete ref;
		}
	}

}

template <>
TNode<Monom>* TList<Monom>::push_after(Monom object, TNode<Monom>* start) {
	_size++;
	TNode<Monom> *tmp = start;
	TNode<Monom> *obj = new TNode<Monom>;
	obj->data = object;

	if (tmp == nullptr) {
		pFirst = obj;
		obj->next = obj;
		return pFirst;
	}

	while (tmp->next->data < object && tmp->next->data.degree != -1) {
		tmp = tmp->next;
	}
	if (tmp->next->data != object) {
		insert(tmp, tmp->next, obj);
		return obj;
	}
	else {
		tmp->next->data.coef += object.coef;
		if (tmp->next->data.coef == 0) {
			auto ref = tmp->next;
			tmp->next = tmp->next->next;
			delete ref;			
		}
		return tmp;
	}

}