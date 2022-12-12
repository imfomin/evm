#pragma once

#include <string>
using namespace std;

class Function {
public:
	virtual ~Function() {}
	virtual const string& get_name();
	virtual double operator()(double x) = 0;
	virtual void calculate() = 0;
protected:
	string name;
	double x;
};