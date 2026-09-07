#pragma once
#include <array>
#include <vector>
#include "Square.h"
using namespace std;

class Board {
public:
	Board();

	void addSquare(const Square& square);

	int getSquare1Width() const;
	int getSquare1Height() const;
	int getSquare2Width() const;
	int getSquare2Height() const;
	void moveSquare1(int dx, int dy);
	void moveSquare2(int dx, int dy);
	void zoomSquare1(int dx, int dy);
	void zoomSquare2(int dx, int dy);

	int getWidth() const;
	int getHeight() const;
	void setWidth(int w);
	void setHeight(int h);

	void resetBoard();
	void printBoard();

private:
	int width = 30;
	int height = 30;
	vector<vector<char>> board;
	vector<Square> squares;
	vector<pair<pair<int, int>, pair<int, int>>> hitCollisions;		//충돌한 부분의 좌표
};