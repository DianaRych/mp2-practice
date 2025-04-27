#pragma once

#include "HeadList.h"
#include "TList.h"

template <typename T>
class ListRingHead : public HeadList<T> {
public:
	ListRingHead() : HeadList<T>() {
		this->pHead->pNext = this->pHead;
		this->pStop = this->pHead;
	}

	ListRingHead(const ListRingHead& other) : HeadList<T>(other) {
		if (pLast != nullptr)
		{
			this->pLast->pNext = this->pHead;
		}
	}

	void InsertEnd(T key) {
		HeadList<T>::InsertEnd(key);
		pLast->pNext = pHead;
	}

	void DeleteLast() { // TODO: use base
		if (this->pFirst == nullptr) {
			throw "Empty";
		}
		if (this->pFirst->pNext == this->pFirst) {
			delete this->pFirst;
			this->pFirst = nullptr;
			this->pHead->pNext = nullptr;
			this->pStop = this->pHead;
			return;
		}
		TNode<T>* tmp = this->pFirst;
		while (tmp->pNext != this->pFirst) { // бежим до того момента пока не найдем ласт, который указывает на ферст
			tmp = tmp->pNext; // tmp last elem
		}
		TNode<T>* last = tmp->pNext;
		tmp->pNext = this->pFirst;
		delete last;
		this->pStop = this->pHead;
	}
};
