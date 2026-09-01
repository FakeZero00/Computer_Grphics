#pragma once

class CMatrix
{
public:
	CMatrix() = default;
	CMatrix(int v11, int v12, int v13, int v14,
			int v21, int v22, int v23, int v24,
			int v31, int v32, int v33, int v34,
			int v41, int v42, int v43, int v44);

	void printMatrix() const;
	void printtMatrix() const;

	int getData(int row, int col) const;
	int setData(int row, int col, int value);
	void settData();
	int getmmDet() const;
	int getmDet() const;
	int getDet() const;
	int gettDet() const;

	CMatrix operator*(CMatrix& other);
	CMatrix operator+(CMatrix& other);
	CMatrix operator-(CMatrix& other);

private:
	int matrixData[4][4] = { {0} };
	int tmatrixData[4][4] = { {0} };
};