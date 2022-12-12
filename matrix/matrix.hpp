#include <iostream>

#ifndef MATRIX_HPP
#define MATRIX_HPP

//template<typename FieldEl>
class Matrix {
protected:
	float** matrix;
	int rows;
	int cols;

	void reconstruct(int newRows, int newCols);
public:
	Matrix();
	Matrix(int _rows, int _cols);
	Matrix(const Matrix& _matrix);
	Matrix(Matrix&& _matrix) noexcept;
	~Matrix();

	void clear();

	Matrix& operator =(const Matrix& _matrix);
	Matrix& operator =(Matrix&& _matrix) noexcept;

	Matrix operator +(const Matrix& _matrix) const;
	Matrix operator -(const Matrix& _matrix) const;
	Matrix operator *(const Matrix& _matrix) const;

	bool operator ==(const Matrix& _matrix) const;
	bool operator !=(const Matrix& _matrix) const;

	float*& operator[](int row) const;

	virtual Matrix& transpose();
	float max_element();

	friend std::ostream& operator <<(std::ostream& stream, const Matrix& _matrix);
	friend std::istream& operator >>(std::istream& stream, Matrix& _matrix);

	friend class SqMatrix;
};

class SqMatrix : public Matrix {
private:
	void reconstruct(int newSize);
public:
	SqMatrix();
	SqMatrix(int size);
	explicit SqMatrix(const Matrix& _matrix);
	explicit SqMatrix(Matrix&& _matrix) noexcept;

	SqMatrix& transpose() override;

	float det();

	SqMatrix pow(int power);

	friend std::istream& operator >>(std::istream& stream, SqMatrix& _matrix);
};

#endif // MATRIX_HPP