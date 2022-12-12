#include <iostream>
#include "Functions.hpp"
#include "Menu.hpp"

int Menu::select_item(size_t count) {
	int index;
	while (true) {
		std::cin >> index;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cout << "Error: you should enter a number\n";
			continue;
		}

		if (index >= 0 && index <= count) {
			return index;
		}
		else {
			std::cout << "Error: you have to enter number from 0 to " << count << '\n';
			std::cin.clear();
		}
	}
}

Function* Menu::select_function() {
	std::cout << "==========================================\n";
	std::cout << "Choose one of the functions:\n";
	
	for (int i = 0; i < f_count; i++) {
		std::cout << i + 1 << ". " << f_pointers[i]->get_name() << '\n';
	}
	std::cout << "0. Exit\n";
	std::cout << "==========================================\n";

	int choice = select_item(f_count);

	if (choice) return f_pointers[choice - 1];
	else return nullptr;
}

Action* Menu::select_action() {
	std::cout << "==========================================\n";
	std::cout << "Choose one of the actions:\n";

	for (int i = 0; i < a_count; i++) {
		std::cout << i + 1 << ". " << a_pointers[i]->get_name() << '\n';
	}
	std::cout << "0. Exit (get back to choose function)\n";
	std::cout << "==========================================\n";

	int choice = select_item(a_count);

	if (choice) return a_pointers[choice - 1];
	else return nullptr;
}