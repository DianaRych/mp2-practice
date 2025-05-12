#pragma once

#include "TList.h"

template <typename T>
class HeadList : public TList<T> {
protected:
	TNode<T>* pHead;
public:
	HeadList() : TList<T>() {
		this->pHead = new TNode<T>();
		this->pHead->pNext = this->pFirst;
	}

	HeadList(const HeadList& other) :TList<T>(other) {
		this->pHead = new TNode<T>();
		this->pHead->pNext = this->pFirst;
	}

	~HeadList() {
		delete this->pHead;

	}

	virtual void InsertFirst(T key) {
		TList<T>::InsertFirst(key);
		this->pHead->pNext = this->pFirst;
	}

	virtual void DeleteFirst() {
		TList<T>::DeleteFirst();
		this->pHead->pNext = this->pFirst;
	}

	const HeadList& operator=(const HeadList& other) {
		this->pHead = nullptr;
		TList<T>::operator=(other);
		this->pHead = new TNode<T>();
		this->pHead->pNext = this->pFirst;
		return *this;
	}

};