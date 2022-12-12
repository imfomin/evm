#include <iostream>
#include <iomanip>
#include <string>
#include "Functions.hpp"
#include "Actions.hpp"

const std::string& CALCULATION_NAME = "Calculate";
const std::string& TABULATION_NAME = "Tabulate";

Calculation a_calc;
Tabulation a_tab;
Action* a_ptrs[] = { &a_calc, &a_tab };
size_t a_count = 2;

// Calculation

Calculation::Calculation() {
	name = &CALCULATION_NAME;
}

void Calculation::perform(Function* f) {
	float x;
	std::cout << "Enter x:\n";
	std::cin >> x;
	while (std::cin.fail()) {
		std::cout << "input error. you should enter a number\n";
		std::cin.clear();
		std::cin >> x;
	}

	std::cout << "y(" << x << ") = " << (*f)(x) << '\n';
}

// Tabulation

Tabulation::Tabulation() : left(0), right(0), step(0) {
	name = &TABULATION_NAME;
}

void Tabulation::input() {
	std::cout << "Enter bounds of tabulation:\n";
	std::cin >> left >> right;

	while (std::cin.fail()) {
		std::cout << "input error. enter two numbers\n";
		std::cin.clear();

		std::cin >> left >> right;
	}

	std::cout << "Enter step of tabulation:\n";
	std::cin >> step;

	while (std::cin.fail()) {
		std::cout << "input error. enter a number\n";
		std::cin.clear();

		std::cin >> step;
	}
}

void Tabulation::perform(Function* f) {
	input();

	std::cout << "          x                  y(x)         \n";
	std::cout << "------------------------------------------\n";

	int pr = std::cout.precision();
	auto inc = [pr](float& x, float step) {
		for (int i = 0; i < pr; i++) {
			x *= 10;
			step *= 10;
		}
		x += step;
		for (int i = 0; i < pr; i++) {
			x /= 10;
		}
	};

	for (float x = left; x < right + step; inc(x, step)) {
		// std::cout.setf(std::ios::fixed);
		std::cout << std::setw(19) << x;

		// std::cout.unsetf(std::ios::fixed);
		std::cout << std::setw(19) << (*f)(x);

		std::cout << '\n';
	}

	std::cout << "------------------------------------------\n";
}