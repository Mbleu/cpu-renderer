#include "matrix.h"

double dotProd(const std::vector<double>& lhs, const std::vector<double>& rhs);

Matrix::Matrix()
	: cols(0)
{}
Matrix::Matrix(const int rows, const int cols)
	: cols(cols), data(rows * cols)
{
	if (cols < 0) throw "Invalid number of columns.";
	if (rows < 0) throw "Invalid number of rows.";
}
Matrix::Matrix(const int cols, const std::vector<double>& data)
	: cols(cols), data(data)
{
	if (cols < 0) throw "Invalid number of columns.";
	if (data.size() % cols != 0) throw "Incomplete vector.";
}
Matrix Matrix::identity(const int cols)	// named constructor
{
	return Matrix(cols);
}
Matrix::Matrix::Matrix(const int cols)	// identity matrix
	: cols(cols), data(cols * cols)
{
	if (cols < 0) throw "Invalid number of columns.";

	for (int i{ 0 }; i < data.size(); ++i)
		data[i * cols + i] = 1;
}
void Matrix::setRow(const int i, const std::vector<double>& dataRow)
{
	if (i < 0 || i > rowCount()) throw "Invalid row index.";
	if (dataRow.size() != cols) throw "Invalid row size.";

	for (int j{ 0 }; j < cols; ++j)
		data[i * cols + j] = dataRow[j];
}
void Matrix::setCol(const int j, const std::vector<double>& dataCol)
{
	if (j < 0 || j > cols) throw "Invalid column index.";
	if (dataCol.size() != rowCount()) throw "Invalid column size.";

	for (int i{ 0 }; i < dataCol.size(); ++i)
		data[i * cols + j] = dataCol[i];
}
void Matrix::setElem(const int i, const int j, const double dataElem)
{
	if (i < 0 || i > rowCount()) throw "Invalid row index.";
	if (j < 0 || j > cols) throw "Invalid column index.";

	data[i * cols + j] = dataElem;
}
int Matrix::rowCount() const
{
	return data.size() / cols;
}
int Matrix::colCount() const
{
	return cols;
}
const std::vector<double>& Matrix::getData() const
{
	return data;
}
std::vector<double> Matrix::copyRow(const int i) const
{
	if (i < 0 || i > rowCount()) throw "Invalid row index.";

	std::vector<double>::const_iterator rowStart{ data.begin() + i * cols };

	return { rowStart, rowStart + cols };
}
std::vector<double> Matrix::copyCol(const int j) const
{
	if (j < 0 || j > cols) throw "Invalid column index.";

	std::vector<double> colData(cols);

	for (int i{ 0 }; i < rowCount(); ++i)
		colData[i] = data[i * cols + j];

	return colData;
}
double Matrix::copyElem(const int i, const int j) const
{
	return data[i * cols + j];
}
Matrix& Matrix::operator+=(const Matrix& rhs)
{
	Matrix& lhs{ *this };
	if (lhs.rowCount() != rhs.rowCount() ||  lhs.colCount() != rhs.colCount()) throw "Cannot add matrix with different dimensions.";

	for (int i{ 0 }; i < lhs.data.size(); ++i)
		lhs.data[i] += rhs.getData()[i];

	return lhs;
}
Matrix& Matrix::operator-=(const Matrix& rhs)
{
	Matrix& lhs{ *this };
	if (lhs.rowCount() != rhs.rowCount() || lhs.colCount() != rhs.colCount()) throw "Cannot substract matrix with different dimensions.";

	for (int i{ 0 }; i < lhs.data.size(); ++i)
		lhs.data[i] -= rhs.getData()[i];

	return lhs;
}
Matrix& Matrix::operator*=(const Matrix& rhs)
{
	Matrix& lhs{ *this };
	if (lhs.colCount() != rhs.rowCount()) throw "Matrix lhs must have same number of columns as matrix rhs has rows.";

	Matrix result{ lhs.rowCount(), rhs.colCount() };
	for (int i{ 0 }; i < lhs.rowCount(); ++i)
		for (int j{ 0 }; j < rhs.colCount(); ++j)
			result.setElem(i, j, dotProd(lhs.copyRow(i), rhs.copyCol(j)));

	lhs = result;
	return lhs;
}
Matrix& Matrix::operator*=(const double rhs)
{
	Matrix& lhs{ *this };

	for (int i{ 0 }; i < lhs.data.size(); ++i)
		lhs.data[i] *= rhs;

	return lhs;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
	Matrix result{ lhs };
	result += rhs;
	return result;
}
Matrix operator-(const Matrix& lhs, const Matrix& rhs)
{
	Matrix result{ lhs };
	result -= rhs;
	return result;
}
Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
	Matrix result{ lhs };
	result *= rhs;
	return result;
}
Matrix operator*(const double lhs, const Matrix& rhs)
{
	Matrix result{ rhs };
	result *= lhs;
	return result;
}
Matrix operator*(const Matrix& lhs, const double rhs)
{
	return rhs * lhs;
}
double dotProd(const std::vector<double>& lhs, const std::vector<double>& rhs)
{
	if (lhs.size() != rhs.size()) throw "Vectors must have same dimensions.";

	double result{ 0 };

	for (int i{ 0 }; i < lhs.size(); ++i)
		result += lhs[i] * rhs[i];

	return result;
}