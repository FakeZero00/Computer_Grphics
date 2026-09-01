#include <ranges>
#include <iostream>
#include "CMatrix.h"
using namespace std;

CMatrix::CMatrix(int v00, int v01, int v02, int v03,
				 int v10, int v11, int v12, int v13,
				 int v20, int v21, int v22, int v23,
				 int v30, int v31, int v32, int v33)
{
	matrixData[0][0] = v00;
	matrixData[0][1] = v01;
	matrixData[0][2] = v02;
	matrixData[0][3] = v03;
	matrixData[1][0] = v10;
	matrixData[1][1] = v11;
	matrixData[1][2] = v12;
	matrixData[1][3] = v13;
	matrixData[2][0] = v20;
	matrixData[2][1] = v21;
	matrixData[2][2] = v22;
	matrixData[2][3] = v23;
	matrixData[3][0] = v30;
	matrixData[3][1] = v31;
	matrixData[3][2] = v32;
	matrixData[3][3] = v33;
}

void CMatrix::printmMatrix() const {
	for (int i : views::iota(0, 3)) {
		for (int j : views::iota(0, 3)) {
			std::cout << matrixData[j][i] << " ";
		}
		std::cout << std::endl;
	}
}

void CMatrix::printMatrix() const {
	for (int i : views::iota(0, 4)) {
		for (int j : views::iota(0, 4)) {
			std::cout << matrixData[j][i] << " ";
		}
		std::cout << std::endl;
	}
}

int CMatrix::getmmDet() const {
	return matrixData[0][0] * matrixData[1][1] - matrixData[0][1] * matrixData[1][0];
}

int CMatrix::getmDet() const {
	int det = 0;
	for (int i : views::iota(0, 3)) {
		CMatrix minorMatrix{
			matrixData[(i + 1) % 3][1], matrixData[(i + 2) % 3][1], 0, 0,
			matrixData[(i + 1) % 3][2], matrixData[(i + 2) % 3][2], 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		};
		//minorMatrix.printmMatrix();
		det += (matrixData[i][0] * minorMatrix.getmmDet() * ((i % 2 == 0) ? 1 : -1));
	}
	cout << "3x3 행렬의 행렬식: " << det << endl;

	return det;
}

int CMatrix::getDet() const {
	int det = 0;
	for (int i : views::iota(0, 4)) {
		CMatrix minorMatrix{
			matrixData[(i + 1) % 4][1], matrixData[(i + 1) % 4][2], matrixData[(i + 1) % 4][3], 0,
			matrixData[(i + 2) % 4][1], matrixData[(i + 2) % 4][2], matrixData[(i + 2) % 4][3], 0,
			matrixData[(i + 3) % 4][1], matrixData[(i + 3) % 4][2], matrixData[(i + 3) % 4][3], 0,
			0, 0, 0, 0
		};
		minorMatrix.printmMatrix();
		det += (matrixData[i][0] * minorMatrix.getmDet() * ((i % 2 == 0) ? 1 : -1));
	}

	return det;
}

CMatrix CMatrix::operator*(CMatrix& other)
{
	CMatrix result;
	for (int i : views::iota(0, 4)) {
		for (int j : views::iota(0, 4)) {
			result.matrixData[i][j] = 0;
			for (int k : views::iota(0, 4)) {
				result.matrixData[i][j] += matrixData[i][k] * other.matrixData[k][j];
			}
		}
	}
	return result;
}

CMatrix CMatrix::operator+(CMatrix& other)
{
	CMatrix result;
	for (int i : views::iota(0, 4)) {
		for (int j : views::iota(0, 4)) {
			result.matrixData[i][j] = matrixData[i][j] + other.matrixData[i][j];
		}
	}
	return result;
}

CMatrix CMatrix::operator-(CMatrix& other)
{
	CMatrix result;
	for (int i : views::iota(0, 4)) {
		for (int j : views::iota(0, 4)) {
			result.matrixData[i][j] = matrixData[i][j] - other.matrixData[i][j];
		}
	}
	return result;
}