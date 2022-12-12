#include <iostream>
#include <limits>
#include "matrix.hpp"
#include "ex.hpp"

void Matrix::reconstruct(int newRows, int newCols) {
	clear();

	rows = newRows; cols = newCols;

	matrix = new float* [rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new float[cols];
	}
}

Matrix::Matrix() : matrix(nullptr), rows(0), cols(0) {}

Matrix::Matrix(int _rows, int _cols) : matrix(new float* [_rows]), rows(_rows), cols(_cols) {
	for (int i = 0; i < rows; i++) {
		matrix[i] = new float[cols];

		for (int j = 0; j < cols; j++) {
			matrix[i][j] = 0;
		}
	}
}
Matrix::Matrix(const Matrix& _matrix) : matrix(new float* [_matrix.rows]), rows(_matrix.rows), cols(_matrix.cols) {
	for (int i = 0; i < rows; i++) {
		matrix[i] = new float[cols];

		for (int j = 0; j < cols; j++) {
			matrix[i][j] = _matrix[i][j];
		}
	}
}

Matrix::Matrix(Matrix&& _matrix) noexcept {
	matrix = _matrix.matrix;
	rows = _matrix.rows;
	cols = _matrix.cols;

	_matrix.matrix = nullptr;
	_matrix.rows = 0;
	_matrix.cols = 0;
}

Matrix::~Matrix() {
	clear();
}

void Matrix::clear() {
	if (matrix == nullptr) return;

	for (int i = 0; i < rows; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
	matrix = nullptr;

	rows = cols = 0;
}

Matrix& Matrix::operator =(const Matrix& _matrix) {
	if (this == &_matrix) return *this;

	if (rows != _matrix.rows || cols != _matrix.cols) {
		rows = _matrix.rows; cols = _matrix.cols;
		reconstruct(rows, cols);
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = _matrix[i][j];
		}
	}

	return *this;
}
Matrix& Matrix::operator =(Matrix&& _matrix) noexcept {
	if (this == &_matrix) return *this;

	clear();

	matrix = _matrix.matrix;
	rows = _matrix.rows;
	cols = _matrix.cols;

	_matrix.matrix = nullptr;
	_matrix.rows = 0;
	_matrix.cols = 0;

	return *this;
}

Matrix Matrix::operator +(const Matrix& _matrix) const {
	if (rows != _matrix.rows || cols != _matrix.cols) throw "add error in +";

	Matrix sum(*this);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			sum[i][j] += _matrix[i][j];
		}
	}

	return sum;
}

Matrix Matrix::operator -(const Matrix& _matrix) const {
	if (rows != _matrix.rows || cols != _matrix.cols) throw "add error in -";

	Matrix dif(*this);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			dif[i][j] -= _matrix[i][j];
		}
	}

	return dif;
}

Matrix Matrix::operator *(const Matrix& _matrix) const {
	if (cols != _matrix.rows) throw sizeerror();

	Matrix prod(rows, _matrix.cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < _matrix.cols; j++) {
			for (int l = 0; l < cols; l++)
				prod[i][j] += matrix[i][l] * _matrix[l][j];
		}
	}

	return prod;
}

bool Matrix::operator ==(const Matrix& _matrix) const {
	if (rows != _matrix.rows || cols != _matrix.cols) throw "cmp error";

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (matrix[i][j] != _matrix[i][j]) return false;
		}
	}

	return true;
}

bool Matrix::operator !=(const Matrix& _matrix) const {
	if (rows != _matrix.rows || cols != _matrix.cols) throw "cmp error";

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (matrix[i][j] != _matrix[i][j]) return true;
		}
	}

	return false;
}

float*& Matrix::operator [](int row) const {
	return matrix[row];
}

Matrix& Matrix::transpose() {
	Matrix this_copy(*this);

	reconstruct(cols, rows);

	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			matrix[j][i] = this_copy[i][j];
		}
	}

	return *this;
}

float Matrix::max_element() {
	float max = -FLT_MAX;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (matrix[i][j] > max) {
				max = matrix[i][j];
			}
		}
	}

	return max;
}

std::ostream& operator <<(std::ostream& stream, const Matrix& _matrix) {
	for (int i = 0; i < _matrix.rows; i++) {
		for (int j = 0; j < _matrix.cols; j++) {
			stream.width(10);
			stream << _matrix[i][j] << ' ';
		}
		stream << '\n';
	}

	return stream;
}

std::istream& operator >>(std::istream& stream, Matrix& _matrix) {
	try {
		if (_matrix.matrix == nullptr) {
			stream >> _matrix.rows >> _matrix.cols;
			if (stream.fail()) throw 1;

			_matrix.reconstruct(_matrix.rows, _matrix.cols);
		}


		for (int i = 0; i < _matrix.rows; i++) {
			for (int j = 0; j < _matrix.cols; j++) {
				stream >> _matrix[i][j];
				if (stream.fail()) throw 1;
			}
		}

		return stream;
	}
	catch (...) {
		stream.setstate(std::ios::failbit);
		return stream;
	}
}

// -----------------------------------------------------------------------

void SqMatrix::reconstruct(int newSize) {
	Matrix::reconstruct(newSize, newSize);
}

SqMatrix::SqMatrix() : Matrix() {}

SqMatrix::SqMatrix(int size) : Matrix(size, size) {}

inline int min(int a, int b) {
	return a < b ? a : b;
}

SqMatrix::SqMatrix(const Matrix& _matrix) : SqMatrix() {
	reconstruct(min(_matrix.rows, _matrix.cols));

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = _matrix[i][j];
		}
	}
}

SqMatrix::SqMatrix(Matrix&& _matrix) noexcept : SqMatrix() {
	if (_matrix.rows == _matrix.cols) {
		matrix = _matrix.matrix;
		rows = _matrix.rows;
		cols = _matrix.cols;

		_matrix.matrix = nullptr;
		_matrix.rows = _matrix.cols = 0;

		return;
	}

	int min_size = min(_matrix.rows, _matrix.cols);
	reconstruct(min_size);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = _matrix[i][j];
		}
	}
 
	_matrix.clear();
}

SqMatrix& SqMatrix::transpose() {
	float t;

	for (int i = 0; i < rows; i++) {
		for (int j = i + 1; j < cols; j++) {
			t = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = t;
		}
	}

	return *this;
}

float SqMatrix::det() {
	SqMatrix copy(*this);

	float sign = 1;
	auto swap = [](float*& a, float*& b) {
		float* t = a;
		a = b;
		b = t;
	};

	/* цикл приводит матрицу к диагональному виду путём элементарных преобразований */
	for (int i = 0; i < cols; i++) {

		/* если элемент на главной диагонали нулевой,
		то надо найти в том же столбце ниже ненулевой элемент
		и поменять строки местами,
		при этом изменится знак определителя;
		если такого элемента не нашлось, то определитель равен нулю */

		if (copy[i][i] == 0) {
			for (int j = i + 1; j < rows; j++) {
				if (copy[j][i] == 0) continue;

				swap(copy[i], copy[j]);
				sign = -sign;
				break;
			}

			if (copy[i][i] == 0) return 0;
		}

		/* выполняет элементарные преобразования со строками:
		зануляет элементы ниже главной диагонали */

		for (int j = i + 1; j < rows; j++) {
			float coeff = copy[j][i] / copy[i][i];

			for (int k = i; k < cols; k++) {
				copy[j][k] -= copy[i][k] * coeff;
			}
		}
	}

	/* осталось перемножить элементы главной диагонали */

	float det = sign;
	for (int i = 0; i < cols; i++) {
		det *= copy[i][i];
	}

	return det;
}

SqMatrix SqMatrix::pow(int power) {
	SqMatrix prod(rows);

	if (power == 0) {
		for (int i = 0; i < rows; i++) {
			prod[i][i] = 1;
		}

		return prod;
	}

	prod = *this;

	for (int p = 1; p < power; p++) {
		prod = static_cast<SqMatrix>(prod * (*this));
	}

	return prod;
}

std::istream& operator >>(std::istream& stream, SqMatrix& _matrix) {
	try {
		if (_matrix.matrix == nullptr) {
			stream >> _matrix.rows;
			if (stream.fail()) throw 1;

			_matrix.cols = _matrix.rows;

			_matrix.reconstruct(_matrix.rows);
		}


		for (int i = 0; i < _matrix.rows; i++) {
			for (int j = 0; j < _matrix.cols; j++) {
				stream >> _matrix[i][j];
				if (stream.fail()) throw 1;
			}
		}

		return stream;
	}
	catch (...) {
		stream.setstate(std::ios::failbit);
		return stream;
	}
}