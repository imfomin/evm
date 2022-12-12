#include "exp.h"
#include <iostream>
using namespace std;

Exp::Exp() {
	name = "e ^ x";
}

void Exp::calculate() {
	cout << "Calculation for function y = " << name << endl;
	cout << "Enter x: "; cin >> x;
	cout << "y = " << (*this)(x) << endl;
}
