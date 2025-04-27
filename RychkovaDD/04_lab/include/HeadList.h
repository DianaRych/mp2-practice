#pragma once

#include "TList.h"

template <typename T>
class HeadList : public TList<T> {
protected:
    TNode<T>* pHead;

public:
    // Конструктор
    HeadList() : TList<T>() {
        this->pHead = new TNode<T>();  // Создаём вспомогательный узел
        this->pHead->pNext = nullptr;  // Инициализируем pNext как nullptr
    }

    // Конструктор копирования
    HeadList(const HeadList& other) : TList<T>(other) {
        this->pHead = new TNode<T>();  // Создаём новый вспомогательный узел
        this->pHead->pNext = this->pFirst;  // Связываем его с первым элементом
    }

    // Деструктор
    ~HeadList() {
        delete this->pHead;  // Удаляем вспомогательный узел
    }

    const HeadList& operator=(const HeadList& other) {
        if (this == &other) return *this;
        TList<T>::operator=(other);
        this->pHead->pNext = this->pFirst;
        return *this;
    }

    // Вставка в начало
    virtual void InsertFirst(T key) override {
        TList<T>::InsertFirst(key);  // Вставляем в начало списка
        this->pHead->pNext = this->pFirst;  // Связываем pHead с первым элементом
    }

    // Вставка в конец
    virtual void InsertEnd(T key) override {
        TList<T>::InsertEnd(key);  // Вставляем в конец списка
        this->pHead->pNext = this->pFirst;  // Связываем pHead с первым элементом
    }
};

