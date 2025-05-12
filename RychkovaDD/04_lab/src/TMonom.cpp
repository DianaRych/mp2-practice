#include "TMonom.h"

using namespace std;

int TMonom::GetConvolution(const string& pMem) {
	int i = 0;
	string newNum = "";
	char lastChar;
	double xconf = 0, yconf = 0, zconf = 0;
	int len = strlen(pMem.c_str());
	while ((pMem[i] != 'x' && pMem[i] != 'X' && pMem[i] != 'y' && pMem[i] != 'Y' && pMem[i] != 'z' && pMem[i] != 'Z') && i < len) {
		i++;

	}
	if (i == len) return 0;
	while (i < len) {
		if (pMem[i] == 'x' || pMem[i] == 'X' || pMem[i] == 'y' || pMem[i] == 'Y' || pMem[i] == 'z' || pMem[i] == 'Z') {
			lastChar = pMem[i];
			if (pMem[i + 1] == 'x' || pMem[i + 1] == 'X' || pMem[i + 1] == 'y' || pMem[i + 1] == 'Y' || pMem[i + 1] == 'z' || pMem[i + 1] == 'Z' || i + 1 == len) {
				switch (lastChar) {
				case 'x':
					xconf = 100;
					if (xconf == 0) xconf = 100;
					break;
				case 'X':
					xconf = 100;
					if (xconf == 0) xconf = 100;
					break;
				case 'y':
					yconf = 10;
					if (yconf == 0) yconf = 10;
					break;
				case 'Y':
					yconf = 10;
					if (yconf == 0) yconf = 10;
					break;
				case 'z':
					zconf = 1;
					if (zconf == 0) zconf = 1;
					break;
				case 'Z':
					zconf = 1;
					if (zconf == 0) zconf = 1;
					break;
				}
			}
			lastChar = pMem[i];
		}
		else if (pMem[i] == '^') {
			if (pMem[i] != 'x' && pMem[i] != 'X' && pMem[i] != 'y' && pMem[i] != 'Y' && pMem[i] != 'z' && pMem[i] != 'Z') {
				switch (lastChar) {
				case 'x':
					xconf = 100 * (pMem[i + 1] - '0');
					i++;
					if (xconf == 0) xconf = 100;
					break;
				case 'X':
					xconf = 100 * (pMem[i + 1] - '0');
					i++;
					if (xconf == 0) xconf = 100;
					break;
				case 'y':
					yconf = 10 * (pMem[i + 1] - '0');
					i++;
					if (yconf == 0) yconf = 10;
					break;
				case 'Y':
					yconf = 10 * (pMem[i + 1] - '0');
					i++;
					if (yconf == 0) yconf = 10;
					break;
				case 'z':
					zconf = pMem[i + 1] - '0';
					i++;
					if (zconf == 0) zconf = 1;
					break;
				case 'Z':
					zconf = pMem[i + 1] - '0';
					i++;
					if (zconf == 0) zconf = 1;
					break;
				}
			}

		}

		i++;
	}
	return xconf + yconf + zconf;
}

TMonom::TMonom() : coeff(0.0), degree(0) {}

TMonom::TMonom(const string& pMem) {
	int len = strlen(pMem.c_str());
	string newNum1 = "";

	for (int i = 0; i < len; i++) {
		if (pMem[i] != ' ' && pMem[i] != '+') {
			newNum1 += pMem[i];
		}
	}
	string pMem1 = newNum1;
	len = strlen(pMem1.c_str());
	string newNum = "";
	int i = 0;
	while ((pMem1[i] != 'x' && pMem1[i] != 'X' && pMem1[i] != 'y' && pMem1[i] != 'Y' && pMem1[i] != 'z' && pMem1[i] != 'Z') && i < len) {
		newNum += pMem1[i];
		i++;
	}

	if (newNum == "") {
		coeff = 1;
	}
	else if (newNum == "-")
		coeff = -1;
	else {
		coeff = stod(newNum);
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
	if (((this->degree / 100) + (m.degree / 100) > 9) || ((degree / 10 % 10) + (degree / 10 % 10) > 9) || ((this->degree % 100 % 10) + (m.degree % 100 % 10) > 9)) throw "error";
	TMonom res(this->coeff * m.coeff, this->degree + m.degree);
	return res;
}

TMonom TMonom::operator*(const double scalar) {
	TMonom m1(this->GetCoeff() * scalar, this->GetDegree());
	return m1;
}

double TMonom::operator()(double x, double y, double z) const {
	int x1 = degree / 100;
	int y1 = degree / 10 % 10;
	int z1 = degree % 100 % 10;
	return this->coeff * pow(x, x1) * pow(y, y1) * pow(z, z1);
}

int TMonom::GetDegree() const { return degree; }

double TMonom::GetCoeff() const { return coeff; }