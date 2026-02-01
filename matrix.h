#pragma once
#include <vector>

class Matrix {
public:
	Matrix();
	Matrix(const int rows, const int cols);
	Matrix(const int cols, const std::vector<double>& data);
	static Matrix identity(const int cols);	// named constructor
	
	void setRow(const int i, const std::vector<double>& dataRow);
	void setCol(const int j, const std::vector<double>& dataCol);
	void setElem(const int i, const int j, const double dataElem);

	int rowCount() const;
	int colCount() const;
	const std::vector<double>& getData() const;
	std::vector<double> copyRow(const int i) const;
	std::vector<double> copyCol(const int j) const;
	double copyElem(const int i, const int j) const;
	
	Matrix& operator+=(const Matrix& rhs);
	Matrix& operator-=(const Matrix& rhs);
	Matrix& operator*=(const Matrix& rhs);
	Matrix& operator*=(const double rhs);

private:
	Matrix(const int cols);	// identity matrix

	int cols;
	std::vector<double> data;
};

Matrix operator+(const Matrix& lhs, const Matrix& rhs);
Matrix operator-(const Matrix& lhs, const Matrix& rhs);
Matrix operator*(const Matrix& lhs, const Matrix& rhs);
Matrix operator*(const double lhs, const Matrix& rhs);
Matrix operator*(const Matrix& lhs, const double rhs);