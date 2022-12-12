#include <iostream>
#include <fstream>
#include <string>
#include "Functions.hpp"

const std::string LINEAR_NAME = "ax + b";
const std::string POLYNOMIAL_NAME = "arbitrary polynomial";
const std::string EXP_NAME = "e ^ x";

Linear f_linear;
Polynomial f_pol;
Exp f_exp;
Function* f_ptrs[] = { &f_linear, &f_pol, &f_exp };
size_t f_count = 3;

// Linear

Linear::Linear() : a(0.f), b(0.f) {
	name = &LINEAR_NAME;
}

float Linear::operator()(float x) const {
	return a * x + b;
}

void Linear::input() {
	std::cout << "Enter a and b:\n";

	std::cin >> a >> b;
	while (std::cin.fail()) {
		std::cout << "input error. enter numbers" << std::endl;
		std::cin.clear();
	}
}

void Linear::output() const {
	std::cout << "y = ";

	if (a != 0) {
		if (a == -1) std::cout << '-';
		else if (a != 1) std::cout << a;
		std::cout << 'x';
	}
	else {
		std::cout << b;
		return;
	}

	if (b > 0) {
		std::cout << " + " << b;
	}
	else if (b < 0) {
		std::cout << " - " << -b;
	}
}

// Exp

Exp::Exp() {
	name = &EXP_NAME;
}

float Exp::operator ()(float x) const {
	float f_value = 1;
	const float epsilon = 1.0E-7f;

	int term_count = 1;
	float term = x;
	while ( (term >= 0 ? term : -term) >= epsilon ) {
		f_value += term;

		term_count++;
		term = term * x / term_count;
	}

	return f_value;
}

void Exp::input() {}

void Exp::output() const {
	std::cout << "y = e ^ x";
}

// polynomial
Polynomial::Polynomial() {
	name = &POLYNOMIAL_NAME;
}

float Polynomial::operator()(float x) const {
	return polynomial(x);
}

void Polynomial::output() const {
	int polynomial_deg = polynomial.deg();
	float coeff; char sign;

	if (!polynomial) {
		std::cout << '0';
		return;
	}

	for (int pow = polynomial_deg; pow >= 0; pow--) {
		coeff = polynomial[pow];
		if (coeff == 0) continue;

		if (coeff > 0) { sign = '+'; }
		else		   { sign = '-', coeff = -coeff; };

		if (pow == polynomial_deg) {
			if (sign == '-') std::cout << sign;
		}
		else {
			std::cout << ' ' << sign << ' ';
		}

		if (pow == 0) std::cout << coeff;
		if (pow != 0) {
			if (coeff != 1) std::cout << coeff;
			std::cout << "x";
			if (pow != 1) std::cout << "^" << pow;
		}
	}
}

void Polynomial::input() {
	std::cout << "Enter the polynomial in format : [ +(-) 0 : a0 +(-) 1 : a1 ...]\n";
	
	std::cin >> polynomial;
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin >> polynomial;
	}
}