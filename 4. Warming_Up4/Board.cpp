#include<iostream>
#include <random>
#include <cctype>
#include <windows.h>
#include "Board.h"
using namespace std;

Board::Board(size_t row, size_t col) : row(row), col(col), data(row, vector<char>(col)), isValid(row, vector<bool>(col)), isVisited(row, vector<bool>(col)), isSuccess(row, vector<bool>(col)), color(row, vector<int>(col))
{
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < col; ++j) {
			data[i][j] = ' ';
			isValid[i][j] = false;
			isVisited[i][j] = false;
			isSuccess[i][j] = false;
			color[i][j] = 0;
		}
	}

	random_device rd;
	default_random_engine dre(rd());
	uniform_int_distribution<size_t> randomRow{ 0, row - 1 };
	uniform_int_distribution<size_t> randomCol{ 0, col - 1 };

	char value = '@';
	int count = 0;
	int setColor = 1;

	while (!isComplete()) {
		size_t prow = randomRow(dre);
		size_t pcol = randomCol(dre);

		if (value == '@' && (row * col) % 2 == 1) {
			data[prow][pcol] = value;
			isValid[prow][pcol] = true;
			color[prow][pcol] = 15;

			value = 'a';
			continue;
		}
		else if (value == '@' && (row * col) % 2 == 0){
			value = 'a';
			continue;
		}

		if (validCheck(prow, pcol)) continue;
		
		data[prow][pcol] = value;
		isValid[prow][pcol] = true;
		color[prow][pcol] = setColor;

		if (isComplete()) {
			jokerPos[0] = prow;
			jokerPos[1] = pcol;
			break;
		}

		if (count == 0) count++;
		else if (count == 1) {
			value++;
			setColor++;
			count = 0;
		}
	}
}

void Board::print() const {
	cout << "\t";
	for (char i = 'a'; i < 'a' + static_cast<char>(col); ++i) {
		cout << i << "\t";
	}

	cout << endl;

	for (size_t i = 0; i < row; ++i) {
		cout << i << "\t";
		for (size_t j = 0; j < col; ++j) {
			if (isVisited[i][j]) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[i][j]);
				cout << data[i][j] << "\t";
			}
			else if (isSuccess[i][j]) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[i][j]);
				cout << static_cast<char>(toupper(data[i][j])) << "\t";
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				cout << "*" << "\t";
			}
		}
		cout << endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void Board::printAll() const {
	cout << "\t";
	for (char i = 'a'; i < 'a' + static_cast<char>(col); ++i) {
		cout << i << "\t";
	}

	cout << endl;

	for (size_t i = 0; i < row; ++i) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		cout << i << "\t";
		for (size_t j = 0; j < col; ++j) {
			if (isSuccess[i][j]) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[i][j]);
				cout << static_cast<char>(toupper(data[i][j])) << "\t";
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[i][j]);
				cout << data[i][j] << "\t";
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		cout << endl;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void Board::clearVisited() {
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < col; ++j) {
			isVisited[i][j] = false;
		}
	}
}

void Board::setCell(size_t row, size_t col, char value) {
	data[row][col] = value;
}

char Board::getCell(size_t row, size_t col) const {
	return data[row][col];
}

void Board::setVisited(size_t row, size_t col, bool visited) {
	isVisited[row][col] = visited;
}

void Board::setSuccess(size_t row, size_t col, bool success) {
	isSuccess[row][col] = success;
}

void Board::openJoker() {
	isSuccess[jokerPos[0]][jokerPos[1]] = true;
}

bool Board::validCheck(size_t row, size_t col) const {
	return isValid[row][col];
}

bool Board::isComplete() const {
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < col; ++j) {
			if (!validCheck(i, j)) {
				return false;
			}
		}
	}
	return true;
}