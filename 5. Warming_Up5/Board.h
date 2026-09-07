#pragma once
#include <vector>
#include "Square.h"
using namespace std;

class Board {
public:
	Board() = default;

	void addSquare(const Square& square);
	void checkCollisions() const;
	void printBoard() const;

private:
	vector<Square> squares;
	vector<pair<pair<int, int>, int>> hitPoints;	//좌표, 충돌하는 곳 표시할 색깔
};