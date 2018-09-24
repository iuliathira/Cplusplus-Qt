#pragma once
#include <string>
#include "domain.h"
#include <vector>
using namespace std;

class ValidateException
{
	//vector<string> msgs;
	string msgs;
public:
	//ValidateException(const vector<string>& errors) :msgs{ errors } {}
	//vector<string> getMsg()const { return msgs; }
	//friend ostream& operator<<(ostream& out, const ValidateException& ex);
	ValidateException(const string& errors) :msgs{ errors } {}
	string getMsg()const { return msgs; }
	friend ostream& operator<<(ostream& out, const ValidateException& ex);
};
ostream& operator<<(ostream& out, const ValidateException& ex);

class DisciplinaValidator {
public:
	void validate(const Disciplina& p);
};
