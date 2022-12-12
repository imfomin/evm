#pragma once

#include <iostream>
#include <string>
#include "Functions.hpp"

class Action {
public:
	virtual ~Action() = default;

	virtual void perform(Function* f) = 0;
	const std::string& get_name() {
		return *name;
	}
protected:
	const std::string* name;
};

class Calculation : public Action {
public:
	Calculation();
	void perform(Function* f) override;
};

class Tabulation : public Action {
public:
	Tabulation();
	void perform(Function* f) override;
private:
	float left, right, step;

	void input();
};

extern Calculation a_calc;
extern Tabulation a_tab;
extern Action* a_ptrs[];
extern size_t a_count;
