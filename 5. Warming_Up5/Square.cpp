#include "Square.h"

Square::Square(int x1, int y1, int x2, int y2) : pos1(x1, y1), pos2(x2, y2) {}

pair<int, int> Square::getPos1() const {
	return pos1;
}

pair<int, int> Square::getPos2() const {
	return pos2;
}

void Square::setPos1(int x, int y) {
	pos1 = { x, y };
}

void Square::setPos2(int x, int y) {
	pos2 = { x, y };
}

int Square::getWidth() const {
	return abs(pos2.first - pos1.first);
}

int Square::getHeight() const {
	return abs(pos2.second - pos1.second);
}