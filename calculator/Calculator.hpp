#pragma once

#include "Functions.hpp"
#include "Actions.hpp"
#include "Menu.hpp"
#include "Calculator.hpp"

class Calculator {
public:
	Calculator();
	~Calculator() = default;

	void run();
private:
	Menu c_menu;
};