#pragma once

#include "HeadList.h"

template <typename T>
class ListRingHead : public HeadList<T> {
public:
	ListRingHead() : HeadList<T>() {
		this->pStop = this->pHead;
		this->pHead->pNext = this->pStop;
	}

	ListRingHead(const ListRingHead& other) :HeadList<T>(other) {
		this->pStop = this->pHead;
		this->pLast->pNext = this->pStop;
	}

	virtual void InsertEnd(T key) {
		TList<T>::InsertEnd(key);
		this->pLast->pNext = this->pStop;
	}

	~ListRingHead() {
		if (this->pLast != nullptr) {
			this->pLast->pNext = nullptr;
		}
	}

	virtual void DeleteLast() {
		TList<T>::DeleteLast();
		this->pLast->pNext = this->pStop;
	}

	const ListRingHead& operator=(const ListRingHead& other) {
		this->pStop = nullptr;
		HeadList<T>::operator=(other);
		this->pStop = this->pHead;
		this->pLast->pNext = this->pStop;
		return *this;
	}
};