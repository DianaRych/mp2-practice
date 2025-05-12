#pragma once

#include "TMonom.h"
#include "TList.h"
#include "HeadRingList.h"
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

class Polynomial {
private:
    ListRingHead<TMonom> terms;
    string polyString;

    void UpdateStringForm();
    void AddTerm(const TMonom& term);
    string BuildTermString(int x, int y, int z);

public:
    Polynomial();
    Polynomial(const string& input);
    Polynomial(const Polynomial& other);

    bool operator==(const Polynomial& other) const;
    bool operator!=(const Polynomial& other) const;
    const Polynomial& operator=(const Polynomial& other);

    Polynomial DifferentiateX() const;
    Polynomial DifferentiateY() const;
    Polynomial DifferentiateZ() const;

    Polynomial operator+(const TMonom& term) const;
    Polynomial operator+(const Polynomial& other) const;
    Polynomial operator+(double constant) const;

    Polynomial operator-(const TMonom& term) const;
    Polynomial operator-(const Polynomial& other) const;
    Polynomial operator-(double constant) const;

    Polynomial operator*(double factor) const;
    Polynomial operator*(const TMonom& term) const;
    Polynomial operator*(const Polynomial& other) const;

    double operator()(double x, double y, double z) const;

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
};