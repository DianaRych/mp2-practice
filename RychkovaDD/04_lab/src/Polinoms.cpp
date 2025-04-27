#include "Polinoms.h"
#include <sstream>
#include <cmath>

string TPolinom::GetPolinom(const TPolinom& p) {
    TPolinom copy = p; // создаем полином и присваиваем ему значения полинома p
    copy.monoms.Reset(); // с помощью ресет сбрасывается итератор на первый моном в списке
    TNode<TMonom>* current = this->monoms.GetFirst(); // получаем первый моном
    string result = "";

    while (!copy.monoms.IsEnd()) {
        int degree = current->key.GetDegree();
        int x = degree / 100;
        int y = degree / 10 % 10;
        int z = degree % 100 % 10;
        double coeff = current->key.GetCoeff();

        std::stringstream monomStream; // создаем строковой поток, чтобы записать в него коэффицент и представить в виде строки
        monomStream << coeff;
        string monom = monomStream.str() + compileMonom(x, y, z); // преобразовываем monomStream в строку и вызываем compileMonom, которая приводит в порядок полином

        if (!result.empty()) { // если у нас не первый моном => результ не пустой
            if (coeff > 0) {
                result += "+" + monom; // делаем запись, чтобы была моном + моном
            }
        }
        else {
            result += monom; // если первый => просто записываем моном
        }
        current = current->pNext;
        copy.monoms.Next();
    }
    return result;
}

string TPolinom::compileMonom(int x, int y, int z) {
    std::stringstream result;
    if (x == 1) {
        result << "x";
    }
    else if (x != 0) {
        result << "x^" << x;
    }

    if (y == 1) {
        result << "y";
    }
    else if (y != 0) {
        result << "y^" << y;
    }

    if (z == 1) {
        result << "z";
    }
    else if (z != 0) {
        result << "z^" << z;
    }

    return result.str();
}

void TPolinom::CheckPolinoms(const string& monom) {
    try {
        TMonom newMonom(monom);
        this->monoms.Reset();

        bool found = false;
        TNode<TMonom>* nodeToUpdate = nullptr;

        // Ищем моном с такой же степенью
        while (!this->monoms.IsEnd()) {
            TNode<TMonom>* current = this->monoms.GetCurrent();
            if (current->key.GetDegree() == newMonom.GetDegree()) {
                nodeToUpdate = current;
                found = true;
                break;
            }
            this->monoms.Next();
        }

        if (found) {
            // Нашли моном с такой же степенью - складываем
            TMonom sum = nodeToUpdate->key + newMonom;
            if (sum.GetCoeff() == 0) {
                // Если сумма равна нулю, удаляем моном (нужно реализовать RemoveCurrent)
                // Временное решение - оставляем как есть
            }
            else {
                nodeToUpdate->key = sum;
            }
        }
        else {
            // Не нашли - добавляем новый моном
            this->monoms.InsertEnd(newMonom);
        }

        this->monoms.Reset();
    }
    catch (...) {
        // Обработка ошибок создания монома
        cerr << "Error creating monom from: " << monom << endl;
    }
}

TPolinom::TPolinom() {}

TPolinom::TPolinom(const string& polinom) {
    this->id_pol = polinom;
    string currentMonom;
    bool isNegative = false;

    for (size_t i = 0; i < polinom.length(); i++) {
        char c = polinom[i];

        // Обрабатываем знак только если это начало нового монома
        if (c == '+' || c == '-') {
            if (!currentMonom.empty()) {
                if (isNegative) {
                    currentMonom = "-" + currentMonom;
                }
                CheckPolinoms(currentMonom);
                currentMonom.clear();
            }
            isNegative = (c == '-');
        }
        else if (c != ' ') {
            currentMonom += c;
        }
    }

    // Добавляем последний моном
    if (!currentMonom.empty()) {
        if (isNegative) {
            currentMonom = "-" + currentMonom;
        }
        CheckPolinoms(currentMonom);
    }
}

TPolinom::TPolinom(const TPolinom& other) {
    this->id_pol = other.id_pol;
    ListRingHead<TMonom> l(other.monoms);
    this->monoms = l;
}

bool TPolinom::operator==(const TPolinom& other) const {
    return (this->monoms == other.monoms) && (this->id_pol == other.id_pol);
}

bool TPolinom::operator!=(const TPolinom& other) const {
    return !(*this == other);
}

const TPolinom& TPolinom::operator=(const TPolinom& other) {
    if (this == &other) return *this; // без самоприсваивания
    this->id_pol = other.id_pol;
    this->monoms = other.monoms;
    return *this;
}

TPolinom TPolinom::DiffX() {
    TPolinom result;
    this->monoms.Reset();
    TNode<TMonom>* node = this->monoms.GetFirst();

    while (!this->monoms.IsEnd()) {
        TMonom monom = node->key.DiffX();
        if (monom.GetCoeff() != 0) {
            result.monoms.InsertEnd(monom);
        }
        this->monoms.Next();
        node = this->monoms.GetCurrent();
    }
    return result;
}

TPolinom TPolinom::DiffY() {
    TPolinom result;
    this->monoms.Reset();
    TNode<TMonom>* node = this->monoms.GetFirst();

    while (!this->monoms.IsEnd()) {
        TMonom monom = node->key.DiffY();
        if (monom.GetCoeff() != 0) {
            result.monoms.InsertEnd(monom);
        }
        this->monoms.Next();
        node = this->monoms.GetCurrent();
    }
    return result;
}

TPolinom TPolinom::DiffZ() {
    TPolinom result;
    this->monoms.Reset();
    TNode<TMonom>* node = this->monoms.GetFirst();

    while (!this->monoms.IsEnd()) {
        TMonom monom = node->key.DiffZ();
        if (monom.GetCoeff() != 0) {
            result.monoms.InsertEnd(monom);
        }
        this->monoms.Next();
        node = this->monoms.GetCurrent();
    }
    return result;
}

TPolinom TPolinom::operator+(const TMonom& monom) { // полином + моном
    TPolinom result = *this;
    result.CheckPolinoms(monom.GetMonom()); // TODO: loop по мономам
    return result;
}

TPolinom TPolinom::operator+(const TPolinom& pol) { // полином + полином
    TPolinom result = *this;
    TNode<TMonom>* node = this->monoms.GetFirst();

    while (!pol.monoms.IsEnd()) {   // TODO: loop по мономам
        result.CheckPolinoms(node->key.GetMonom()); // polinom + monom
        node = node->pNext;
    }
    return result;
}

TPolinom TPolinom::operator+(double scalar) { // полином + конст
    TMonom scalarMonom(scalar, 0);
    return *this + scalarMonom;
}

TPolinom TPolinom::operator-(const TMonom& mon) {
    TMonom negativeMon(-mon.GetCoeff(), mon.GetDegree()); // создаем моном, заполняем 2 необходимых поля монома, степень и коэфф
    return *this + negativeMon;
}

TPolinom TPolinom::operator-(const TPolinom& pol) {
    TPolinom result = *this;

    // Создаем копию monoms из pol для изменения
    ListRingHead<TMonom> tempMonoms = pol.monoms;
    tempMonoms.Reset();  // Сброс итератора для работы с ним

    while (!tempMonoms.IsEnd()) {
        TNode<TMonom>* node = tempMonoms.GetCurrent();
        TMonom negativeMonom(-node->key.GetCoeff(), node->key.GetDegree());
        result.CheckPolinoms(negativeMonom.GetMonom());
        tempMonoms.Next();  // Теперь мы изменяем копию, а не оригинал
    }

    return result;
}

TPolinom TPolinom::operator-(double scalar) {
    return *this + (-scalar);
}

TPolinom TPolinom::operator*(double scalar) {
    TPolinom result;

    if (scalar == 0.0) {
        return TPolinom();
    }

    while (!monoms.IsEnd()) {
        TNode<TMonom>* node = this->monoms.GetCurrent();
        TMonom multipliedMonom(node->key.GetCoeff() * scalar, node->key.GetDegree());
        result.monoms.InsertEnd(multipliedMonom);
        node = node->pNext;
    }
    return result;
}

TPolinom TPolinom::operator*(const TMonom& monom) {
    TPolinom result;

    while (!monoms.IsEnd()) {
        TNode<TMonom>* node = this->monoms.GetCurrent();
        TMonom product = node->key * monom;
        int x = product.GetDegree() / 100;
        int y = (product.GetDegree() / 10) % 10;
        int z = product.GetDegree() % 10;

        if (x > 9 || y > 9 || z > 9) {
            throw "Error";
        }

        result.monoms.InsertEnd(product);
        node = node->pNext;
    }
    return result;
}

TPolinom TPolinom::operator*(const TPolinom& pol) {
    TPolinom result;
    this->monoms.Reset();  // Операции с оригинальным объектом

    ListRingHead<TMonom> tempMonoms = pol.monoms;  // Копия monoms для полинома
    tempMonoms.Reset();  // Сброс итератора для работы с ним

    while (!this->monoms.IsEnd()) {
        TNode<TMonom>* node1 = this->monoms.GetCurrent();
        tempMonoms.Reset();  // Сброс итератора для второго полинома

        while (!tempMonoms.IsEnd()) {
            TNode<TMonom>* node2 = tempMonoms.GetCurrent();
            TMonom product = node1->key * node2->key;
            result = result + product;
            tempMonoms.Next();  // Двигаем итератор по копии
        }
        this->monoms.Next();  // Двигаем итератор по текущему полиному
    }

    return result;
}

double TPolinom::operator()(double x, double y, double z) const {
    double result = 0.0;
    TPolinom tmp(*this);
    tmp.monoms.Reset();

    while (!tmp.monoms.IsEnd()) {
        result += tmp.monoms.GetCurrent()->key(x, y, z);
        tmp.monoms.Next();
    }

    return result;
}

ostream& operator<<(ostream& ostr, const TPolinom& pol) {
    if (pol.monoms.GetFirst() == nullptr) {
        ostr << "0";
        return ostr;
    }

    ListRingHead<TMonom> tempList = pol.monoms;
    tempList.Reset();
    bool firstTerm = true;

    while (!tempList.IsEnd()) {
        TMonom current = tempList.GetCurrent()->key;
        double coeff = current.GetCoeff();
        int degree = current.GetDegree();
        int x = degree / 100;
        int y = (degree / 10) % 10;
        int z = degree % 10;

        if (!firstTerm) {
            if (coeff > 0) {
                ostr << " + ";
            }
            else {
                ostr << " - ";
                coeff = -coeff;
            }
        }
        else if (coeff < 0) {
            ostr << "-";
            coeff = -coeff;
        }

        ostr << coeff;

        if (x > 0) {
            ostr << "x";
            if (x > 1) ostr << "^" << x;
        }
        if (y > 0) {
            ostr << "y";
            if (y > 1) ostr << "^" << y;
        }
        if (z > 0) {
            ostr << "z";
            if (z > 1) ostr << "^" << z;
        }

        firstTerm = false;
        tempList.Next();
    }

    return ostr;
}