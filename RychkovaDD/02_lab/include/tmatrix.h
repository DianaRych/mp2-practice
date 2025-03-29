// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cassert>
using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz <= 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE) throw out_of_range("Size more max size");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      this->sz = v.sz;
      this->pMem = new T[this->sz];
      for (int i = 0; i < this->sz; i++) {
          this->pMem[i] = v.pMem[i];
      }
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v) return *this;
      if (this->sz != v.sz)
      {
          this->sz = v.sz;
          delete[]pMem;
          this->pMem = new T[this->sz];
      }
      for (int i = 0; i < this->sz; i++) {
          this->pMem[i] = v.pMem[i];
      }
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if(ind >= sz || ind < 0) throw "Index error";
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz || ind < 0) throw "Index error";
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (this->sz != v.sz) return 0;
      for (int i = 0; i < this->size(); i++) {
          if (this->pMem[i] != v.pMem[i]) return 0;
      }
      return 1;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector t1(this -> size());
      for (int i = 0; i < this->size(); i++) {
          t1.pMem[i] = this->pMem[i] + val;
      }
      return t1;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector t1(this->size());
      for (int i = 0; i < this->size(); i++) {
          t1.pMem[i] = this->pMem[i] - val;
      }
      return t1;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector t1(this->size());
      for (int i = 0; i < this->size(); i++) {
          t1[i] = this->pMem[i] * val;
      }
      return t1;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (this->size() != v.size()) throw range_error("Wrong size");
      TDynamicVector t1(this->size());
      for (int i = 0; i < this->size(); i++) {
          t1.pMem[i] = this->pMem[i] + v.pMem[i];
      }
      return t1;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (this->size() != v.size()) throw range_error("Wrong size");
      TDynamicVector t1(this->size());
      for (int i = 0; i < this->size(); i++) {
          t1.pMem[i] = this->pMem[i] - v.pMem[i];
      }
      return t1;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (this->size() != v.size()) throw range_error("Wrong size");
      T a(0);
      for (int i = 0; i < this->size(); i++) {
          a += this->pMem[i] * v.pMem[i];
      }
      return a;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.size(), rhs.size());
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.size(); i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.size(); i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (s > MAX_MATRIX_SIZE) throw "Error";
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz-i);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  int size() const { return sz; }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      return TDynamicVector<TDynamicVector<T>>::operator==(m);
  }
  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      return TDynamicVector<TDynamicVector<T>>::operator!=(m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix m1(this->size());
      for (int i = 0; i < this->size(); i++) {
          m1[i] = this->pMem[i] * val;
      }
      return m1;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (this->size() != v.size()) throw "Range error";
      TDynamicVector<T> v1(this->size());
      for (int i = 0; i < this->size(); i++) {
          for (int j = 0; j <= i; j++) {
              v1[i] += this->pMem[j][i-j] * v[j];
          }
      }
      return v1;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (this->size() != m.size()) throw "error";
      TDynamicMatrix m1(this->size());
      for (int i = 0; i < this->size(); i++) {
          for (int j = 0; j < this->size()-i; j++) {
              m1[i][j] = this->pMem[i][j] + m[i][j];
          }
      }
      
      return m1;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m) 
  {
      if (this->size() != m.size()) throw "error";
      TDynamicMatrix m1(this->size());
      for (int i = 0; i < this->size(); i++) {
          m1[i] = this->pMem[i] - m[i];
      }
      return m1;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (this->size() != m.size()) throw "error";
      TDynamicMatrix m1(this->size());
      for (int i = 0; i < this->size(); i++) {
          for (int j = 0; j < this->size()-i; j++) {
              for (int k = 0; k <= j; k++) {
                  m1[i][j] += this->pMem[i][k] * m[i+k][j-k];
              }
          }
      }
      return m1;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (int i = 0; i < v[0].size(); i++) {
          for (int j = i; j < v[0].size(); j++) {
              istr >> v[i][j];
          }
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      ostr << endl;
      for (int i = 0; i < v.size(); i++) {
          for (int k = 0; k < i; k++) {
              ostr << "\t";
          }
          for (int j = 0; j < v.size()-i; j++) {
              ostr << v[i][j]<< "\t";
          }
          ostr << endl;
      }
      return ostr;
  }
};

#endif
