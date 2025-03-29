#pragma once

#include "list.h"
#include "tstack.h"

template <typename T>
class TStackList : public TStack<T>{
private:
	TList<T> pMem;
public:
	TStackList() { // todo
	}
	TStackList(const TStackList<T>& ts) {  // todo TStackList&
		TNode<T>* tmp = ts.pMem.GetLast();
		while (tmp != nullptr) {
			pMem.InsertEnd(tmp->key);
			tmp = tmp->pNext;
		}
	}
	~TStackList() {	}

	bool isFull() const {

		TNode<int>* s = new TNode<int>(1);
		return (s == nullptr); // todo
	}
	bool isEmpty() const {
		return (pMem.GetFirst() == nullptr); // todo
	}
	void push(T val)
	{
		if (isFull()) throw "error";

		pMem.InsertFirst(val);
	}
	void pop() {
		if (isEmpty()) throw "error";

		pMem.DeleteFirst();


	}

	T Top() const {
		if (isEmpty()) { throw ""; }
		return pMem.GetFirst()->key;
	}
};
