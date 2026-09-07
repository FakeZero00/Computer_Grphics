#pragma once
#include <array>
using namespace std;

class Square {
public:
	Square() = default;
	Square(int x1, int y1, int x2, int y2);
	
	pair<int, int> getMin() const;
	pair<int, int> getMax() const;
	void setMin(int x, int y);
	void setMax(int x, int y);

	int getWidth() const;
	int getHeight() const;

private:
	pair<int, int> minPos;
	pair<int, int> maxPos;
};