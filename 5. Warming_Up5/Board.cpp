#include <iostream>
#include <iomanip>
#include <windows.h>
#include "Square.h"
#include "Board.h"
using namespace std;

Board::Board() {
	for (int i = 0; i < width; i++) {
		board.push_back(vector<char>());
		for (int j = 0; j < height; j++) {
			board[i].push_back('.');
		}
	}
}

void Board::addSquare(const Square& square) {
	squares.push_back(square);
}

int Board::getSquare1Width() const {
	return squares[0].getWidth();
}

int Board::getSquare1Height() const {
	return squares[0].getHeight();
}

int Board::getSquare2Width() const {
	return squares[1].getWidth();
}

int Board::getSquare2Height() const {
	return squares[1].getHeight();
}

void Board::moveSquare1(int dx, int dy) {
	pair<int, int> minPos = squares[0].getMin();
	pair<int, int> maxPos = squares[0].getMax();
	minPos.first += dy;
	minPos.second += dx;
	maxPos.first += dy;
	maxPos.second += dx;
	squares[0].setMin(minPos.first, minPos.second);
	squares[0].setMax(maxPos.first, maxPos.second);
}

void Board::moveSquare2(int dx, int dy) {
	pair<int, int> minPos = squares[1].getMin();
	pair<int, int> maxPos = squares[1].getMax();
	minPos.first += dy;
	minPos.second += dx;
	maxPos.first += dy;
	maxPos.second += dx;
	squares[1].setMin(minPos.first, minPos.second);
	squares[1].setMax(maxPos.first, maxPos.second);
}

void Board::zoomSquare1(int dx, int dy) {
	pair<int, int> minPos = squares[0].getMin();
	pair<int, int> maxPos = squares[0].getMax();

	if (squares[0].getWidth() + dx >= width ||
		squares[0].getWidth() + dx < 0) return;
	if (squares[0].getHeight() + dy >= height ||
		squares[0].getHeight() + dy < 0) return;

	if (maxPos.first + dy >= height) minPos.first -= dy;
	else maxPos.first += dy;

	if (maxPos.second + dx >= width) minPos.second -= dx;
	else maxPos.second += dx;

	squares[0].setMin(minPos.first, minPos.second);
	squares[0].setMax(maxPos.first, maxPos.second);
}

void Board::zoomSquare2(int dx, int dy) {
	pair<int, int> minPos = squares[1].getMin();
	pair<int, int> maxPos = squares[1].getMax();

	if (squares[1].getWidth() + dx >= width ||
		squares[1].getWidth() + dx < 0) return;
	if (squares[1].getHeight() + dy >= height ||
		squares[1].getHeight() + dy < 0) return;

	if (maxPos.first + dy >= height) minPos.first -= dy;
	else maxPos.first += dy;

	if (maxPos.second + dx >= width) minPos.second -= dx;
	else maxPos.second += dx;

	squares[1].setMin(minPos.first, minPos.second);
	squares[1].setMax(maxPos.first, maxPos.second);
}

int Board::getWidth() const {
	return width;
}

int Board::getHeight() const {
	return height;
}

void Board::setWidth(int w) {
	if (w < 10) return;
	else if (w > 40) return;
	width = w;
}

void Board::setHeight(int h) {
	if (h < 10) return;
	else if (h > 40) return;
	height = h;
}

void Board::resetBoard() {
	vector<vector<char>> newBoard;

	for (int i = 0; i < width; i++) {
		newBoard.push_back(vector<char>());
		for (int j = 0; j < height; j++) {
			newBoard[i].push_back('.');
		}
	}
	
	board = newBoard;
}

void Board::printBoard() {
	resetBoard();

	char alphabet = 'O';
	for (auto& square : squares) {
		for (int u = square.getMin().first; u <= square.getMax().first; u++) {
			for (int v = square.getMin().second; v <= square.getMax().second; v++) {
				int row = u;
				int col = v;
				
				if (row < 0) {
					while (row >= 0) row += width;
				}
				else if (u >= width) {
					while (row >= width) row -= width;
				}
				else row = u;

				if (col < 0) {
					while (col >= 0) col += height;
				}
				else if (col >= height) {
					while (col >= height) col -= height;
				}
				else col = v;

				if (alphabet == 'X' && board[row][col] == 'O') board[row][col] = '#';
				else board[row][col] = alphabet;
			}
		}
		alphabet = 'X';
	}

	cout << setw(5);
	for (int u = 0; u < width; u++) {
		for (int v = 0; v < height; v++) {
			if (board[u][v] == 'O') SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); // 붉은색
			else if (board[u][v] == 'X') SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); // 파란색
			else if (board[u][v] == '#') SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); // 보라색
			else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 기본 색상
			cout << board[u][v] << setw(5);
		}
		cout << endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}