#include "TMonom.h"

double TMonom::GetConvolution(const std::string& pMem) {
	double xCoef = 0, yCoef = 0, zCoef = 0;

	for (size_t i = 0; i < pMem.length(); i++) {
		char c = tolower(pMem[i]);

		if (c == 'x') {
			if (i + 1 < pMem.length() && pMem[i + 1] == '^') {
				if (i + 2 < pMem.length() && isdigit(pMem[i + 2])) {
					xCoef = 100 * (pMem[i + 2] - '0');
					i += 2;
				}
			}
			else {
				xCoef = 100; // степень 1
			}
		}
		else if (c == 'y') {
			if (i + 1 < pMem.length() && pMem[i + 1] == '^') {
				if (i + 2 < pMem.length() && isdigit(pMem[i + 2])) {
					yCoef = 10 * (pMem[i + 2] - '0');
					i += 2;
				}
			}
			else {
				yCoef = 10; // степень 1
			}
		}
		else if (c == 'z') {
			if (i + 1 < pMem.length() && pMem[i + 1] == '^') {
				if (i + 2 < pMem.length() && isdigit(pMem[i + 2])) {
					zCoef = (pMem[i + 2] - '0');
					i += 2;
				}
			}
			else {
				zCoef = 1; // степень 1
			}
		}
	}

	return xCoef + yCoef + zCoef;
}


TMonom::TMonom(const string& pMem) {
	int len = std::strlen(pMem.c_str());
	std::string newNum1 = "";

	for (int i = 0; i < len; i++) {
		if (pMem[i] != ' ' && pMem[i] != '+') {
			newNum1 += pMem[i];
		}
	}

	std::string pMem1 = newNum1;
	len = std::strlen(pMem1.c_str());
	std::string newNum = "";
	int i = 0;
	while ((pMem1[i] != 'x' && pMem1[i] != 'X' && pMem1[i] != 'y' && pMem1[i] != 'Y' && pMem1[i] != 'z' && pMem1[i] != 'Z') && i < len) {
		newNum += pMem1[i];
		i++;
	}
	if (newNum == "") {
		coeff = 1;
	}
	else {
		coeff = std::stod(newNum);
	}
	degree = GetConvolution(pMem1);
}

TMonom::TMonom(const TMonom& mon) {
	this->coeff = mon.coeff;
	this->degree = mon.degree;
}

TMonom::TMonom(const double coeff, const int degree) {
	int x = degree / 100;
	int y = degree / 10 % 10;
	int z = degree % 100 % 10;
	if (x < 0 || x > 9 || y < 0 || y > 9 || z < 0 || z > 9) throw "error";
	this->coeff = coeff;
	this->degree = degree;
}

bool TMonom::operator==(const TMonom& m) const {
	if (this == nullptr || &m == nullptr) return false;  // Handle null cases
	return (this->degree == m.degree);
}

bool TMonom::operator!=(const TMonom& m) const {
	return !(*this == m);
}

bool TMonom::operator>(const TMonom& m) const {
	if (m.degree == this->degree) return this->coeff > m.coeff;
	return this->degree > m.degree;
}

bool TMonom::operator<(const TMonom& m) const {
	if (m.degree == this->degree) return this->coeff < m.coeff;
	return this->degree < m.degree;
}

bool TMonom::operator>=(const TMonom& m) const {
	return !(*this < m);
}

bool TMonom::operator<=(const TMonom& m) const {
	return !(*this > m);
}

TMonom TMonom::operator+(const TMonom& m) {
	if (this->degree != m.degree) throw "error";
	TMonom res(this->coeff + m.coeff, this->degree);
	return res;
}

TMonom TMonom::operator-(const TMonom& m) {
	if (this->degree != m.degree) throw "error";
	TMonom res(this->coeff - m.coeff, this->degree);
	return res;
}

TMonom TMonom::operator*(const TMonom& m) {
	if (((this->degree / 100) + (m.degree / 100) > 9) || ((degree / 10 % 10) + (m.degree / 10 % 10) > 9) || ((this->degree % 100 % 10) + (m.degree % 100 % 10) > 9)) throw "error";
	TMonom res(this->coeff * m.coeff, this->degree + m.degree);
	return res;
}

double TMonom::operator()(double x, double y, double z) const {
	int x1 = degree / 100;
	int y1 = degree / 10 % 10;
	int z1 = degree % 100 % 10;
	return this->coeff * std::pow(x1, x) * std::pow(y1, y) * std::pow(z1, z);
}

int TMonom::GetDegree() const {
	if (this == nullptr) return 0;
	return degree;
}
double TMonom::GetCoeff() const { return coeff; }

TMonom TMonom::DiffX() const {
	int xDegree = degree / 100;
	int yDegree = (degree / 10) % 10;
	int zDegree = degree % 10;

	if (xDegree == 0) {
		return TMonom(0, degree);
	}

	double newCoeff = coeff * xDegree;
	int newDegree = (xDegree - 1) * 100 + yDegree * 10 + zDegree;

	return TMonom(newCoeff, newDegree);
}

TMonom TMonom::DiffY() const {
	int xDegree = degree / 100;
	int yDegree = (degree / 10) % 10;
	int zDegree = degree % 10;

	if (yDegree == 0) {
		return TMonom(0, degree);
	}

	double newCoeff = coeff * yDegree;
	int newDegree = xDegree * 100 + (yDegree - 1) * 10 + zDegree;

	return TMonom(newCoeff, newDegree);
}

TMonom TMonom::DiffZ() const {
	int xDegree = degree / 100;
	int yDegree = (degree / 10) % 10;
	int zDegree = degree % 10;

	if (zDegree == 0) {
		return TMonom(0, degree);
	}

	double newCoeff = coeff * zDegree;
	int newDegree = xDegree * 100 + yDegree * 10 + (zDegree - 1);

	return TMonom(newCoeff, newDegree);
}

string TMonom::GetMonom() const {
	std::stringstream result;

	if (coeff != 1 && coeff != -1) {
		result << coeff;
	}
	else if (coeff == -1) {
		result << "-";
	}

	int xDegree = degree / 100;
	if (xDegree > 0) {
		if (xDegree == 1) result << "x";
		else result << "x^" << xDegree;
	}

	int yDegree = (degree / 10) % 10;
	if (yDegree > 0) {
		if (yDegree == 1) result << "y";
		else result << "y^" << yDegree;
	}

	int zDegree = degree % 10;
	if (zDegree > 0) {
		if (zDegree == 1) result << "z";
		else result << "z^" << zDegree;
	}

	return result.str();
}