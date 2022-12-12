#pragma once

#include <iostream>
#include <string>
#include "polynomial.hpp"

class Function {
public:
	virtual ~Function() = default;

	const std::string& get_name() {
		return *name;
	}
	virtual float operator()(float x) const = 0;

	virtual void output() const = 0;
	virtual void input() = 0;
protected:
	const std::string* name;
};

class Linear : public Function {
public:
	Linear();

	float operator()(float x) const override;

	void output() const override;
	void input() override;
private:
	float a, b;
};

class Exp : public Function {
public:
	Exp();

	float operator()(float x) const override;

	void output() const override;
	void input() override;
};

class Polynomial : public Function {
public:
	Polynomial();

	float operator()(float x) const override;

	void output() const override;
	void input() override;
private:
	rgr::polynomial polynomial;
};

extern Function* f_ptrs[];
extern size_t f_count;