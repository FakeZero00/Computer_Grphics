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

	tmatrixData[0][0] = v00;
	tmatrixData[0][1] = v10;
	tmatrixData[0][2] = v20;
	tmatrixData[0][3] = v30;
	tmatrixData[1][0] = v01;
	tmatrixData[1][1] = v11;
	tmatrixData[1][2] = v21;
	tmatrixData[1][3] = v31;
	tmatrixData[2][0] = v02;
	tmatrixData[2][1] = v12;
	tmatrixData[2][2] = v22;
	tmatrixData[2][3] = v32;
	tmatrixData[3][0] = v03;
	tmatrixData[3][1] = v13;
	tmatrixData[3][2] = v23;
	tmatrixData[3][3] = v33;
}

void CMatrix::printMatrix() const {
	for (int i : views::iota(0, 4)) {
		for (int j : views::iota(0, 4)) {
			cout << matrixData[i][j] << " ";
		}
		cout << endl;
	}
}

void CMatrix::printtMatrix() const {
	for (int i : views::iota(0, 4)) {
		for (int j : views::iota(0, 4)) {
			cout << tmatrixData[i][j] << " ";
		}
		cout << endl;
	}
}

int CMatrix::getData(int row, int col) const {
	return matrixData[row][col];
}

int CMatrix::setData(int row, int col, int value) {
	matrixData[row][col] = value;
	CMatrix::settData();
	return value;
}

void CMatrix::settData() {
	tmatrixData[0][0] = matrixData[0][0];
	tmatrixData[0][1] = matrixData[1][0];
	tmatrixData[0][2] = matrixData[2][0];
	tmatrixData[0][3] = matrixData[3][0];
	tmatrixData[1][0] = matrixData[0][1];
	tmatrixData[1][1] = matrixData[1][1];
	tmatrixData[1][2] = matrixData[2][1];
	tmatrixData[1][3] = matrixData[3][1];
	tmatrixData[2][0] = matrixData[0][2];
	tmatrixData[2][1] = matrixData[1][2];
	tmatrixData[2][2] = matrixData[2][2];
	tmatrixData[2][3] = matrixData[3][2];
	tmatrixData[3][0] = matrixData[0][3];
	tmatrixData[3][1] = matrixData[1][3];
	tmatrixData[3][2] = matrixData[2][3];
	tmatrixData[3][3] = matrixData[3][3];

	return;
}

int CMatrix::getmmDet() const {
	return matrixData[0][0] * matrixData[1][1] - matrixData[0][1] * matrixData[1][0];
}

int CMatrix::getmDet() const {
	int det = 0;
	CMatrix minorMatrix1{
			matrixData[1][1], matrixData[1][2], 0, 0,
			matrixData[2][1], matrixData[2][2], 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
	};
	CMatrix minorMatrix2{
		matrixData[1][0], matrixData[1][2], 0, 0,
		matrixData[2][0], matrixData[2][2], 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	};
	CMatrix minorMatrix3{
		matrixData[1][0], matrixData[1][1], 0, 0,
		matrixData[2][0], matrixData[2][1], 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	};
	det += matrixData[0][0] * minorMatrix1.getmmDet();
	det -= matrixData[0][1] * minorMatrix2.getmmDet();
	det += matrixData[0][2] * minorMatrix3.getmmDet();

	return det;
}

int CMatrix::getDet() const {
	int det = 0;
	CMatrix minorMatrix1{
			matrixData[1][1], matrixData[1][2], matrixData[1][3], 0,
			matrixData[2][1], matrixData[2][2], matrixData[2][3], 0,
			matrixData[3][1], matrixData[3][2], matrixData[3][3], 0,
			0, 0, 0, 0
	};
	CMatrix minorMatrix2{
			matrixData[1][0], matrixData[1][2], matrixData[1][3], 0,
			matrixData[2][0], matrixData[2][2], matrixData[2][3], 0,
			matrixData[3][0], matrixData[3][2], matrixData[3][3], 0,
			0, 0, 0, 0
	};
	CMatrix minorMatrix3{
			matrixData[1][0], matrixData[1][1], matrixData[1][3], 0,
			matrixData[2][0], matrixData[2][1], matrixData[2][3], 0,
			matrixData[3][0], matrixData[3][1], matrixData[3][3], 0,
			0, 0, 0, 0
	};
	CMatrix minorMatrix4{
			matrixData[1][0], matrixData[1][1], matrixData[1][2], 0,
			matrixData[2][0], matrixData[2][1], matrixData[2][2], 0,
			matrixData[3][0], matrixData[3][1], matrixData[3][2], 0,
			0, 0, 0, 0
	};

	det += matrixData[0][0] * minorMatrix1.getmDet();
	det -= matrixData[0][1] * minorMatrix2.getmDet();
	det += matrixData[0][2] * minorMatrix3.getmDet();
	det -= matrixData[0][3] * minorMatrix4.getmDet();

	return det;
}

int CMatrix::gettDet() const {
	int det = 0;
	CMatrix minorMatrix1{
			tmatrixData[1][1], tmatrixData[1][2], tmatrixData[1][3], 0,
			tmatrixData[2][1], tmatrixData[2][2], tmatrixData[2][3], 0,
			tmatrixData[3][1], tmatrixData[3][2], tmatrixData[3][3], 0,
			0, 0, 0, 0
	};
	CMatrix minorMatrix2{
			tmatrixData[1][0], tmatrixData[1][2], tmatrixData[1][3], 0,
			tmatrixData[2][0], tmatrixData[2][2], tmatrixData[2][3], 0,
			tmatrixData[3][0], tmatrixData[3][2], tmatrixData[3][3], 0,
			0, 0, 0, 0
	};
	CMatrix minorMatrix3{
			tmatrixData[1][0], tmatrixData[1][1], tmatrixData[1][3], 0,
			tmatrixData[2][0], tmatrixData[2][1], tmatrixData[2][3], 0,
			tmatrixData[3][0], tmatrixData[3][1], tmatrixData[3][3], 0,
			0, 0, 0, 0
	};
	CMatrix minorMatrix4{
			tmatrixData[1][0], tmatrixData[1][1], tmatrixData[1][2], 0,
			tmatrixData[2][0], tmatrixData[2][1], tmatrixData[2][2], 0,
			tmatrixData[3][0], tmatrixData[3][1], tmatrixData[3][2], 0,
			0, 0, 0, 0
	};

	det += tmatrixData[0][0] * minorMatrix1.getmDet();
	det -= tmatrixData[0][1] * minorMatrix2.getmDet();
	det += tmatrixData[0][2] * minorMatrix3.getmDet();
	det -= tmatrixData[0][3] * minorMatrix4.getmDet();

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