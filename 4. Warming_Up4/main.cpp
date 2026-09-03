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
	bool isRunning = true;
	string command;

	while (isRunning)
	{
		board.print();

		cout << "뒤집을 좌표(예: \"a1 b2\")나 명령어(\"help\"로 명령어들을 볼 수 있습니다)를 입력하세요\n";
		cout << "명령어 입력: ";
		getline(cin, command);

		//리셋하고 다시 시작
		if (command == "r") {
			board = Board(row, col);
			system("cls");
		}

		//일시적으로 모든 칸을 뒤집음
		else if (command == "h") {
			system("cls");
			board.printAll();
			system("pause");

			system("cls");
		}

		//종료
		else if (command == "q") isRunning = false;

		else if (command == "help") {
			cout << "명령어 목록:\n";
			cout << "r: 보드를 리셋하고 다시 시작\n";
			cout << "h: 모든 칸을 일시적으로 뒤집음\n";
			cout << "q: 게임 종료\n";
		}
	}

	system("pause");
}