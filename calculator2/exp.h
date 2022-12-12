#pragma once

#include "function.h"

class Exp : public Function {
public:
	Exp();
	void calculate();
};

extern Exp f_exp;