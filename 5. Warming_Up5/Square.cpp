#include "Square.h"

Square::Square(int x1, int y1, int x2, int y2) : minPos(x1, y1), maxPos(x2, y2) {}

pair<int, int> Square::getMin() const {
	return minPos;
}

pair<int, int> Square::getMax() const {
	return maxPos;
}

void Square::setMin(int x, int y) {
	minPos = { x, y };
}

void Square::setMax(int x, int y) {
	maxPos = { x, y };
}

int Square::getWidth() const {
	return abs(maxPos.second - minPos.second) + 1;
}

int Square::getHeight() const {
	return abs(maxPos.first - minPos.first) + 1;
}