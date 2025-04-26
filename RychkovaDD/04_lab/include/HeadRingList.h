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
		if (this->pLast != nullptr)
		{
			this->pLast->pNext = this->pHead;
		}
	}

	void InsertEnd(T key) {
		HeadList<T>::InsertEnd(key);
		this->pLast->pNext = this->pHead;
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
		TList<T>::DeleteLast();
		if (this->pLast != nullptr) {
			this->pLast->pNext = this->pFirst;
		}
	}
};