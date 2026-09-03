#pragma once
#include <array>
#include <vector>
using namespace std;

class Board {
public:
	Board() = default;
	Board(size_t row, size_t col);

	void print() const;
	void printAll() const;
	void clearVisited();

	void setCell(size_t row, size_t col, char value);
	char getCell(size_t row, size_t col) const;
	void setVisited(size_t row, size_t col, bool visited);
	void setSuccess(size_t row, size_t col, bool success);
	void openJoker();
	bool validCheck(size_t row, size_t col) const;
	bool isComplete() const;

private:
	size_t row;
	size_t col;
	vector<vector<char>> data;
	vector<vector<bool>> isValid;
	vector<vector<bool>> isVisited;
	vector<vector<bool>> isSuccess;
	vector<vector<int>> color;
	array<int, 2> jokerPos;
};