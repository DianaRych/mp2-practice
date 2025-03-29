#pragma once

#include "tstack.h"

template <typename T>
class TStackArray : public TStack<T> {
private:
	T* pMem;
	int maxSize;
	int top;
public:
	TStackArray(int maxSize = 10) {
		if (maxSize <= 0) throw "Negative size";
		this->maxSize = maxSize;
		this->pMem = new T[maxSize];
		for (int i = 0; i < this->maxSize; i++) {
			this->pMem[i] = 0;
		}
		this->top = -1;
	}
	TStackArray(const TStackArray& ts) {
		this->maxSize = ts.maxSize;
		this->top = ts.top;
		this->pMem = new T[this->maxSize];
		for (int i = 0; i < this->maxSize; i++) {
			this->pMem[i] = ts.pMem[i];
		}
	}
	~TStackArray() {
		delete[] pMem;
	}

	bool isFull() const {
		return (this->top == this->maxSize - 1);
	}
	bool isEmpty() const {
		return (this->top == -1);
	}
	void push(T val)
	{
		if (isFull()) throw "error";
		top++;
		this->pMem[top] = val;
	}
	void pop() {
		if (isEmpty()) throw "error";

		this->top--;
	}

	T Top() const {
		if (isEmpty()) return 0;
		return pMem[top];
	}
};
