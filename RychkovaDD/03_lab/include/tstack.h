#pragma once

#include <iostream>

template <typename T>
class TStack {
public:
	virtual bool isFull() const = 0;
	virtual bool isEmpty() const = 0;
	virtual void push(T val) = 0;
	virtual void pop() = 0;
	virtual T Top() const = 0;
};
