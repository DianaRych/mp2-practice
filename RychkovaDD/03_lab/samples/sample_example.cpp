// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "postform.h"
//---------------------------------------------------------------------------

int main() {
	setlocale(LC_ALL, "Russian");
	char* st = "(A-C)*T"; 
	cout << "Обычная форма: " << st << endl;
	int n = strlen(st);
	string a;
	//char* a = new char[n];
	a = getPostform(st);
	cout << "Постфиксная форма: " << a << endl;;
	cout <<"\n" << endl;
	map<char, int> s;
	vector<char> v = getOperand(a);
	for (int i = 0; i < v.size(); i++) {
		int d;
		cout << "Введите значение для элемента " << v[i] << ":" << endl;
		cin >> d;
		s[v[i]]= d;
	}
	cout <<"Ответ: "<< Calculate(a,s) << endl;
	

	
}