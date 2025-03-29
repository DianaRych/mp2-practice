#include "postform.h"
#include <map>


//#define USE_ARRAY

#ifndef USE_ARRAY

string getPostform(const string& simpleForm) {

	TStackList<char> s1;
	TStackList<char> s2;
	char stakItem;
	for (int i = 0; i < strlen(simpleForm.c_str()); i++) {
		if (simpleForm[i] == '+' || simpleForm[i] == '-') {
			try {
				if (s2.Top() == '/' || s2.Top() == '*') {
					while (s2.Top() == '/' || s2.Top() == '*') {
						s1.push(s2.Top());
						s2.pop();
					}
					s2.push(simpleForm[i]);
				}

		else {
			s2.push(simpleForm[i]);
		}
			}
			catch (const char* error) {
				s2.push(simpleForm[i]);

		}
		}
		else if (simpleForm[i] == '*' || simpleForm[i] == '/') {
			s2.push(simpleForm[i]);

		}
		else if (simpleForm[i] == '(') s2.push(simpleForm[i]);
		else if (simpleForm[i] == ')') {
			stakItem = s2.Top();
			s2.pop();
			while (s2.Top() != '(') {
				s1.push(stakItem);

				stakItem = s2.Top();
				s2.pop();
			}
			s1.push(stakItem);
			s2.pop();
		}
		else {
			s1.push(simpleForm[i]);
		}
	}
	while (!s2.isEmpty()) {
		s1.push(s2.Top());
		s2.pop();
	}
	string newForm = "";
	while (!s1.isEmpty()) {
		newForm = s1.Top() + newForm;
		s1.pop();
	}
	return newForm;

}
vector<char> getOperand(const string& simpleForm) {
	vector<char> v;
	for (int i = 0; i < strlen(simpleForm.c_str()); i++) {
		if (simpleForm[i] != '+' && simpleForm[i] != '*' && simpleForm[i] != '/' && simpleForm[i] != '-') {
			int j = 0;
			bool f = false;
			for (int j = 0; j < v.size(); j++) {
				if (v[j] == simpleForm[i]) {
					f = true;
					break;
				}
			}
			if (f == false) {
				v.push_back(simpleForm[i]);
			}
		}

	}
	return v;

}
int Calculate(const string& postForm, map<char, int>& values) {

	TStackList<char> s1;

	for (int i = 0; i < strlen(postForm.c_str()); i++) {
		if (postForm[i] == '+') {
			char num2 = s1.Top();
			s1.pop();
			char num1 = s1.Top();
			s1.pop();
			int k = (values[num1] + values[num2]);
			s1.push(k);
			values.insert({ k, k });
		}
		else if (postForm[i] == '*') {
			char num2 = s1.Top();
			s1.pop();
			char num1 = s1.Top();
			s1.pop();
			int k = (values[num1] * values[num2]);
			s1.push(k);
			values.insert({ k, k });
		}
		else if (postForm[i] == '/') {
			char num2 = s1.Top();
			s1.pop();
			char num1 = s1.Top();
			s1.pop();
			int k = (values[num1] / values[num2]);
			s1.push(k);
			values.insert({ k, k });
		}
		else if (postForm[i] == '-') {
			char num2 = s1.Top();
			s1.pop();
			char num1 = s1.Top();
			s1.pop();
			int k = (values[num1] - values[num2]);
			s1.push(k);
			values.insert({ k, k });
		}
		else {
			s1.push(postForm[i]);
		}
	}
	return (int)s1.Top();
}

#else
string getPostform(const string& simpleForm, int n) {

	TStackArray<char> s1(n);
	TStackArray<char> s2(n);
	char stakItem;
	for (int i = 0; i < strlen(simpleForm.c_str()); i++) {
		if (simpleForm[i] == '+' || simpleForm[i] == '-') {
			try {
				if (s2.Top() == '/' || s2.Top() == '*') {
					while (s2.Top() == '/' || s2.Top() == '*') {
						s1.push(s2.Top());
						s2.pop();
					}
					s2.push(simpleForm[i]);
				}

				else {
					s2.push(simpleForm[i]);
				}
			}
			catch (const char* error) {
				s2.push(simpleForm[i]);

			}
		}
		else if (simpleForm[i] == '*' || simpleForm[i] == '/') {
			s2.push(simpleForm[i]);

		}
		else if (simpleForm[i] == '(') s2.push(simpleForm[i]);
		else if (simpleForm[i] == ')') {
			stakItem = s2.Top();
			s2.pop();
			while (s2.Top() != '(') {
				s1.push(stakItem);

				stakItem = s2.Top();
				s2.pop();
			}
			s1.push(stakItem);
			s2.pop();
		}
		else {
			s1.push(simpleForm[i]);
		}
	}
	while (!s2.isEmpty()) {
		s1.push(s2.Top());
		s2.pop();
	}
	string newForm = "";
	while (!s1.isEmpty()) {
		newForm = s1.Top() + newForm;
		s1.pop();
	}
	return newForm;

}
vector<char> getOperand(const string& simpleForm) {
	vector<char> v;
	for (int i = 0; i < strlen(simpleForm.c_str()); i++) {
		if (simpleForm[i] != '+' && simpleForm[i] != '*' && simpleForm[i] != '/' && simpleForm[i] != '-') {
			int j = 0;
			bool f = false;
			for (int j = 0; j < v.size(); j++) {
				if (v[j] == simpleForm[i]) {
					f = true;
					break;
				}
			}
			if (f == false) {
				v.push_back(simpleForm[i]);
			}
		}

	}
	return v;

}
int Calculate(const string& postForm, int n, map<char, int>& values) {

	TStackArray<char> s1(n);

	for (int i = 0; i < n; i++) {
		if (postForm[i] == '+') {
			char num2 = s1.Top();
			s1.pop();
			char num1 = s1.Top();
			s1.pop();
			int k = (values[num1] + values[num2]);
			s1.push(k);
			values.insert({ k, k });
		}
		else if (postForm[i] == '*') {
			char num2 = s1.Top();
			s1.pop();
			char num1 = s1.Top();
			s1.pop();
			int k = (values[num1] * values[num2]);
			s1.push(k);
			values.insert({ k, k });
		}
		else if (postForm[i] == '/') {
			char num2 = s1.Top();
			s1.pop();
			char num1 = s1.Top();
			s1.pop();
			int k = (values[num1] / values[num2]);
			s1.push(k);
			values.insert({ k, k });
		}
		else if (postForm[i] == '-') {
			char num2 = s1.Top();
			s1.pop();
			char num1 = s1.Top();
			s1.pop();
			int k = (values[num1] - values[num2]);
			s1.push(k);
			values.insert({ k, k });
		}
		else {
			s1.push(postForm[i]);
		}
	}
	return (int)s1.Top();
}




#endif // !USE_LIST