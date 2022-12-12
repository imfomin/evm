#pragma once

#include <iostream>
#include "Functions.hpp"
#include "Actions.hpp"

class Menu {
public:
	Menu() = delete;
	Menu(Function** functions,
		size_t count_f,
		Action** actions,
		size_t count_a) : 

		f_pointers(functions), f_count(count_f),
		a_pointers(actions), a_count(count_a) {}
	~Menu() = default;

	Function* select_function();
	Action* select_action();
private:
	Function** f_pointers;
	size_t f_count;

	Action** a_pointers;
	size_t a_count;

	int select_item(size_t count);
};
