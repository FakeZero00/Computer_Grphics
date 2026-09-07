#pragma once
#include <array>
#include <vector>
#include "Square.h"
using namespace std;

class Board {
public:
	Board() = default;

	void addSquare(const Square& square);
	void checkCollisions();
	void printBoard() const;

private:
	array<array<char, 30>, 30> board;
	vector<Square> squares;
	vector<pair<pair<int, int>, pair<int, int>>> hitCollisions;		//충돌한 부분의 좌표
};