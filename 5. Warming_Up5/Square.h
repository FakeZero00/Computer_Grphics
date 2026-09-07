#pragma once
#include <array>
using namespace std;

class Square {
public:
	Square() = default;
	Square(int x1, int y1, int x2, int y2);
	
	pair<int, int> getPos1() const;
	pair<int, int> getPos2() const;
	void setPos1(int x, int y);
	void setPos2(int x, int y);

	int getWidth() const;
	int getHeight() const;

private:
	pair<int, int> pos1;
	pair<int, int> pos2;
};