#pragma once

#include <iostream>
#include <map>
#include "stacklist.h"
#include "stackarray.h"
#include <vector>

using namespace std;

string getPostform(const string& simpleForm); 
vector<char> getOperand(const string& simpleForm);// todo strlen
// todo сформировать список операндов
int Calculate(const string& postForm, map<char, int>& values);  // todo strlen, double
