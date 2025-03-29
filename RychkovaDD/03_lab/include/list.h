#pragma once

template <typename T>
struct TNode {
	T key;
	TNode* pNext;
	TNode(T k) : key(k), pNext(nullptr) {}

};

template <typename T>
class TList {
private:
	TNode<T>* pFirst;
public:
	TList() :pFirst(nullptr) {}
	TList(const TList& other) : pFirst(nullptr) {
		if (other.pFirst == nullptr) {
			return;
		}
		pFirst = new TNode<T>(other.pFirst->key);
		TNode<T>* tmp = pFirst;
		TNode<T>* curr = other.pFirst->pNext;
		while (curr != nullptr) {
			tmp->pNext = new TNode<T>(curr->key);
			tmp = tmp->pNext;
			curr = curr->pNext;
		}
	}
	~TList() {
		while (pFirst != nullptr) {
			TNode<T>* tmp = pFirst;
			pFirst = pFirst->pNext;
			delete tmp;
		}
	}
	TNode<T>* Search(T key) {
		if (this->pFirst == nullptr) throw "First element is null";
		TNode<T>* tmp = pFirst;
		while (tmp != nullptr && tmp->key != key) { 
			tmp = tmp->pNext;
		}
		return tmp;

	}
	void InsertEnd(T key) { 
		TNode<T>* tmp1 = new TNode<T>(key);
		if (pFirst == nullptr) {
			pFirst = tmp1;
			return;
		}
		TNode<T>* tmp = this->pFirst;
		while (tmp->pNext != nullptr) {
			tmp = tmp->pNext;
		}
		tmp->pNext = tmp1;

	}
	void InsertBefore(T searchKey, T key) {
		TNode<T>* tmp1 = new TNode<T>(key);
		if (pFirst == nullptr) {
			pFirst = tmp1;
			return;
		}
		TNode<T>* tmp = this->pFirst;
		while (tmp->pNext != nullptr && tmp->pNext->key != searchKey) { 
			tmp = tmp->pNext;
		}
		TNode<T>* findElem = tmp->pNext;
		tmp->pNext = tmp1;
		tmp1->pNext = findElem;

	}
	void InsertAfter(T searchKey, T key) { 
		TNode<T>* tmp1 = new TNode<T>(key);
		if (pFirst == nullptr) {
			pFirst = tmp1;
			return;
		}
		TNode<T>* tmp = this->pFirst;
		while (tmp != nullptr && tmp->key != searchKey) { 
			tmp = tmp->pNext;
		}
		TNode<T>* findElem = tmp->pNext;
		tmp->pNext = tmp1;
		tmp1->pNext = findElem;

	}
	void InsertFirst(T key) {
		TNode<T>* tmp1 = new TNode<T>(key);
		if (pFirst == nullptr) {
			pFirst = tmp1;
			return;
		}
		TNode<T>* tmp = this->pFirst;
		tmp1->pNext = tmp;
		this->pFirst = tmp1;

	}
	TNode<T>* GetLast() const {
		if (pFirst == nullptr) return nullptr;
		TNode<T>* tmp = pFirst;

		while (tmp->pNext != nullptr) {
			tmp = tmp->pNext;
		}
		return tmp;

	}
	TNode<T>* GetFirst() const { return this->pFirst;}

	void DeleteLast() {
		if (pFirst == nullptr)
			throw "List is empty";

		if (pFirst->pNext == nullptr) {
			delete pFirst;
			pFirst = nullptr;
			return;
		}

		TNode<T>* tmp = pFirst;
		while (tmp->pNext->pNext != nullptr) {
			tmp = tmp->pNext;
		}

		delete tmp->pNext;
		tmp->pNext = nullptr;
	}
	void DeleteFirst() {
		if (pFirst == nullptr)
			return ;

		if (pFirst->pNext == nullptr) {
			delete pFirst;
			pFirst = nullptr;
			return;
		}

		TNode<T>* tmp = pFirst->pNext;
		delete pFirst;
		this->pFirst = tmp;
	}

};


