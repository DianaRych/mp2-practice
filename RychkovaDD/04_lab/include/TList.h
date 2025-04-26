#pragma once

template <typename T>
struct TNode {
    T key;
    TNode* pNext;
    TNode() : key(), pNext(nullptr) {}
    TNode(T k, TNode* pN = nullptr) : key(k), pNext(pN) {}
};

template <typename T>
class TList {
protected:
    TNode<T>* pFirst;
    TNode<T>* pCurrent; // Каррентный элемент для навигации
    TNode<T>* pLast; // Указатель на последний 
    TNode<T>* pStop; // Конец списка
    TNode<T>* pPrev; // Предыдущий для pCurr
private:
    void clear() {
        while (this->pFirst != nullptr) {
            TNode<T>* tmp = this->pFirst;
            this->pFirst = this->pFirst->pNext;
            delete tmp;
        }
        this->pFirst = nullptr;
        this->pCurrent = nullptr;
        this->pLast = nullptr;
    }

    void copy(const TList& other) {
        this->pFirst = new TNode<T>(other.pFirst->key);
        TNode<T>* tmp = this->pFirst;
        TNode<T>* curr = other.pFirst->pNext;
        while (curr != other.pStop) {
            tmp->pNext = new TNode<T>(curr->key);
            tmp = tmp->pNext;
            curr = curr->pNext;
        }
        this->pLast = tmp;
        this->pLast->pNext = pStop;
    }

public:
    // Конструктор по умолчанию
    TList() : pFirst(nullptr), pCurrent(nullptr), pLast(nullptr), pStop(nullptr), pPrev(nullptr) {}

    // Конструктор копирования
    TList(const TList& other) : pFirst(nullptr), pCurrent(nullptr), pLast(nullptr), pStop(nullptr), pPrev(nullptr) {
        if (other.pFirst == nullptr) {
            return;
        }
        copy(other);
    }

    // Деструктор
    virtual ~TList() {
        clear();
    }

    // перегрузка присваивания
    const TList& operator=(const TList& other) {
        if (this == &other) return *this;
        clear();

        if (other.pFirst != nullptr) {
            copy(other);
        }
        else {
            pFirst = pLast = nullptr;
        }
        return *this;
    }

    // Получить первый элемент
    TNode<T>* GetFirst() const {
        return pFirst;
    }

    // Получить последний элемент
    TNode<T>* GetCurrent() const {
        return pCurrent;
    }

    // Поиск
    virtual TNode<T>* Search(T key) {
        pCurrent = pFirst;
        pPrev = nullptr;
        while (pCurrent != pStop && pCurrent->key != key) {
            pPrev = pCurrent;
            pCurrent = pCurrent->pNext;
        }
        return pCurrent;
    }

    // Вставка в конец
    virtual void InsertEnd(T key) {
        TNode<T>* tmp1 = new TNode<T>(key);
        if (pFirst == nullptr) {
            InsertFirst(key);
            return;
        }
        pLast->pNext = tmp1;
        pLast = tmp1;
        pLast->pNext = pStop;
    }

    // Вставка в начало
    virtual void InsertFirst(T key) {
        TNode<T>* tmp1 = new TNode<T>(key);
        tmp1->pNext = pFirst;
        pFirst = tmp1;
        if (pLast == nullptr) {
            pLast = pFirst;
        }
    }

    // Вставка перед элементом
    virtual void InsertBefore(T searchKey, T key) {
        Search(searchKey);
        if (pCurrent == nullptr)
        {
            throw "Element not found";
        }
        if (pCurrent == pFirst) {
            InsertFirst(key);
            return;
        }
        TNode<T>* newNode = new TNode<T>(key);
        newNode->pNext = pCurrent;
        pPrev->pNext = newNode;
    }

    // Вставка после элемента
    virtual void InsertAfter(T searchKey, T key) {
        Search(searchKey);
        if (pCurrent == nullptr) throw "Element not found";
        TNode<T>* newNode = new TNode<T>(key);
        newNode->pNext = pCurrent->pNext;
        pCurrent->pNext = newNode;
        if (pCurrent == pLast) {
            pLast = newNode;
        }
    }

    // Удаление первого элемента
    virtual void DeleteFirst() {
        if (pFirst == nullptr) throw "List is empty";
        TNode<T>* tmp = pFirst;
        pFirst = pFirst->pNext;
        delete tmp;
        if (pFirst == pStop) {
            pFirst = nullptr;
            pLast = nullptr;
        }
    }

    virtual void DeleteLast() {
        if (pFirst == nullptr) throw "List is empty";
        if (pFirst->pNext == pStop) {
            delete pFirst;
            pFirst = pLast = nullptr;
            return;
        }
        TNode<T>* tmp = pFirst;
        while (tmp->pNext != pLast) {
            tmp = tmp->pNext;
        }
        delete pLast;
        pLast = tmp;
        pLast->pNext = pStop;
    }

    // Удаление элемента по ключу
    void DeleteByKey(T key) {
        if (pFirst == nullptr) throw "List is empty";
        Search(key);
        if (pCurrent == nullptr)
        {
            throw  "Element not found";;
        }

        if (pCurrent == pFirst)
        {
            DeleteFirst();
            return;
        }
        pPrev->pNext = pCurrent->pNext;
        delete pCurrent;
    }

    void Reset() {
        this->pPrev = nullptr;
        this->pCurrent = this->pFirst;
    }

    void Next() {
        if (pCurrent == nullptr) {
            return;
        }

        if (pCurrent != pStop) {
            pPrev = pCurrent;
            pCurrent = pCurrent->pNext;
        }
    }

    bool IsEnd() const {
        return pCurrent == pStop;
    }

    bool operator==(const TList<T>& other) const {
        TNode<T>* tmp = this->pFirst;
        TNode<T>* oth = other.pFirst;
        while (tmp != this->pStop && oth != other.pStop) {
            if (oth->key != tmp->key) return 0;
            tmp = tmp->pNext;
            oth = oth->pNext;
        }
        if (oth == other.pStop && tmp == this->pStop) return 1;
        return 0;
    }
    bool operator!=(const TList<T>& other) const {
        return !(*this == other);
    }
};
