#pragma once

#include "TList.h"

template <typename T>
class HeadList : public TList<T> {
protected:
    TNode<T>* pHead;

public:
    // Конструктор
    HeadList() : TList<T>() {
        this->pHead = new TNode<T>();
        this->pHead->pNext = nullptr;
    }

    // Конструктор копирования
    HeadList(const HeadList& other) : TList<T>(other) {
        this->pHead = new TNode<T>();
        this->pHead->pNext = this->pFirst;
    }

    // Деструктор
    ~HeadList() {
        delete this->pHead;
    }

    const HeadList& operator=(const HeadList& other) {
        if (this == &other) return *this;
        TList<T>::operator=(other);
        this->pHead->pNext = this->pFirst;
        return *this;
    }

    virtual void InsertFirst(T key) override {
        TList<T>::InsertFirst(key);
        this->pHead->pNext = this->pFirst;
    }

    virtual void InsertEnd(T key) override {
        TList<T>::InsertEnd(key);
        this->pHead->pNext = this->pFirst;
    }
};

