#include <iostream>
#include <string>
#include <sstream>
#include "Board.h"
using namespace std;

int main() {
	string input;
	size_t row, col;
	bool validInput = false;

	while (!validInput)
	{
		cout << "보드의 크기 입력(가로, 세로 3~6): ";
		getline(cin, input);
		stringstream ss(input);
		ss >> row >> col;

		if (row >= 3 && row <= 6 && col >= 3 && col <= 6) validInput = true;
		else cout << "3 ~ 6 범위의 수를 입력해 주세요." << endl;
	}

	Board board(row, col);
	board.print();

	system("pause");
}