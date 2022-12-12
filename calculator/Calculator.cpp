#include <iostream>
#include "Functions.hpp"
#include "Actions.hpp"
#include "Menu.hpp"
#include "Calculator.hpp"

Calculator::Calculator() : c_menu(f_ptrs, f_count, a_ptrs, a_count) {}

void Calculator::run() {
	Function* function;
	Action* action;

	std::cout << "\n";
	std::cout << "Functional calculator is working...\n";
	std::cout << "\n";

	while (function = c_menu.select_function()) {
		function->input();
		std::cout << "Your function is ";
		function->output(); 
		std::cout << '\n';

		action = c_menu.select_action();
		if (action == nullptr) continue;

		action->perform(function);
	}
}