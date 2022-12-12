#include <iostream>
#include <fstream>
#include "polynomial.hpp"

using namespace rgr;

void polynomial::alloc(int _count_terms) {
	Terms = new Term[_count_terms];
	count_terms = _count_terms;
}

polynomial::polynomial(float number) {
	alloc(1);
	Terms->coefficient = number;
	Terms->power = 0;
}
polynomial::polynomial(const polynomial& other) {
	alloc(other.count_terms);

	for (int i = 0; i < count_terms; i++) {
		Terms[i] = other.Terms[i];
	}
}
polynomial::polynomial(polynomial&& other) noexcept {
	Terms = other.Terms;
	count_terms = other.count_terms;

	other.Terms = nullptr;
	other.count_terms = 0;
}

void polynomial::clear() {
	if (Terms) {
		delete[] Terms;
		Terms = nullptr;
	}
	count_terms = 0;
}

// перегрузка операторов
polynomial& polynomial::operator =(const polynomial& other) {
	if (this == &other) return *this;

	if (count_terms != other.count_terms) {
		clear();
		alloc(other.count_terms);
	}

	for (int i = 0; i < count_terms; i++) {
		Terms[i] = other.Terms[i];
	}

	return *this;
}
polynomial& polynomial::operator =(polynomial&& other) noexcept {
	if (this == &other) return *this;

	Terms = other.Terms;
	count_terms = other.count_terms;

	other.Terms = nullptr;
	other.count_terms = 0;

	return *this;
}

// нахождение значения многочлена при заданном x
float polynomial::operator ()(float x) const {
	float eval = 0;
	float term_value;

	for (Term _term : *this) {
		term_value = _term.coefficient;
		for (int i = 0; i < _term.power; i++) {
			term_value *= x;
		}

		eval += term_value;
	}

	return eval;
}

// возвращает коэффициент при заданной степени
float polynomial::operator [](int power) const {
	if (power < 0) return 0;

	for (Term _term : *this) {
		if (_term.power == power) {
			return _term.coefficient;
		}
	}

	return 0;
}

polynomial::operator bool() const {
	return count_terms;
}

polynomial polynomial::operator +(const polynomial& added) const {
	polynomial sum;

	if (count_terms == 0) {
		sum = added;
		return sum;
	}
	if (added.count_terms == 0) {
		sum = *this;
		return sum;
	}

	auto max = [](int a, int b) { return a > b ? a : b; };
	int max_power = max(deg(), added.deg());

	Term* sum_terms = new Term[max_power + 1];
	int count_sum_terms = 0;

	float pow_coeff;
	for (int pow = 0; pow <= max_power; pow++) {
		pow_coeff = (*this)[pow] + added[pow];

		if (pow_coeff == 0) continue;

		sum_terms[count_sum_terms].coefficient = pow_coeff;
		sum_terms[count_sum_terms].power = pow;
		count_sum_terms++;
	}

	if (count_sum_terms == 0) {
		delete[] sum_terms;
	}
	else {
		sum.Terms = sum_terms;
		sum.count_terms = count_sum_terms;
	}

	return sum;
}

polynomial polynomial::operator -() const {
	polynomial negative;
	negative.alloc(count_terms);

	for (int i = 0; i < count_terms; i++) {
		negative.Terms[i].coefficient = -Terms[i].coefficient;
		negative.Terms[i].power = Terms[i].power;
	}

	return negative;
}
polynomial polynomial::operator -(const polynomial& subbed) const {
	polynomial dif;

	if (count_terms == 0) {
		dif = -subbed;
		return dif;
	}
	if (subbed.count_terms == 0) {
		dif = *this;
		return dif;
	}

	auto max = [](int a, int b) { return a > b ? a : b; };
	int max_power = max(deg(), subbed.deg());

	Term* dif_terms = new Term[max_power + 1];
	int count_dif_terms = 0;

	float pow_coeff;
	for (int pow = 0; pow <= max_power; pow++) {
		pow_coeff = (*this)[pow] - subbed[pow];

		if (pow_coeff == 0) continue;

		dif_terms[count_dif_terms].coefficient = pow_coeff;
		dif_terms[count_dif_terms].power = pow;
		count_dif_terms++;
	}

	if (count_dif_terms == 0) {
		delete[] dif_terms;
	}
	else {
		dif.Terms = dif_terms;
		dif.count_terms = count_dif_terms;
	}


	return dif;
}

polynomial polynomial::operator *(const polynomial& multed) const {
	polynomial prod;

	if (count_terms == 0 || multed.count_terms == 0) return prod;

	int max_power = deg() + multed.deg();

	Term* temp_terms = new Term[max_power + 1];
	int prod_terms = 0;

	float pow_coeff;
	for (int pow = 0; pow <= max_power; pow++) {
		pow_coeff = 0;

		/* коэффициент при слагаемом степени pow в произведении
		равен сумме произведений коэффициентов всех слагаемых многочленов-множителей
		со степенями pow1, pow2 такими, что pow1 + pow2 = pow */

		int pow1, pow2;
		for (pow1 = 0, pow2 = pow; pow1 <= pow; pow1++, pow2--) {
			pow_coeff += (*this)[pow1] * multed[pow2];
		}

		if (pow_coeff == 0) continue;

		temp_terms[prod_terms].coefficient = pow_coeff;
		temp_terms[prod_terms].power = pow;
		prod_terms++;
	}

	prod.Terms = temp_terms;
	prod.count_terms = prod_terms;

	return prod;
};

polynomial polynomial::operator /(const polynomial& divisor) const {
	if (deg() < divisor.deg()) return polynomial();

	// будущий остаток от деления
	polynomial remainder(*this);

	// будущее неполное частное
	polynomial quot;
	polynomial quot_term;
	quot_term.alloc(1);

	// степень остатка (будет уменьшаться)
	int remainder_deg = remainder.deg();
	// степень делителя
	int devisor_deg = divisor.deg();
	// коэффициент при старшей степени делителя
	float devisor_deg_coeff = divisor[devisor_deg];

	// деление, аналогичное делению в столбик
	while (remainder_deg >= devisor_deg) {
		quot_term.Terms->power = remainder_deg - devisor_deg;
		quot_term.Terms->coefficient = remainder[remainder_deg] / devisor_deg_coeff;

		quot = quot + quot_term;

		remainder = remainder - quot_term * divisor;
		remainder_deg = remainder.deg();
	}

	return quot;
}

polynomial polynomial::operator %(const polynomial& divisor) const {
	if (deg() < divisor.deg()) return polynomial();

	// будущий остаток
	polynomial remainder(*this);

	// очередное слагаемое неполного частного
	polynomial quot_term;
	quot_term.alloc(1);

	// степень остатка (будет уменьшаться)
	int remainder_deg = remainder.deg();
	// степень делителя
	int devisor_deg = divisor.deg();
	// коэффициент при старшей степени делителя
	float devisor_deg_coeff = divisor[devisor_deg];

	// деление, аналогичное делению в столбик
	while (remainder_deg >= devisor_deg) {
		quot_term.Terms->power = remainder_deg - devisor_deg;
		quot_term.Terms->coefficient = remainder[remainder_deg] / devisor_deg_coeff;

		remainder = remainder - quot_term * divisor;

		remainder_deg = remainder.deg();
	}

	return remainder;
}

bool polynomial::operator ==(const polynomial& polynomial) const {
	int max_power = deg();
	if (max_power != polynomial.deg()) return false;

	for (int pow = 0; pow <= max_power; pow++) {
		if ((*this)[pow] != polynomial[pow]) return false;
	}

	return true;
}
bool polynomial::operator !=(const polynomial& polynomial) const {
	int max_power = deg();
	if (max_power != polynomial.deg()) return true;

	for (int pow = 0; pow <= max_power; pow++) {
		if ((*this)[pow] != polynomial[pow]) return true;
	}

	return false;
}

// степень многочлена
int polynomial::deg() const {
	int max_power = 0;

	for (Term _term : *this) {
		if (_term.power > max_power) {
			max_power = _term.power;
		}
	}

	return max_power;
};

// производная
polynomial polynomial::derivative() const {

	/* если в многочлене нет слагаемых или оно одно, но степени 0,
	то производная - нулевой многочлен */

	if (count_terms == 0 || (count_terms == 1 && Terms->power == 0)) return polynomial();

	/* если в многочлене есть слагаемое с нулевой степенью,
	то в производной будет на одно слагаемое меньше */

	int derived_count_terms = count_terms;
	if ((*this)[0] != 0) derived_count_terms--;

	polynomial derived;
	derived.alloc(derived_count_terms);

	int i = 0;
	for (Term _term : *this) {
		/* игнорируем слагаемое с нулевой степенью */
		if (_term.power == 0) continue;

		derived.Terms[i].coefficient = _term.coefficient * _term.power;
		derived.Terms[i].power = _term.power - 1;
		i++;
	}

	return derived;
}

/* манипулятор для пропуска пробелов и символов '\n' */
std::istream& skipspaces(std::istream& stream) {
	while (stream.peek() == ' ' || stream.peek() == '\n') stream.ignore();

	return stream;
}

std::ostream& rgr::operator <<(std::ostream& stream, const polynomial& polynomial) {
	stream << '[';

	char sign; float coeff; int polynomial_deg = polynomial.deg();
	for (int pow = 0; pow <= polynomial_deg; pow++) {
		coeff = polynomial[pow];
		if (coeff == 0) continue;

		if (coeff > 0) {
			sign = '+';
		}
		else {
			sign = '-';
			coeff = -coeff;
		}

		stream << sign << pow << " : " << coeff;

		if (pow != polynomial_deg) {
			stream << ' ';
		}
	}

	stream << ']';

	return stream;
}
std::istream& rgr::operator >>(std::istream& stream, polynomial& polynomial) {
	polynomial.clear();

	try {
		stream >> skipspaces;

		if (stream.peek() != '[') throw 1;
		stream.ignore();

		polynomial.count_terms = 0;
		int size = 1;
		polynomial.Terms = new polynomial::Term[1];

		char sign; int _power; float _coefficient;
		while (true) {
			stream >> skipspaces;

			if (stream.peek() == ']') {
				stream.ignore();
				return stream;
			}

			stream >> sign;
			if (sign != '+' && sign != '-') throw 1;

			stream >> _power >> skipspaces;
			if (stream.fail() || _power < 0) throw 2;

			/* контроль сортированного ввода (не уверен, что это необходимо) */
			// if (polynomial.count_terms > 0 && _power <= polynomial.Terms[polynomial.count_terms - 1].power) throw 3;

			if (stream.peek() != ':') throw 1;
			stream.ignore();

			stream >> _coefficient;
			if (stream.fail()) throw 2;
			if (_coefficient == 0) continue;

			if (sign == '-') _coefficient = -_coefficient;

			if (polynomial.count_terms >= size) {
				size *= 2;
				polynomial::Term* twice_terms = new polynomial::Term[size];

				for (int i = 0; i < polynomial.count_terms; i++) {
					twice_terms[i] = polynomial.Terms[i];
				}

				delete[] polynomial.Terms;
				polynomial.Terms = twice_terms;
			}

			polynomial.Terms[polynomial.count_terms].power = _power;
			polynomial.Terms[polynomial.count_terms].coefficient = _coefficient;
			polynomial.count_terms++;
		}

	}
	catch (int error_code) {
		// std::ofstream err("pol_input_errors.txt");

		switch (error_code) {
		case 1: std::cout << "symbol error\n"; break;
		case 2: std::cout << "value error\n"; break;
		case 3: std::cout << "error: not sorted input\n"; break;
		}

		stream.setstate(std::ios::failbit);
		return stream;
	}
}

// перегрузка операторов для итератора
polynomial::Term& polynomial::Iterator::operator*() const {
	return *ptr;
}
bool polynomial::Iterator::operator==(const polynomial::Iterator& it) const {
	return ptr == it.ptr;
}
bool polynomial::Iterator::operator!=(const polynomial::Iterator& it) const {
	return ptr != it.ptr;
}
polynomial::Iterator& polynomial::Iterator::operator++() {
	ptr++;
	return *this;
}
polynomial::Iterator polynomial::Iterator::operator++(int) {
	Iterator old = *this;
	ptr++;
	return old;
}
